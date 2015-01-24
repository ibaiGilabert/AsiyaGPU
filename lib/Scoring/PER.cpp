#include "../include/PER.hpp"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <iostream>
#include <fstream>
#include <sstream>

#include <boost/regex.hpp>
#include <boost/filesystem.hpp>
#include <boost/algorithm/string.hpp>


const string PER::PEREXT = "PER";
const string PER::TPER = "per/PER.pl";

set<string> PER::create_rPER() {
	set<string> rPER;
	rPER.insert("-"+PER::PEREXT);
	return rPER;
}
const set<string> PER::rPER = create_rPER();


void PER::PER_f_create_doc(string input, string output) {
	// description _ creation of a RAW evaluation document
	if (Config::verbose > 1) fprintf(stderr, "OPENING <%s> for PER parsing...\n", input.c_str());

    if (exists(boost::filesystem::path(input))) {
    	if (Config::verbose ) fprintf(stderr, "reading <%s>\n", input.c_str());

    	ifstream input_file(input.c_str());
    	ofstream output_file(output.c_str());
	    if (!output_file) { fprintf(stderr, "couldn't open output file: %s\n", output.c_str()); exit(1); }
    	if (input_file) {
	    	string str;
	    	boost::regex re("\\s+$");
        	boost::regex re2("\r");
            while(getline(input_file, str)) {
	        	str = boost::regex_replace(str, re, "");
	            str = boost::regex_replace(str, re2, "");
	            if (Config::CASE == Common::CASE_CI) boost::to_lower(str);
	    		output_file << str << endl;
	    	}
		    output_file.close();
	    	input_file.close();
    	} else { fprintf(stderr, "couldn't open input file: %s\n", input.c_str()); exit(1); }
	} else { printf("\n[ERROR] UNAVAILABLE file <%s>!!!\n", input.c_str()); exit(1); }
}

void PER::read_PER(string report, int do_neg, double &PER, vector<double> &lPER) {
	// description _ read PER (system and segment scores) from report file
    ifstream file(report.c_str());
    if (file) {
		string str;
    	while (getline(file, str)) {
			vector<string> v;
	    	istringstream buf(str);
	    	for (string token; getline(buf, token, ' '); ) v.push_back(token);

	     	if (do_neg) {
	     		if (v.size() == 3) lPER.push_back( -atof(v[2].c_str()) );
	     		else if (v.size() == 1) PER = -atof(str.c_str());
	     	}
	     	else {
	     		if (v.size() == 3) lPER.push_back( atof(v[2].c_str()) );
	     		else if (v.size() == 1) PER = atof(str.c_str());
	     	}
	    }
	    file.close();
	} else { fprintf(stderr, "couldn't open file: %s\n", report.c_str()); exit(1); }
}

void PER::computePER(string TGT, int do_neg, double &MAXSYS, vector<double> &MAXSEG) {
	// description _ computes -PER score (multiple references)
	string t_id;
    if (Config::serialize) t_id = "_" + TGT;//TB_FORMAT::get_formated_thread(TGT);
	stringstream ssOut, ssReport;
	ssReport << Common::DATA_PATH << "/" << Common::TMP << "/" << rand()%(Common::NRAND+1) << "." << PER::PEREXT << t_id << "." << Common::REPORTEXT;
	ssOut << Common::DATA_PATH << "/" << Common::TMP << "/" << rand()%(Common::NRAND+1) << "." << PER::PEREXT << t_id << "." << Common::SYSEXT;

	string outRND = ssOut.str();
	string reportPER = ssReport.str();
	string toolPER = "perl "+Config::tools+"/"+PER::TPER;
	//cout << "[PER] toolPER: " << toolPER << endl;

	if (Config::verbose) fprintf(stderr, "building %s...\n", reportPER.c_str());
	PER_f_create_doc(TESTBED::Hsystems[TGT], outRND);

	MAXSYS = Common::NOT_DEFINED;
	//vector<double> maxSEGscores;
    for (map<string, string>::const_iterator it = TESTBED::Hrefs.begin(); it != TESTBED::Hrefs.end(); ++it) {
    	//string ref = it->second;
    	stringstream ssRef;
		ssRef << Common::DATA_PATH << "/" << Common::TMP << "/" << rand()%(Common::NRAND+1) << "." << PER::PEREXT << t_id << "." << Common::REFEXT;
		string refRND = ssRef.str();

		PER_f_create_doc(it->second, refRND);

		string sc = toolPER + " -s -t " + outRND + " -r " + refRND + " > " + reportPER;
		Common::execute_or_die(sc, "[ERROR] probles running PER...");

		double sys;
		vector<double> segs;
		read_PER(reportPER, do_neg, sys, segs);

		if (MAXSYS == Common::NOT_DEFINED) MAXSYS = sys;
		else if (sys > MAXSYS) MAXSYS = sys;

		if (MAXSEG.empty()) MAXSEG = vector<double>(segs.size(), Common::NOT_DEFINED);
		for (int i = 0; i < segs.size(); ++i) {
			if (MAXSEG[i] == Common::NOT_DEFINED) MAXSEG[i] = segs[i];
			else if (segs[i] > MAXSEG[i]) MAXSEG[i] = segs[i];
		}

		string sysaux;
		sysaux = "rm -f "+reportPER;	system(sysaux.c_str());
		sysaux = "rm -f "+refRND;		system(sysaux.c_str());
    }
    string sysaux = "rm -f "+outRND;	system(sysaux.c_str());
}

