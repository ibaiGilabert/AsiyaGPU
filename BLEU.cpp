#include "BLEU.hpp"
#include "Common.hpp"
#include "NISTXML.hpp"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <iostream>
#include <fstream>

#include <boost/regex.hpp>
#include <boost/filesystem.hpp>
#include <boost/algorithm/string.hpp>


const string BLEU::BLEUEXT = "BLEU";
const string BLEU::BLEUEXTi = "BLEUi";
const string BLEU::TBLEU = "mteval-kit";
map<string, int> create_rBLEU() {
	map<string, int> rBLEU;
	string aux;
	aux = BLEU::BLEUEXT + "-1";		rBLEU[aux] = 1;
	aux = BLEU::BLEUEXT + "-2";		rBLEU[aux] = 1;
	aux = BLEU::BLEUEXT + "-3";		rBLEU[aux] = 1;
	aux = BLEU::BLEUEXT + "-4";		rBLEU[aux] = 1;
	aux = BLEU::BLEUEXTi + "-2";		rBLEU[aux] = 1;
	aux = BLEU::BLEUEXTi + "-3";		rBLEU[aux] = 1;
	aux = BLEU::BLEUEXTi + "-4";		rBLEU[aux] = 1;
	return rBLEU;
}
const map<string, int> rBLEU = create_rBLEU();

vector<double> BLEU::read_bleu(string reportBLEU) {
	// description _ read BLEU value from report file

    boost::regex re("^ +BLEU:.*");

    string str;
    bool individual = false;
    vector<double> lbleu(4), lbleui(4);
    ifstream file(reportBLEU);
    if (file) {
	    while (getline(file, str)) {
	    	boost::match_results<string::const_iterator> results;
	        if (boost::regex_match(str, results, re)) {
	            cout << "\t That was a kind of line" << endl;
	            string s = results[0];
	            cout << "line: |" << s << "|" << endl;

				boost::regex re2("^\\s+BLEU:\\s+");	//, boost::regex::perl|boost::regex::icase);
				s = boost::regex_replace(s, re2, "2");

				cout << "\tline1: " << s << endl;

	            istringstream iss(s);
				double value;
				for (int i = 0; i < 4; ++i) {
					iss >> value;
					if (individual) lbleu[i] = value;
					else lbleui[i] = value;
				}
				individual = true;
	        }
	    }
        file.close();
    } else { fprintf(stderr, "couldn't open file: %s\n", reportBLEU); exit(1); }

	    for (int i = 0; i < 4; ++i) cout << "lbleu[" << i << "]: " << lbleu[i] << endl;
	    for (int i = 0; i < 4; ++i) cout << "lbleui[" << i << "]: " << lbleui[i] << endl;

    vector<double> l(0);
    l.insert(l.begin(), lbleu.begin(), lbleu.end());
	    cout << "l after first insertion: ";
	    for (int i = 0; i < l.size(); ++i) cout << l[i] << ", ";
	    cout << endl;

    l.insert(l.begin() + 4, lbleui.begin(), lbleui.end());
	    cout << "l after second insertion: ";
	    for (int i = 0; i < l.size(); ++i) cout << l[i] << ", ";
	    cout << endl;

	return l;
}

