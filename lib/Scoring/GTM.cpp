#include "../include/GTM.hpp"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <iostream>
#include <fstream>
#include <sstream>

//#include <boost/regex.hpp>
#include <boost/filesystem.hpp>
//#include <boost/algorithm/string.hpp>


const string GTM::GTMEXT = "GTM";
const string GTM::TGTM = "gtm-1.4";	// version 1.4

set<string> GTM::create_rGTM() {
	set<string> rGTM;
	rGTM.insert(GTM::GTMEXT+"-1");
	rGTM.insert(GTM::GTMEXT+"-2");
	rGTM.insert(GTM::GTMEXT+"-3");
	return rGTM;
}
const set<string> GTM::rGTM = create_rGTM();


double GTM::read_GTM(string reportGTM) {
	// description _ read GTM value from report file
	string last;
	ifstream file(reportGTM.c_str());
	if (file) {
		file.seekg(-1, ios_base::end);  //go to one spot before end of file
		bool loop = true;
		while (loop) {
			char c;
			file.get(c);					// Get current byte's data
			if ((int)file.tellg() <= 1) {
				file.seekg(0);				// If the data was at or before the 0th byte
				loop = false;				// The first line is the last line, so stop here
			}
			else if (c == ' ') loop = false;
			else file.seekg(-2, ios_base::cur);	// Move to the front of that data, then to the front of the data before it
		}
		getline(file, last);
		file.close();
	} else { fprintf(stderr, "couldn't open input file: %s\n", reportGTM.c_str()); exit(1); }

    //cout << "[GTM]: SYS scores readed: " << last << endl;
    return atof(last.c_str());
}

vector<double> GTM::read_GTM_segments(string reportGTM) {
	// description _ read GTM value from report file (for all segments)
	vector<double> lgtm;
	ifstream file(reportGTM.c_str());
    if (file) {
    	string str;
	    while (getline(file, str)) {
			vector<string> laux;
		    istringstream iss(str);
		    for(std::string token; getline(iss, token, ' '); ) laux.push_back(token);
		    if (laux.size() == 3) lgtm.push_back(atof(laux[2].c_str()));
	    }
        file.close();
    } else { fprintf(stderr, "couldn't open file: %s\n", reportGTM.c_str()); exit(1); }

    return lgtm;
}


void GTM::computeGTM(string TGT, int e, double &SYS, vector<double> &SEG) {
	// description _ computes GTM scores -> n = 1..4, LCS, S*, SU*, W-1.2 (multiple references)
	string mem_options = "-Xms2G -Xmx2G";

	stringstream tGTM;
	tGTM << "java -Dfile.encoding=UTF-8 " << mem_options << " -jar " << Config::tools << "/" << GTM::TGTM << "/gtm.jar +s +d";
	string toolGTM = tGTM.str();
	fprintf(stderr, "toolGTM -> %s\n", toolGTM.c_str());

	string t_id;
    if (Config::serialize) t_id = "_" + TGT;//TB_FORMAT::get_formated_thread(TGT);

	//srand(time(NULL));
	vector<string> LrefTGMsgml;
	for (map<string, string>::const_iterator it = TESTBED::Hrefs.begin(); it != TESTBED::Hrefs.end(); ++it) {
		string ref = it->second;

		stringstream ssRef;
		ssRef << Common::DATA_PATH << "/" << Common::TMP << "/" << rand() % (Common::NRAND + 1) << "." << Common::REFEXT << "." <<  GTM::GTMEXT << t_id << "." << Common::SGMLEXT;
		string refGTMsgml = ssRef.str();

		if (!exists(boost::filesystem::path(refGTMsgml)) or Config::remake)
			TB_NIST::SGML_GTM_f_create_mteval_doc(ref, refGTMsgml);
	
		LrefTGMsgml.push_back(refGTMsgml);
	}

	stringstream ssOut, ssReport;
	ssOut << Common::DATA_PATH << "/" << Common::TMP << "/" << rand() % (Common::NRAND + 1) << "." << Common::SYSEXT << "." <<  GTM::GTMEXT << t_id << "." << Common::SGMLEXT;
	ssReport << Common::DATA_PATH << "/" << Common::TMP << "/" << rand() % (Common::NRAND + 1) << "." << GTM::GTMEXT << "-" << e << t_id << "." << Common::REPORTEXT;

	string outGTMsgml = ssOut.str();
	string reportGTM = ssReport.str();
	boost::filesystem::path out_path(outGTMsgml);

	if (!exists(out_path) or Config::remake) {
		TB_NIST::SGML_GTM_f_create_mteval_doc(TESTBED::Hsystems[TGT], outGTMsgml);
	}

	if (Config::verbose > 1) fprintf(stderr, "building %s\n", reportGTM.c_str());

	stringstream sc;
	sc << toolGTM << " -e " << e << " " << outGTMsgml;
	for (int i = 0; i < LrefTGMsgml.size(); ++i) sc << " " << LrefTGMsgml[i];
	sc << " > " << reportGTM;
	string ms = "[ERROR] problems running GTM...";

	Common::execute_or_die(sc.str(), ms);

	SYS = read_GTM(reportGTM);
	SEG = read_GTM_segments(reportGTM);

	string sysaux = "rm -f " + reportGTM;
	system(sysaux.c_str());

	for (int i = 0; i < LrefTGMsgml.size(); ++i) {
		boost::filesystem::path Lref_path(LrefTGMsgml[i]);
		if (exists(Lref_path)) {
			sysaux = "rm -f " + LrefTGMsgml[i];
			system(sysaux.c_str());
		}
	}
	if (exists(out_path)) {
		sysaux = "rm -f " + outGTMsgml;
		system(sysaux.c_str());
	}
}

