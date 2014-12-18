#include "../include/LeM.hpp"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <iostream>
#include <fstream>
#include <sstream>

#include <boost/regex.hpp>
#include <boost/filesystem.hpp>
//#include <boost/algorithm/string.hpp>

const string LeM::LeMEXT = "LeM";
const string LeM::TLeM = "lengthmodel/LengthModel.jar";

set<string> LeM::create_rLeM() {
	set<string> rLeM;
	rLeM.insert(LeM::LeMEXT);
	return rLeM;
}
const set<string> LeM::rLeM = create_rLeM();


void LeM::LeM_f_create_doc(string input, string output, string TGT, string G) {
	// description _ creation of a RAW evaluation document
	if (Config::verbose > 1) fprintf(stderr, "OPENING <%s> for LeM parsing...\n", input.c_str());

    if (exists(boost::filesystem::path(input))) {
    	if (Config::verbose ) fprintf(stderr, "reading <%s>\n", input.c_str());

    	ifstream input_file(input.c_str());
    	ofstream output_file(output.c_str());
	    if (!output_file) { fprintf(stderr, "couldn't open output file: %s\n", output.c_str()); exit(1); }
    	if (input_file) {
    		int i = 1;
    		string docid = TESTBED::IDX[TGT][i][0];
	    	string str;
	    	boost::regex re("\\s+$");
        	boost::regex re2("\r");
            while(getline(input_file, str)) {
	        	str = boost::regex_replace(str, re, "");
	            str = boost::regex_replace(str, re2, "");
	            if (G == Common::G_SEG) 				// seg-level
	            	output_file << str << endl;
	            else if (G == Common::G_DOC) {			// doc-level
	            	if (TESTBED::IDX[TGT][i][0] != docid) {
	            		output_file << endl << str << " ";
	            		docid = TESTBED::IDX[TGT][i][0];
	            	}
	            	else output_file << str << " ";
	            }
	            else 									// sys-level
	            	output_file << str << " ";
	            ++i;
			}
		    output_file.close();
	    	input_file.close();
    	} else { fprintf(stderr, "couldn't open input file: %s\n", input.c_str()); exit(1); }
	} else { printf("\n[ERROR] UNAVAILABLE file <%s>!!!\n", input.c_str()); exit(1); }
}

void LeM::read_LeM(string report, double &SYS, vector<double> &DOC, vector<double> &SEG) {
	// description _ reads a given MetricsMaTr format scr file (of a given granularity)
    string report_sys = report+"."+Common::G_SYS;
    ifstream file_sys(report_sys.c_str());
    if (file_sys) {
		string str;
    	getline(file_sys, str);
		SYS = atof(str.c_str());
		file_sys.close();
	} else { fprintf(stderr, "[ERROR] Unvailable file <%s>\n", report_sys.c_str()); exit(1); }

	string report_doc = report+"."+Common::G_DOC;
	ifstream file_doc(report_doc.c_str());
    if (file_doc) {
    	string str;
    	while (getline(file_doc, str))
			DOC.push_back(atof(str.c_str()));
		file_doc.close();
	} else { fprintf(stderr, "[ERROR] Unvailable file <%s>\n", report_doc.c_str()); exit(1); }

    string report_seg = report+"."+Common::G_SEG;
	ifstream file_seg(report_seg.c_str());
    if (file_seg) {
    	string str;
    	while (getline(file_seg, str))
			SEG.push_back(atof(str.c_str()));
		file_seg.close();
	} else { fprintf(stderr, "[ERROR] Unvailable file <%s>\n", report_seg.c_str()); exit(1); }
}