vector<vector<double> > BLEU::read_bleu_segments(string reportBLEU) {
    boost::regex re1("^ +BLEU score using.*");
    boost::regex re2("^ +cumulative-BLEU score using.*");
    boost::regex re3("^ +individual-BLEU score using.*");

    vector<double> lbleu1, lbleu2, lbleu3, lbleu4;
    vector<double> lbleu1i, lbleu2i, lbleu3i, lbleu4i;

    vector<vector<double> > SEG(8);

    string str;
    ifstream file("reportBLEU.txt");
    if (file) {
	    while (getline(file, str)) {
	    	boost::match_results<string::const_iterator> results;

	        if (boost::regex_match(str, results, re1)) {
	            cout << "\t That was a kind of line" << endl;
	            string s = results[0];
	            cout << "line: |" << s << "|" << endl;

				vector<string> strs;
				boost::split(strs, s, boost::is_any_of("\t "));
				lbleu1.push_back(atof(strs[7].c_str()));
				lbleu2.push_back(atof(strs[8].c_str()));
				lbleu3.push_back(atof(strs[9].c_str()));
				lbleu4.push_back(atof(strs[10].c_str()));
	   			//for (int i = 0; i < strs.size(); ++i) cout << "strs[" << i << "]: " << strs[i] << endl;
			}
			else if (boost::regex_match(str, results, re2)) {
	            cout << "\t That was a kind of line" << endl;
	            string s = results[0];
	            cout << "line: |" << s << "|" << endl;

				vector<string> strs;
				boost::split(strs, s, boost::is_any_of("\t "));
				lbleu1.push_back(atof(strs[7].c_str()));
				lbleu2.push_back(atof(strs[8].c_str()));
				lbleu3.push_back(atof(strs[9].c_str()));
				lbleu4.push_back(atof(strs[10].c_str()));
	   			//for (int i = 0; i < strs.size(); ++i) cout << "strs[" << i << "]: " << strs[i] << endl;
			}
			else if (boost::regex_match(str, results, re3)) {
	            cout << "\t That was a kind of line" << endl;
	            string s = results[0];
	            cout << "line: |" << s << "|" << endl;

				vector<string> strs;
	            boost::split(strs, s, boost::is_any_of("\t "));
				lbleu1i.push_back(atof(strs[7].c_str()));
				lbleu2i.push_back(atof(strs[8].c_str()));
				lbleu3i.push_back(atof(strs[9].c_str()));
				lbleu4i.push_back(atof(strs[10].c_str()));
	   			//for (int i = 0; i < strs.size(); ++i) cout << "strs[" << i << "]: " << strs[i] << endl;
			}
	    }
        file.close();
        SEG[0] = lbleu1;	SEG[1] = lbleu2;	SEG[2] = lbleu3;	SEG[3] = lbleu4;
        SEG[4] = lbleu1i;	SEG[5] = lbleu2i;	SEG[6] = lbleu3i;	SEG[7] = lbleu4i;

	} else { fprintf(stderr, "couldn't open file: reportBLEU.txt\n"); exit(1); }

		cout << "--------------------SEG-----------------" << endl;
		for (int i = 0; i < SEG.size(); ++i) {
			for (int j = 0; j < SEG[i].size(); ++j) {
				cout << "SEG[" << i << "," << j << "]: " << SEG[i][j] << "\t";
			}
			cout << endl;
		}

	return SEG;
}


