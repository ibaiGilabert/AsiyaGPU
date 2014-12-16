#include "../include/WER.hpp"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <iostream>
#include <fstream>
#include <sstream>

#include <boost/regex.hpp>
#include <boost/filesystem.hpp>
#include <boost/algorithm/string.hpp>


const string WER::WEREXT = "WER";
const string WER::TWER = "wer/WER.pl";

set<string> WER::create_rWER() {
	set<string> rWER;
	rWER.insert("-"+WER::WEREXT);
	return rWER;
}
const set<string> WER::rWER = create_rWER();


void WER::WER_f_create_doc(string input, string output) {
	// description _ creation of a RAW evaluation document
	if (Config::verbose > 1) fprintf(stderr, "OPENING <%s> for WER parsing...\n", input.c_str());

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

void WER::read_WER(string report, int do_neg, double &WER, vector<double> &lWER) {
	// description _ read WER (system and segment scores) from report file
    ifstream file(report.c_str());
    if (file) {
		string str;
    	while (getline(file, str)) {
			vector<string> v;
	    	istringstream buf(str);
	    	for (string token; getline(buf, token, ' '); ) v.push_back(token);

	     	if (do_neg) {
	     		if (v.size() == 3) lWER.push_back( -atof(v[2].c_str()) );
	     		else if (v.size() == 1) WER = -atof(str.c_str());
	     	}
	     	else {
	     		if (v.size() == 3) lWER.push_back( atof(v[2].c_str()) );
	     		else if (v.size() == 1) WER = atof(str.c_str());
	     	}
	    }
	    file.close();
	} else { fprintf(stderr, "couldn't open file: report\n", report.c_str()); exit(1); }
}

void WER::computeWER(string TGT, int do_neg, double &MAXSYS, vector<double> &MAXSEG) {
	// description _ computes -WER score (multiple references)
	string t_id;
    if (Config::serialize) t_id = "_" + TGT;//TB_FORMAT::get_formated_thread(TGT);
	stringstream ssOut, ssReport;
	ssReport << Common::DATA_PATH << "/" << Common::TMP << "/" << rand()%(Common::NRAND+1) << "." << WER::WEREXT << t_id << "." << Common::REPORTEXT;
	ssOut << Common::DATA_PATH << "/" << Common::TMP << "/" << rand()%(Common::NRAND+1) << "." << WER::WEREXT << t_id << "." << Common::SYSEXT;

	string outRND = ssOut.str();
	string reportWER = ssReport.str();
	string toolWER = "perl "+Config::tools+"/"+WER::TWER;
	cout << "[WER] toolWER: " << toolWER << endl;

	if (Config::verbose) fprintf(stderr, "building %s...\n", reportWER.c_str());
	WER_f_create_doc(TESTBED::Hsystems[TGT], outRND);

	MAXSYS = Common::NOT_DEFINED;
	//vector<double> maxSEGscores;
    for (map<string, string>::const_iterator it = TESTBED::Hrefs.begin(); it != TESTBED::Hrefs.end(); ++it) {
    	//string ref = it->second;
    	stringstream ssRef;
		ssRef << Common::DATA_PATH << "/" << Common::TMP << "/" << rand()%(Common::NRAND+1) << "." << WER::WEREXT << t_id << "." << Common::REFEXT;
		string refRND = ssRef.str();

		WER_f_create_doc(it->second, refRND);

		string sc = toolWER + " -s -t " + outRND + " -r " + refRND + " > " + reportWER;
		Common::execute_or_die(sc, "[ERROR] probles running WER...");

		double sys;
		vector<double> segs;
		read_WER(reportWER, do_neg, sys, segs);

		if (MAXSYS == Common::NOT_DEFINED) MAXSYS = sys;
		else if (sys > MAXSYS) MAXSYS = sys;

		if (MAXSEG.empty()) MAXSEG = vector<double>(segs.size(), Common::NOT_DEFINED);
		for (int i = 0; i < segs.size(); ++i) {
			if (MAXSEG[i] == Common::NOT_DEFINED) MAXSEG[i] = segs[i];
			else if (segs[i] > MAXSEG[i]) MAXSEG[i] = segs[i];
		}

		string sysaux;
		sysaux = "rm -f "+reportWER;	system(sysaux.c_str());
		sysaux = "rm -f "+refRND;		system(sysaux.c_str());
    }
    string sysaux = "rm -f "+outRND;	system(sysaux.c_str());
}

void WER::doMetric(string TGT, string REF, string prefix, Scores &hOQ) {
	// description _ computes -WER score (multiple references)
	vector<string> mWER(WER::rWER.size());

	int GO, i;
	GO = i = 0;
	for (set<string>::const_iterator it = WER::rWER.begin(); it != WER::rWER.end(); ++it, ++i)
		mWER[i] = *it;
	for (i = 0; i < mWER.size() and !GO; ++i) {
		if (Config::Hmetrics.find(mWER[i]) != Config::Hmetrics.end()) GO = 1;
	}

	if (GO) {
		if (Config::verbose ) fprintf(stderr, "%s...\n", WER::WEREXT.c_str());

		for (i = 0; i < mWER.size(); ++i) {
			string reportWERxml = Common::DATA_PATH+"/"+Common::REPORTS+"/"+TGT+"/"+REF+"/-"+WER::WEREXT+"."+Common::XMLEXT;
			if ( (!exists(boost::filesystem::path(reportWERxml)) and !exists(boost::filesystem::path(reportWERxml+"."+Common::GZEXT))) or Config::remake) {
	    		double SYS;
	    		vector<double> SEG, d_scores, s_scores;
	    		computeWER(TGT, 1, SYS, SEG);
				TESTBED::get_seg_doc_scores(SEG, 0, TGT, d_scores, s_scores);
				if (Config::O_STORAGE == 1) {
		    		sc_asiya.write_report(TGT, REF, "-WER", SYS, d_scores, s_scores);
	         		cout << "SC_ASIYA DOCUMENT -WER CREATED" << endl;
	         	}
	         	hOQ.save_hash_scores("-WER", TGT, REF, SYS, d_scores, s_scores);
	   		}

			reportWERxml = Common::DATA_PATH+"/"+Common::REPORTS+"/"+TGT+"/"+REF+"/"+WER::WEREXT+"."+Common::XMLEXT;
			if ( (!exists(boost::filesystem::path(reportWERxml)) and !exists(boost::filesystem::path(reportWERxml+"."+Common::GZEXT))) or Config::remake) {
	    		double SYS;
	    		vector<double> SEG, d_scores, s_scores;
	    		computeWER(TGT, 0, SYS, SEG);
				TESTBED::get_seg_doc_scores(SEG, 0, TGT, d_scores, s_scores);
				if (Config::O_STORAGE == 1) {
		    		sc_asiya.write_report(TGT, REF, "WER", SYS, d_scores, s_scores);
	         		cout << "SC_ASIYA DOCUMENT WER CREATED" << endl;
	         	}
	         	hOQ.save_hash_scores("WER", TGT, REF, SYS, d_scores, s_scores);
	   		}
		}
        if (Config::serialize) hOQ.save_struct_scores(TB_FORMAT::make_serial(WER::WEREXT, TGT, REF));

	}
}
