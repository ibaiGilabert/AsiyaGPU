#include "WER.hpp"

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

map<string, int> WER::create_rWER() {
	map<string, int> rWER;
	rWER["-" + WER::WEREXT] = 1;
	return rWER;
}
const map<string, int> WER::rWER = create_rWER;


void WER::WER_f_create_doc(string input, string output) {
	// description _ creation of a RAW evaluation document
	if (Config::verbose > 1) fprintf(stderr, "OPENING <%s> for WER parsing...\n", input.c_str());

    boost::filesystem::path input_path(input);
    if (exists(input_path)) {
    	if (Config::verbose > 1) fprintf(stderr, "reading <%s>\n", input.c_str());

    	ifstream input_file(input.c_str());
    	ofstream output_file(output.c_str());
    	string str;
    	while(getline(input_file, str)) {
        	boost::regex re("\\s+$");
        	boost::regex re2("\r");
            str = boost::regex_replace(str, re, "");
            str = boost::regex_replace(str, re2, "");
            if (Config::CASE == Common::CASE_CI) boost::to_lower(str);
    		output_file << str << endl;
    	}
    	output_file.close();
    	input_file.close();
    } else printf("\n[ERROR] UNAVAILABLE file <%s>!!!\n", input.c_str());
}

pair<double, vector<double> > WER::read_WER(string report, int do_neg) {
	// description _ read WER (system and segment scores) from report file
    double WER = 0;
    vector<double> lWER;

    string str;
    ifstream file(report.c_str());
    if (file) {
		while (getline(file, str)) {
			vector<std::string> v;
	    	std::string s = "Hello How Are You Today Man";
	    	istringstream buf(str);
	    	for (string token; getline(buf, token, ' '); )
	     		v.push_back(token);

	     	if (do_neg) {
	     		if (v.size() == 3) lWER.push_back(-v[2]);
	     		else if (v.size() == 1) WER = -;
	     	}
	     	else {
	     		if (v.size() == 3) lWER.push_back(v[2]);
	     		else if (v.size() == 1) WER = ;
	     	}
	    }
	    file.close();
	} else { fprintf(stderr, "couldn't open file: report\n", report.c_str()); exit(1); }

	return make_pair(WER, lWER);
}

pair<double, vector<double> > WER::computeWER(string TGT, int do_neg) {
	// description _ computes -WER score (multiple references)
	stringstream ssReport;
	ssReport << Common::DATA_PATH << "/" << Common::TMP << "/" << rand() % (Common::NRAND + 1) << "." << WER::WEREXT << "." << Common::REPORTEXT;
	ssOut << Common::DATA_PATH << "/" << Common::TMP << "/" << rand() % (Common::NRAND + 1) << "." << WER::WEREXT << "." << Common::SYSEXT;

	string outRND = ssOut.str();
	string reportWER = ssReport.str();
	string toolWER = "perl "+Config::tools+"/"+WER::TWER;

	if (Config::verbose) fprintf(stderr, "building %s...\n", reportWER.c_str());
	WER_f_create_doc(TESTBED::Hsystems[TGT], outRND);

	double maxSYS = -999999;
	vector<double> maxSEGscores;
    for (map<string, string>::const_iterator it = TESTBED::Hrefs.begin(); it != TESTBED::Hrefs.end(); ++it) {
    	string ref = it->second;
    	stringstream ssRef;
		ssRef << Common::DATA_PATH << "/" << Common::TMP << "/" << rand() % (Common::NRAND + 1) << "." << WER::WEREXT << "." << Common::REFEXT;
		string refRND = ssRef.str();

		WER_f_create_doc(ref, refRND);

		stringstream sc;
		sc << toolWER << " -s -t " << outRND << " -r " << refRND << " > " << reportWER;
		Common::execute_or_die(sc.str(), "[ERROR] probles running WER...");

		pair<double, vector<double> res = read_WER(reportWER, do_neg);

		if (maxSYS != -999999) {
			if (res.first > maxSYS) maxSYS = res.first;
		}
		else maxSYS = res.first;

		for (int i = 0; i < res.second; ++i) {
			if (i < maxSEGscores.size()) {	//defined($maxSEGscores[$i]);
				if (res.second[i] > maxSEGscores[i]) maxSEGscores[i] = res.second[i];
			}
			else maxSEGscores[i] = res.second[i];
		}

		string sysaux;
		sysaux = "rm -f " + reportWER;	system(sysaux.c_str());
		sysaux = "rm -f " + refRND;	system(sysaux.c_str());
    }
    string sysaux = "rm -f " + outRND;	system(sysaux.c_str());

	return make_pair(maxSYS, maxSEGscores);
}

