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

map<string, int> GTM::create_rGTM() {
	map<string, int> rGTM;
	rGTM[GTM::GTMEXT + "-1"] = 1;
	rGTM[GTM::GTMEXT + "-2"] = 1;
	rGTM[GTM::GTMEXT + "-3"] = 1;
	return rGTM;
}
const map<string, int> GTM::rGTM = create_rGTM();


double GTM::read_GTM(string reportGTM) {
	// description _ read GTM value from report file
	vector<string> GTM;
	ifstream file(reportGTM.c_str());
    if (file) {
    	string str;
	    //while (getline(file, str)) {
		getline(file, str);
        istringstream iss(str);
	    for(std::string token; getline(iss, token, ' '); ) GTM.push_back(token);
	    //}
        file.close();
    } else { fprintf(stderr, "couldn't open input file: %s\n", reportGTM.c_str()); exit(1); }

    return atof(GTM[1].c_str());
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


pair<double, vector<double> > GTM::computeGTM(string TGT, int e) {
	stringstream tGTM;
	// description _ computes GTM scores -> n = 1..4, LCS, S*, SU*, W-1.2 (multiple references)
	tGTM << "java -Dfile.encoding=UTF-8 -jar " << Config::tools << "/" << GTM::TGTM << "/gtm.jar +s +d";
	string toolGTM = tGTM.str();
	cout << "toolGTM ->" << toolGTM << endl << endl;

	srand(time(NULL));
	vector<string> LrefTGMsgml;
	for (map<string, string>::const_iterator it = TESTBED::Hrefs.begin(); it != TESTBED::Hrefs.end(); ++it) {
		string ref = it->second;

		stringstream ssRef;
		ssRef << Common::DATA_PATH << "/" << Common::TMP << "/" << rand() % (Common::NRAND + 1) << "." << Common::REFEXT << "." <<  GTM::GTMEXT << "." << Common::SGMLEXT;
		string refGTMsgml = ssRef.str();
 	    boost::filesystem::path ref_path(refGTMsgml);

		if (!exists(ref_path) or Config::remake) {
			TB_NIST::SGML_GTM_f_create_mteval_doc(ref, refGTMsgml);
		}
		LrefTGMsgml.push_back(refGTMsgml);
	}

	stringstream ssOut, ssReport;
	ssOut << Common::DATA_PATH << "/" << Common::TMP << "/" << rand() % (Common::NRAND + 1) << "." << Common::SYSEXT << "." <<  GTM::GTMEXT << "." << Common::SGMLEXT;
	ssReport << Common::DATA_PATH << "/" << Common::TMP << "/" << rand() % (Common::NRAND + 1) << "." << GTM::GTMEXT << "-" << e << "." << Common::REPORTEXT;

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

	double SYS = read_GTM(reportGTM);
	vector<double> SEG = read_GTM_segments(reportGTM);

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

	return make_pair(SYS, SEG);
}

void GTM::doMetric(string TGT, string REF, string prefix, Scores &hOQ) {
	// description _ computes GTM F1 (by calling Proteus java gtm) -> e = 1..3 (multiple references)
	vector<string> mGTM(GTM::rGTM.size());

	int GO, i;
	GO = i = 0;
	for (map<string, int>::const_iterator it = GTM::rGTM.begin(); it != GTM::rGTM.end(); ++it, ++i) {
		mGTM[i] = it->first;
	}
	for (i = 0; i < mGTM.size() and !GO; ++i) {
		string aux = prefix + mGTM[i];
		if (Config::Hmetrics.find(aux) != Config::Hmetrics.end()) GO = 1;
	}

	cout << "GTM ei!" << endl;
	if (GO) {
		cout << "GO! GTM GO!" << endl;
		if (Config::verbose == 1) fprintf(stderr, "%s\n", GTM::GTMEXT.c_str());
		stringstream ss1, ss2, ss3;
		ss1 << Common::DATA_PATH << "/" << Common::REPORTS << "/" << TGT << "/" << REF << prefix << GTM::GTMEXT << "-1." << Common::XMLEXT;
		ss2 << Common::DATA_PATH << "/" << Common::REPORTS << "/" << TGT << "/" << REF << prefix << GTM::GTMEXT << "-2." << Common::XMLEXT;
		ss3 << Common::DATA_PATH << "/" << Common::REPORTS << "/" << TGT << "/" << REF << prefix << GTM::GTMEXT << "-3." << Common::XMLEXT;

		string reportGTM1xml = ss1.str();
		string reportGTM2xml = ss2.str();
		string reportGTM3xml = ss3.str();

	    boost::filesystem::path reportGTM1xml_path(reportGTM1xml);
		boost::filesystem::path reportGTM2xml_path(reportGTM2xml);
	    boost::filesystem::path reportGTM3xml_path(reportGTM3xml);

	    boost::filesystem::path reportGTM1xml_gz(reportGTM1xml + "." + Common::GZEXT);
		boost::filesystem::path reportGTM2xml_gz(reportGTM2xml + "." + Common::GZEXT);
	    boost::filesystem::path reportGTM3xml_gz(reportGTM3xml + "." + Common::GZEXT);

	    SC_ASIYA sc_asiya;
	    if ( (!exists(reportGTM1xml_path) and !exists(reportGTM1xml_gz)) or Config::remake) {
	    	pair<double, vector<double> > res = computeGTM(TGT, 1);

         	string prefG = prefix + GTM::GTMEXT + "-1";
			pair<vector<double>, vector<double> > doc_seg =  TESTBED::get_seg_doc_scores(res.second, 0, TGT);

	    	if (Config::O_STORAGE == 1) {
	    		sc_asiya.write_report(TGT, REF, prefG, res.first, doc_seg.first, doc_seg.second);
         		cout << "IQXML DOCUMENT " << prefG << " CREATED" << endl;
         	}
         	hOQ.save_hash_scores(prefG, TGT, REF, res.first, doc_seg.first, doc_seg.second);
	    }
		if ( (!exists(reportGTM2xml_path) and !exists(reportGTM2xml_gz)) or Config::remake) {
	    	pair<double, vector<double> > res = computeGTM(TGT, 2);

			string prefG = prefix + GTM::GTMEXT + "-2";
			pair<vector<double>, vector<double> > doc_seg = TESTBED::get_seg_doc_scores(res.second, 0, TGT);
         	if (Config::O_STORAGE == 1) {
	    		sc_asiya.write_report(TGT, REF, prefG, res.first, doc_seg.first, doc_seg.second);
         		cout << "IQXML DOCUMENT " << prefG << " CREATED" << endl;
         	}
	    	hOQ.save_hash_scores(prefG, TGT, REF, res.first, doc_seg.first, doc_seg.second);
		}
	    if ( (!exists(reportGTM3xml_path) and !exists(reportGTM3xml_gz)) or Config::remake) {
	    	pair<double, vector<double> > res = computeGTM(TGT, 3);

	    	string prefG = prefix + GTM::GTMEXT + "-3";
			pair<vector<double>, vector<double> > doc_seg = TESTBED::get_seg_doc_scores(res.second, 0, TGT);
         	if (Config::O_STORAGE == 1) {
	    		sc_asiya.write_report(TGT, REF, prefG, res.first, doc_seg.first, doc_seg.second);
         		cout << "IQXML DOCUMENT " << prefG << " CREATED" << endl;
         	}
         	hOQ.save_hash_scores(prefG, TGT, REF, res.first, doc_seg.first, doc_seg.second);
		}
	}
}