void PER::doMetric(string TGT, string REF, string prefix, Scores &hOQ) {
	// description _ computes -PER score (multiple references)
	vector<string> mPER(PER::rPER.size());

	int GO, i;
	GO = i = 0;
	for (set<string>::const_iterator it = PER::rPER.begin(); it != PER::rPER.end(); ++it, ++i)
		mPER[i] = *it;
	for (i = 0; i < mPER.size() and !GO; ++i) {
		if (Config::Hmetrics.find(mPER[i]) != Config::Hmetrics.end()) GO = 1;
	}

	if (GO) {
		if (Config::verbose ) fprintf(stderr, "%s...\n", PER::PEREXT.c_str());

		for (i = 0; i < mPER.size(); ++i) {
			string reportPERxml = Common::DATA_PATH+"/"+Common::REPORTS+"/"+TGT+"/"+REF+"/-"+PER::PEREXT+"."+Common::XMLEXT;
			if ( (!exists(boost::filesystem::path(reportPERxml)) and !exists(boost::filesystem::path(reportPERxml+"."+Common::GZEXT))) or Config::remake) {
	    		double SYS;
	    		vector<double> SEG, d_scores, s_scores;
	    		computePER(TGT, 1, SYS, SEG);
				TESTBED::get_seg_doc_scores(SEG, 0, TGT, d_scores, s_scores);
				if (Config::O_STORAGE == 1) {
		    		sc_asiya.write_report(TGT, REF, "-PER", SYS, d_scores, s_scores);
	         		cout << "SC_ASIYA DOCUMENT -PER CREATED" << endl;
	         	}
	         	hOQ.save_hash_scores("-PER", TGT, REF, SYS, d_scores, s_scores);
	   		}

			reportPERxml = Common::DATA_PATH+"/"+Common::REPORTS+"/"+TGT+"/"+REF+"/"+PER::PEREXT+"."+Common::XMLEXT;
			if ( (!exists(boost::filesystem::path(reportPERxml)) and !exists(boost::filesystem::path(reportPERxml+"."+Common::GZEXT))) or Config::remake) {
	    		double SYS;
	    		vector<double> SEG, d_scores, s_scores;
	    		computePER(TGT, 0, SYS, SEG);
				TESTBED::get_seg_doc_scores(SEG, 0, TGT, d_scores, s_scores);
				if (Config::O_STORAGE == 1) {
		    		sc_asiya.write_report(TGT, REF, "PER", SYS, d_scores, s_scores);
	         		cout << "SC_ASIYA DOCUMENT PER CREATED" << endl;
	         	}
	         	hOQ.save_hash_scores("PER", TGT, REF, SYS, d_scores, s_scores);
	   		}
		}
        if (Config::serialize) hOQ.save_struct_scores(TB_FORMAT::make_serial(PER::PEREXT, TGT, REF));

	}
}