pair<vector<double>, vector<vector<double> > > BLEU::computeBLEU(string tools, string remakeREPORTS, int verbose) {
	stringstream tBLEU;
	tBLEU << "perl " << tools << "/" << BLEU::TBLEU << "/" << "mteval-v13a.pl -b -d 2 ";
	//string toolBLEU = tBLEU.str();
	if (Config::CASE == Common::CASE_CS) tBLEU << "-c "; //toolBLEU += "-c ";

	srand(time(NULL));
	//double nr = rand() % (Common::NRAND + 1);	//random number [0, Common::NRAND];
	stringstream ssRef, ssSrc, ssOut, ssReport;
	ssRef << Common::DATA_PATH << "/" << Common::TMP << "/" << rand() % (Common::NRAND + 1) << "." << Common::REFEXT << "." << BLEU::BLEUEXT << "." << Common::SGMLEXT;
	ssSrc << Common::DATA_PATH << "/" << Common::TMP << "/" << rand() % (Common::NRAND + 1) << "." << Common::SRCEXT << "." << BLEU::BLEUEXT << "." << Common::SGMLEXT;
	ssOut << Common::DATA_PATH << "/" << Common::TMP << "/" << rand() % (Common::NRAND + 1) << "." << Common::SYSEXT << "." << BLEU::BLEUEXT << "." << Common::SGMLEXT;
	ssReport << Common::DATA_PATH << "/" << Common::TMP << "/" << rand() % (Common::NRAND + 1) << "." << BLEU::BLEUEXT << "." << Common::REPORTEXT;

    boost::filesystem::path refBLEUsgml(ssRef.str()));
    boost::filesystem::path srcBLEUsgml(ssSrc.str()));
    boost::filesystem::path outBLEUsgml(ssOut.str()));
    boost::filesystem::path reportBLEUsgml(ssReport.str()));

	if (!exists(refBLEUsgml) or remakeREPORTS) NISTXML::SGML_f_create_mteval_multidoc(refBLEUsgml.string(), 2, $verbose);
	if (!exists(srcBLEUsgml) or remakeREPORTS) NISTXML::SGML_f_create_mteval_multidoc(refBLEUsgml.string(), 0, $verbose);
	if (!exists(refBLEUsgml) or remakeREPORTS) NISTXML::SGML_f_create_mteval_multidoc(refBLEUsgml.string(), 1, $verbose);
	if (verbose > 1) fprintf(stderr, "building %s\n", reportBLEUsgml.string().c_str());

    stringstream sc;
    sc << toolBLEU << " -s " << ssSrc.str() << " -t " << ssOut.str() << " -r " << ssRef.str() << " > " << ssReport.str();
    string ms = "[ERROR] problems running BLEU...";
	Common::execute_or_die(sc.str(), ms);

	if (exists(srcBLEUsgml)) {
		string sysaux = "rm -f "; sysaux += ssSrc.str();
		system (sysaux.c_str());
	}
	if (exists(refBLEUsgml)) {
		string sysaux = "rm -f "; sysaux += ssRef.str();
		system (sysaux.c_str());
	}
	if (exists(outBLEUsgml)) {
		string sysaux = "rm -f "; sysaux += ssOut.str();
		system (sysaux.c_str());
	}

	vector<double> SYS = read_bleu(ssReport.str());
	vector<vector<double> > SEG = read_bleu_segments(ssReport.str());

	return make_pair(SYS, SEG);
}