void LeM::computeLeM(string TGT, string langpair, double &SYS, vector<double> &DOC, vector<double> &SEG) {
	// description _ computes -LeM score (multiple references)
	string t_id;
    if (Config::serialize) t_id = "_" + TGT;//TB_FORMAT::get_formated_thread(TGT);
	stringstream ssOut, ssSrc, ssReport;
	ssReport << Common::DATA_PATH << "/" << Common::TMP << "/" << rand()%(Common::NRAND+1) << "." << LeM::LeMEXT << t_id << "." << Common::REPORTEXT;
	ssOut << Common::DATA_PATH << "/" << Common::TMP << "/" << rand()%(Common::NRAND+1) << "." << LeM::LeMEXT << t_id << "." << Common::SYSEXT;
	ssSrc << Common::DATA_PATH << "/" << Common::TMP << "/" << rand()%(Common::NRAND+1) << "." << LeM::LeMEXT << t_id << "." << Common::SRCEXT;

	string outRND = ssOut.str();
	string srcRND = ssSrc.str();
	string reportLeM = ssReport.str();

	string mem_options = "-Xms1G -Xmx3G";
	string toolLeM = "java -Dfile.encoding=UTF-8 "+mem_options+" -jar "+Config::tools+"/"+LeM::TLeM;

	if (Config::verbose) fprintf(stderr, "building %s...\n", reportLeM.c_str());

	// SEG LEVEL
	LeM_f_create_doc(TESTBED::Hsystems[TGT], outRND, TGT, Common::G_SEG);
	LeM_f_create_doc(TESTBED::src, srcRND, TGT, Common::G_SEG);

	string sc = toolLeM+" -s "+srcRND+" -t "+outRND+" -p "+langpair+" > "+reportLeM+"."+Common::G_SEG+" 2> /dev/null";
	Common::execute_or_die(sc, "[ERROR] problems running LeM...");

	// DOC LEVEL
	LeM_f_create_doc(TESTBED::Hsystems[TGT], TGT, outRND, Common::G_DOC);
	LeM_f_create_doc(TESTBED::src, srcRND, TGT, Common::G_DOC);

	sc = toolLeM+" -s "+srcRND+" -t "+outRND+" -p "+langpair+" > "+reportLeM+"."+Common::G_DOC+" 2> /dev/null";
	Common::execute_or_die(sc, "[ERROR] problems running LeM...");

	// SYS LEVEL
	LeM_f_create_doc(TESTBED::Hsystems[TGT], outRND, TGT, Common::G_SEG);
	LeM_f_create_doc(TESTBED::src, srcRND, TGT, Common::G_SEG);

	sc = toolLeM+" -s "+srcRND+" -t "+outRND+" -p "+langpair+" > "+reportLeM+"."+Common::G_SYS+" 2> /dev/null";
	Common::execute_or_die(sc, "[ERROR] problems running LeM...");

	read_LeM(reportLeM, SYS, DOC, SEG);

	string sysaux;
	sysaux = "rm -f "+reportLeM+"."+Common::G_SEG;		system(sysaux.c_str());
	sysaux = "rm -f "+reportLeM+"."+Common::G_DOC;		system(sysaux.c_str());
	sysaux = "rm -f "+reportLeM+"."+Common::G_SYS;		system(sysaux.c_str());
	sysaux = "rm -f "+srcRND;		system(sysaux.c_str());
	sysaux = "rm -f "+outRND;		system(sysaux.c_str());
}

void LeM::doMetric(string TGT, string REF, string prefix, Scores &hOQ) {
	// description _ computes -LeM score (multiple references)
	vector<string> mLeM(LeM::rLeM.size());

	int GO, i;
	GO = i = 0;
	for (set<string>::const_iterator it = LeM::rLeM.begin(); it != LeM::rLeM.end(); ++it, ++i)
		mLeM[i] = *it;
	for (i = 0; i < mLeM.size() and !GO; ++i) {
		if (Config::Hmetrics.find(mLeM[i]) != Config::Hmetrics.end()) GO = 1;
	}

	if (GO) {
		if (Config::verbose ) fprintf(stderr, "%s...\n", LeM::LeMEXT.c_str());

		string reportLeMxml = Common::DATA_PATH+"/"+Common::REPORTS+"/"+TGT+"/"+LeM::LeMEXT+"/"+LeM::LeMEXT+"."+Common::XMLEXT;
		if ( (!exists(boost::filesystem::path(reportLeMxml)) and !exists(boost::filesystem::path(reportLeMxml+"."+Common::GZEXT))) or Config::remake) {
    		double SYS;
    		vector<double> DOC, SEG;
    		string langpair = Config::SRCLANG+"-"+Config::LANG;
    		computeLeM(TGT, langpair, SYS, DOC, SEG);
			if (Config::O_STORAGE == 1) {
	    		sc_asiya.write_report(TGT, LeM::LeMEXT, LeM::LeMEXT, SYS, DOC, SEG);
         		cout << "SC_ASIYA DOCUMENT " << LeM::LeMEXT << " CREATED" << endl;
         	}
         	hOQ.save_hash_scores(LeM::LeMEXT, TGT, REF, SYS, DOC, SEG);
   		}

        if (Config::serialize) hOQ.save_struct_scores(TB_FORMAT::make_serial(LeM::LeMEXT, TGT, REF));

	}
}