void WER::doMetric(string TGT, string REF, string prefix, Scores &hOQ) {
	// description _ computes -WER score (multiple references)
	vector<string> mWER(WER::rWER.size());

	int GO, i;
	GO = i = 0;
	for (map<string, int>::const_iterator it = WER::rWER[Config::LANG].begin(); it != WER::rWER[Config::LANG].end(); ++it, ++i) {
		mWER[i] = it->first;
	}
	for (i = 0; i < mWER.size() and !GO; ++i) {
		if (Config::Hmetrics.find(mWER[i]) != Config::Hmetrics.end()) GO = 1;
	}

	cout << "WER ei!" << endl;
	if (GO) {
		cout << "GO! WER GO!" << endl;
		if (Config::verbose == 1) fprintf(stderr, "%s...\n", WER::WEREXT.c_str());
		for (i = 0; i < mWER.size() and !GO; ++i) {

			ss << Common::DATA_PATH << "/" << Common::REPORTS << "/" << TGT << "/" << REF << "/-" << WER::WEREXT << "." << Common::XMLEXT;
			string reportWERxml = ss.string();
		    boost::filesystem::path reportWERxml_path(reportWERxml);
	   		boost::filesystem::path reportWERxml_gz(reportWERxml + "." + Common::GZEXT);

	   		if ( (!exists(reportWERxml_path) and !exists(reportWERxml_gz)) or Config::remake) {
	    		pair<double, vector<double> > res = computeWER(TGT, 1);
				pair<vector<double>, vector<double> > doc_seg =  Core::get_seg_doc_scores(res.second, 0, TGT);
				if (Config::O_STORAGE == 1) {
		    		IQXML::write_report(TGT, REF, "-WER", res.first, doc_seg.first, doc_seg.second);
	         		cout << "IQXML DOCUMENT -WER CREATED" << endl;
	         	}
	         	hOQ.save_hash_scores("-WER", TGT, REF, res.first, doc_seg.first, doc_seg.second);
	   		}

			ss << Common::DATA_PATH << "/" << Common::REPORTS << "/" << TGT << "/" << REF << "/" << WER::WEREXT << "." << Common::XMLEXT;
			reportWERxml = ss.string();
		    reportWERxml_path(reportWERxml);
	   		reportWERxml_gz(reportWERxml + "." + Common::GZEXT);

	   		if ( (!exists(reportWERxml_path) and !exists(reportWERxml_gz)) or Config::remake) {
	    		pair<double, vector<double> > res = computeWER(TGT, 0);
				pair<vector<double>, vector<double> > doc_seg =  Core::get_seg_doc_scores(res.second, 0, TGT);
				SC_ASIYA sc_asiya;
				if (Config::O_STORAGE == 1) {
		    		sc_asiya.write_report(TGT, REF, "WER", res.first, doc_seg.first, doc_seg.second);
	         		cout << "IQXML DOCUMENT WER CREATED" << endl;
	         	}
	         	hOQ.save_hash_scores("WER", TGT, REF, res.first, doc_seg.first, doc_seg.second);
	   		}

		}
	}
}