void GTM::doMetric(string TGT, string REF, string prefix, Scores &hOQ) {
	// description _ computes GTM F1 (by calling Proteus java gtm) -> e = 1..3 (multiple references)
	int GO = 0;
	for (set<string>::const_iterator it = GTM::rGTM.begin(); !GO and it != GTM::rGTM.end(); ++it) {
		if (Config::Hmetrics.count(prefix+(*it))) GO = 1;
	}

	if (GO) {
		if (Config::verbose) fprintf(stderr, "%s\n", GTM::GTMEXT.c_str());

		string reportGTM1xml = Common::DATA_PATH+"/"+Common::REPORTS+"/"+TGT+"/"+REF+"/"+prefix+GTM::GTMEXT+"-1."+Common::XMLEXT;
		string reportGTM2xml = Common::DATA_PATH+"/"+Common::REPORTS+"/"+TGT+"/"+REF+"/"+prefix+GTM::GTMEXT+"-2."+Common::XMLEXT;
		string reportGTM3xml = Common::DATA_PATH+"/"+Common::REPORTS+"/"+TGT+"/"+REF+"/"+prefix+GTM::GTMEXT+"-3."+Common::XMLEXT;

	    double SYS;
    	vector<double> SEG;
		if ( (!exists(boost::filesystem::path(reportGTM1xml)) and !exists(boost::filesystem::path(reportGTM1xml+"."+Common::GZEXT))) or Config::remake) {
			computeGTM(TGT, 1, SYS, SEG);
	    	vector<double> d_scores, s_scores;
			TESTBED::get_seg_doc_scores(SEG, 0, TGT, d_scores, s_scores);

         	string prefG = prefix + GTM::GTMEXT + "-1";

	    	if (Config::O_STORAGE == 1) {
	    		sc_asiya.write_report(TGT, REF, prefG, SYS, d_scores, s_scores);
         		fprintf(stderr, "SC_ASIYA DOCUMENT %s CREATED\n", prefG.c_str());
         	}
         	hOQ.save_hash_scores(prefG, TGT, REF, SYS, d_scores, s_scores);
	    }
		if ( (!exists(boost::filesystem::path(reportGTM2xml)) and !exists(boost::filesystem::path(reportGTM2xml+"."+Common::GZEXT))) or Config::remake) {
			computeGTM(TGT, 2, SYS, SEG);
	    	vector<double> d_scores, s_scores;
         	TESTBED::get_seg_doc_scores(SEG, 0, TGT, d_scores, s_scores);

			string prefG = prefix + GTM::GTMEXT + "-2";
			if (Config::O_STORAGE == 1) {
	    		sc_asiya.write_report(TGT, REF, prefG, SYS, d_scores, s_scores);
         		fprintf(stderr, "SC_ASIYA DOCUMENT %s CREATED\n", prefG.c_str());
         	}
	    	hOQ.save_hash_scores(prefG, TGT, REF, SYS, d_scores, s_scores);
		}
		if ( (!exists(boost::filesystem::path(reportGTM3xml)) and !exists(boost::filesystem::path(reportGTM3xml+"."+Common::GZEXT))) or Config::remake) {
			computeGTM(TGT, 3, SYS, SEG);
			vector<double> d_scores, s_scores;
			TESTBED::get_seg_doc_scores(SEG, 0, TGT, d_scores, s_scores);

	    	string prefG = prefix + GTM::GTMEXT + "-3";
         	if (Config::O_STORAGE == 1) {
	    		sc_asiya.write_report(TGT, REF, prefG, SYS, d_scores, s_scores);
         		fprintf(stderr, "SC_ASIYA DOCUMENT %s CREATED\n", prefG.c_str());
         	}
         	hOQ.save_hash_scores(prefG, TGT, REF, SYS, d_scores, s_scores);
		}
        if (Config::serialize) //serialize
            hOQ.save_struct_scores(TB_FORMAT::make_serial(GTM::GTMEXT, TGT, REF));
	}
}