void BLEU::doMetric(string TGT, string REF, string prefix, map<string, double> &hOQ) {
   // description _ computes BLEU score (by calling NIST mteval script) -> n = 1..4 (multiple references)
	string src = Config::src;
	int remakeREPORTS = Config::remake;
	string tools = Config::tools;
	map<string, int> M = Config::Hmetrics;
	int verbose = Config::verbose;

	int GO = 0;
	int i = 0;
	set<string> mBLEU;
	for (map<string, int>::const_iterator it = BLEU::rBLEU.begin(); it != rBLEU.end(); ++it) {
		mBLEU.insert(it->first);
	}
	while (i < mBLEU.size() and !GO) {
		string aux = prefix; aux += $mBLEU[i];
		if (M.find(aux) != M.end()) { GO = 1; }
		++i;
	}

	if (GO) {
		if (verbose == 1) fprintf(stderr, "%s\n", BLEU::BLEUEXT);
		stringstream ss1, ss2, ss3, ss4, ss2i, ss3i, ss4i;
		ss1 << Common::DATA_PATH << "/" << Common::REPORTS << "/" << TGT << "/" << REF << prefix << BLEU::BLEUEXT << "-1." << Common::XMLEXT;
		ss2 << Common::DATA_PATH << "/" << Common::REPORTS << "/" << TGT << "/" << REF << prefix << BLEU::BLEUEXT << "-2." << Common::XMLEXT;
		ss3 << Common::DATA_PATH << "/" << Common::REPORTS << "/" << TGT << "/" << REF << prefix << BLEU::BLEUEXT << "-3." << Common::XMLEXT;
		ss4 << Common::DATA_PATH << "/" << Common::REPORTS << "/" << TGT << "/" << REF << prefix << BLEU::BLEUEXT << "-4." << Common::XMLEXT;
		ss2i << Common::DATA_PATH << "/" << Common::REPORTS << "/" << TGT << "/" << REF << prefix << BLEU::BLEUEXTi << "-2." << Common::XMLEXT;
		ss3i << Common::DATA_PATH << "/" << Common::REPORTS << "/" << TGT << "/" << REF << prefix << BLEU::BLEUEXTi << "-3." << Common::XMLEXT;
		ss4i << Common::DATA_PATH << "/" << Common::REPORTS << "/" << TGT << "/" << REF << prefix << BLEU::BLEUEXTi << "-4." << Common::XMLEXT;

		string reportBLEU1xml = ss1.str();
		string reportBLEU2xml = ss2.str();
		string reportBLEU3xml = ss3.str();
		string reportBLEU4xml = ss4.str();
		string reportBLEUi2xml = ss2i.str();
		string reportBLEUi3xml = ss3i.str();
		string reportBLEUi4xml = ss4i.str();

	    boost::filesystem::path reportBLEU1xml_path(reportBLEU1xml);
		boost::filesystem::path reportBLEU2xml_pathreportBLEU1xml);
	    boost::filesystem::path reportBLEU3xml_path(reportBLEU1xml);
	    boost::filesystem::path reportBLEU4xml_path(reportBLEU1xml);
	    boost::filesystem::path reportBLEU2ixml_path(reportBLEU1xml);
	    boost::filesystem::path reportBLEU3ixml_path(reportBLEU1xml);
	    boost::filesystem::path reportBLEU4ixml_path(reportBLEU1xml);
		boost::filesystem::path reportBLEU1xml_ext(reportBLEU1xml + "." + Common::CZEXT);
	    boost::filesystem::path reportBLEU1xml_ext(reportBLEU1xml + "." + Common::CZEXT);
	    boost::filesystem::path reportBLEU1xml_ext(reportBLEU1xml + "." + Common::CZEXT);
	    boost::filesystem::path reportBLEU1xml_ext(reportBLEU1xml + "." + Common::CZEXT);
	    boost::filesystem::path reportBLEU1xml_ext(reportBLEU1xml + "." + Common::CZEXT);
	    boost::filesystem::path reportBLEU1xml_ext(reportBLEU1xml + "." + Common::CZEXT);
	    boost::filesystem::path reportBLEU1xml_ext(reportBLEU1xml + "." + Common::CZEXT);


	    if ( (!exists(reportBLEU1xml_path) and !exists(reportBLEU1xml_ext)) or \
	    (!exists(reportBLEU2xml_path) and !exists(reportBLEU2xml_ext)) or \
	    (!exists(reportBLEU3xml_path) and !exists(reportBLEU3xml_ext)) or \
	    (!exists(reportBLEU4xml_path) and !exists(reportBLEU4xml_ext)) or \
	    (!exists(reportBLEU2ixml_path) and !exists(reportBLEU2ixml_ext)) or \
	    (!exists(reportBLEU3ixml_path) and !exists(reportBLEU3ixml_ext)) or \
	    (!exists(reportBLEU4ixml_path) and !exists(reportBLEU4ixml_ext)) or remakeREPORTS) {
	     	//my ($SYS, $SEGS) = BLEU::computeMultiBLEU($src, $out, $Href, $remakeREPORTS, $config->{CASE}, $tools, $verbose);
	    	pair<vector<double>, vector<vector<double> > > res = computeBLEU(tools, remakeREPORTS, verbose);


	    	string prefBE1 = prefix;	prefBE1 += BLEU::BLEUEXT;	prefBE1 += "-1";
	    	Scores::save_hash_scores(prefBE1, TGT, REF, res->first[0], doc_scores, seg_scores, hOQ);
	    }

	}

}
