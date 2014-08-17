#include "NIST.hpp"
#include "Core.hpp"
#include "Common.hpp"
#include "Config.hpp"
#include "NISTXML.hpp"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <iostream>
#include <fstream>
#include <sstream>

#include <boost/regex.hpp>
#include <boost/filesystem.hpp>
#include <boost/algorithm/string.hpp>


const string NIST::NISTEXT = "NIST";
const string NIST::NISTEXTi = "NISTi";
const string NIST::TNIST = "mteval-kit";

map<string, int> NIST::create_rNIST() {
	map<string, int> rNIST;
	string aux;
	aux = NIST::NISTEXT + "-1";		rNIST[aux] = 1;
	aux = NIST::NISTEXT + "-2";		rNIST[aux] = 1;
	aux = NIST::NISTEXT + "-3";		rNIST[aux] = 1;
	aux = NIST::NISTEXT + "-4";		rNIST[aux] = 1;
	aux = NIST::NISTEXT + "-5";		rNIST[aux] = 1;
	aux = NIST::NISTEXTi + "-2";		rNIST[aux] = 1;
	aux = NIST::NISTEXTi + "-3";		rNIST[aux] = 1;
	aux = NIST::NISTEXTi + "-4";		rNIST[aux] = 1;
	aux = NIST::NISTEXTi + "-5";		rNIST[aux] = 1;
	return rNIST;
}
const map<string, int> NIST::rNIST = create_rNIST();

vector<double> NIST::read_nist(string reportNIST) {
	// description _ read NIST value from report file

    boost::regex re("^ +NIST:.*");

    string str;
    bool individual = false;
    vector<double> lnist(5), lnisti(5);
    ifstream file(reportNIST.c_str());
    if (file) {
	    while (getline(file, str)) {
	    	boost::match_results<string::const_iterator> results;
	        if (boost::regex_match(str, results, re)) {
	            cout << "\t That was a kind of line" << endl;
	            string s = results[0];
	            cout << "line: |" << s << "|" << endl;

				boost::regex re2("^\\s+NIST:\\s+");	//, boost::regex::perl|boost::regex::icase);
				s = boost::regex_replace(s, re2, "2");

				cout << "\tline1: " << s << endl;

	            istringstream iss(s);
				double value;
				for (int i = 0; i < 5; ++i) {
					iss >> value;
					if (individual) lnist[i] = value;
					else lnisti[i] = value;
				}
				individual = true;
	        }
	    }
        file.close();
    } else { fprintf(stderr, "couldn't open file: %s\n", reportNIST.c_str()); exit(1); }

	    for (int i = 0; i < 5; ++i) cout << "lnist[" << i << "]: " << lnist[i] << endl;
	    for (int i = 0; i < 5; ++i) cout << "lnisti[" << i << "]: " << lnisti[i] << endl;

    vector<double> l(0);
    l.insert(l.begin(), lnist.begin(), lnist.end());
	    cout << "l after first insertion: ";
	    for (int i = 0; i < l.size(); ++i) cout << l[i] << ", ";
	    cout << endl;

    l.insert(l.begin() + 5, lnisti.begin(), lnisti.end());
	    cout << "l after second insertion: ";
	    for (int i = 0; i < l.size(); ++i) cout << l[i] << ", ";
	    cout << endl;

	return l;
}

vector<vector<double> > NIST::read_nist_segments(string reportNIST) {
	// description _ read NIST-5 value from report file (for all segments)

    boost::regex re1("^ +NIST score using.*");
    boost::regex re2("^ +cumulative-NIST score using.*");
    boost::regex re3("^ +individual-NIST score using.*");

    vector<double> lnist1, lnist2, lnist3, lnist4, lnist5;
    vector<double> lnist1i, lnist2i, lnist3i, lnist4i, lnist5i;

    vector<vector<double> > SEG(10);

    string str;
    ifstream file("reportNIST.txt");
    if (file) {
	    while (getline(file, str)) {
	    	boost::match_results<string::const_iterator> results;

	        if (boost::regex_match(str, results, re1)) {
	            cout << "\t That was a kind of line" << endl;
	            string s = results[0];
	            cout << "line: |" << s << "|" << endl;

				vector<string> strs;
				boost::split(strs, s, boost::is_any_of("\t "));
				lnist1.push_back(atof(strs[7].c_str()));
				lnist2.push_back(atof(strs[8].c_str()));
				lnist3.push_back(atof(strs[9].c_str()));
				lnist4.push_back(atof(strs[10].c_str()));
				lnist5.push_back(atof(strs[11].c_str()));

	   			//for (int i = 0; i < strs.size(); ++i) cout << "strs[" << i << "]: " << strs[i] << endl;
			}
			else if (boost::regex_match(str, results, re2)) {
	            cout << "\t That was a kind of line" << endl;
	            string s = results[0];
	            cout << "line: |" << s << "|" << endl;

				vector<string> strs;
				boost::split(strs, s, boost::is_any_of("\t "));
				lnist1.push_back(atof(strs[7].c_str()));
				lnist2.push_back(atof(strs[8].c_str()));
				lnist3.push_back(atof(strs[9].c_str()));
				lnist4.push_back(atof(strs[10].c_str()));
				lnist5.push_back(atof(strs[11].c_str()));

	   			//for (int i = 0; i < strs.size(); ++i) cout << "strs[" << i << "]: " << strs[i] << endl;
			}
			else if (boost::regex_match(str, results, re3)) {
	            cout << "\t That was a kind of line" << endl;
	            string s = results[0];
	            cout << "line: |" << s << "|" << endl;

				vector<string> strs;
	            boost::split(strs, s, boost::is_any_of("\t "));
				lnist1i.push_back(atof(strs[7].c_str()));
				lnist2i.push_back(atof(strs[8].c_str()));
				lnist3i.push_back(atof(strs[9].c_str()));
				lnist4i.push_back(atof(strs[10].c_str()));
				lnist5i.push_back(atof(strs[11].c_str()));

	   			//for (int i = 0; i < strs.size(); ++i) cout << "strs[" << i << "]: " << strs[i] << endl;
			}
	    }
        file.close();
        SEG[0] = lnist1;	SEG[1] = lnist2;	SEG[2] = lnist3;	SEG[3] = lnist4;	SEG[4] = lnist5;
        SEG[5] = lnist1i;	SEG[6] = lnist2i;	SEG[7] = lnist3i;	SEG[8] = lnist4i;	SEG[9] = lnist5i;

	} else { fprintf(stderr, "couldn't open file: reportNIST.txt\n"); exit(1); }

		cout << "--------------------SEG-----------------" << endl;
		for (int i = 0; i < SEG.size(); ++i) {
			for (int j = 0; j < SEG[i].size(); ++j) {
				cout << "SEG[" << i << "," << j << "]: " << SEG[i][j] << "\t";
			}
			cout << endl;
		}

	return SEG;
}

pair<vector<double>, vector<vector<double> > > NIST::computeNIST(string TGT) {
	// description _ computes NIST score (by calling NIST mteval script) -> n = 1..4 (multiple references)

	stringstream tNIST;

	tNIST << "perl " << Config::tools << "/" << NIST::TNIST << "/" << "mteval-v13a.pl -n -d 2 ";

	if (Config::CASE == Common::CASE_CS) tNIST << "-c "; //toolBLEU += "-c ";
	string toolNIST = tNIST.str();

	cout << "toolNIST ->" << toolNIST << endl << endl;

	srand(time(NULL));
	//double nr = rand() % (Common::NRAND + 1);	//random number [0, Common::NRAND];
	stringstream ssRef, ssSrc, ssOut, ssReport;
	ssRef << Common::DATA_PATH << "/" << Common::TMP << "/" << rand() % (Common::NRAND + 1) << "." << Common::REFEXT << "." << NIST::NISTEXT << "." << Common::SGMLEXT;
	ssSrc << Common::DATA_PATH << "/" << Common::TMP << "/" << rand() % (Common::NRAND + 1) << "." << Common::SRCEXT << "." << NIST::NISTEXT << "." << Common::SGMLEXT;
	ssOut << Common::DATA_PATH << "/" << Common::TMP << "/" << rand() % (Common::NRAND + 1) << "." << Common::SYSEXT << "." << NIST::NISTEXT << "." << Common::SGMLEXT;
	ssReport << Common::DATA_PATH << "/" << Common::TMP << "/" << rand() % (Common::NRAND + 1) << "." << NIST::NISTEXT << "." << Common::REPORTEXT;

    boost::filesystem::path refNISTsgml(ssRef.str());
    boost::filesystem::path srcNISTsgml(ssSrc.str());
    boost::filesystem::path outNISTsgml(ssOut.str());
    boost::filesystem::path reportNISTsgml(ssReport.str());

	if (!exists(refNISTsgml) or Config::remake) NISTXML::SGML_f_create_mteval_multidoc(refNISTsgml.string(), 2);
	if (!exists(srcNISTsgml) or Config::remake) NISTXML::SGML_f_create_mteval_doc(Config::src, srcNISTsgml.string(), 0);
	if (!exists(outNISTsgml) or Config::remake) NISTXML::SGML_f_create_mteval_doc(Config::Hsystems[TGT], outNISTsgml.string(), 1);

	if (Config::verbose > 1) fprintf(stderr, "building %s\n", reportNISTsgml.string().c_str());

    stringstream sc;// = tNIST;
    sc << toolNIST << " -s " << ssSrc.str() << " -t " << ssOut.str() << " -r " << ssRef.str() << " > " << ssReport.str();

    string ms = "[ERROR] problems running NIST...";
	Common::execute_or_die(sc.str(), ms);

	if (exists(srcNISTsgml)) {
		string sysaux = "rm -f "; sysaux += ssSrc.str();
		system (sysaux.c_str());
	}
	if (exists(refNISTsgml)) {
		string sysaux = "rm -f "; sysaux += ssRef.str();
		system (sysaux.c_str());
	}
	if (exists(outNISTsgml)) {
		string sysaux = "rm -f "; sysaux += ssOut.str();
		system (sysaux.c_str());
	}

	vector<double> SYS = read_nist(ssReport.str());
	vector<vector<double> > SEG; //= read_NIST_segments(ssReport.str());

	return make_pair(SYS, SEG);
}


void NIST::doMetric(string TGT, string REF, string prefix, Scores &hOQ) {
   // description _ computes NIST score (by calling NIST mteval script) -> n = 1..4 (multiple references)

	map<string, int> M = Config::Hmetrics;
	vector<string> mNIST(M.size());

	int GO , i;
	GO = i = 0;
	for (map<string, int>::const_iterator it = NIST::rNIST.begin(); it != NIST::rNIST.end(); ++it) mNIST[i++] = it->first;

	i = 0;
	while (i < mNIST.size() and !GO) {
		string aux = prefix; aux += mNIST[i];
		if (M.find(aux) != M.end()) { GO = 1; }
		++i;
	}

	if (GO) {
		if (Config::verbose == 1) fprintf(stderr, "%s\n", NIST::NISTEXT.c_str());
		stringstream ss1, ss2, ss3, ss4, ss5, ss2i, ss3i, ss4i, ss5i;
		ss1 << Common::DATA_PATH << "/" << Common::REPORTS << "/" << TGT << "/" << REF << prefix << NIST::NISTEXT << "-1." << Common::XMLEXT;
		ss2 << Common::DATA_PATH << "/" << Common::REPORTS << "/" << TGT << "/" << REF << prefix << NIST::NISTEXT << "-2." << Common::XMLEXT;
		ss3 << Common::DATA_PATH << "/" << Common::REPORTS << "/" << TGT << "/" << REF << prefix << NIST::NISTEXT << "-3." << Common::XMLEXT;
		ss4 << Common::DATA_PATH << "/" << Common::REPORTS << "/" << TGT << "/" << REF << prefix << NIST::NISTEXT << "-4." << Common::XMLEXT;
		ss5 << Common::DATA_PATH << "/" << Common::REPORTS << "/" << TGT << "/" << REF << prefix << NIST::NISTEXT << "-5." << Common::XMLEXT;
		ss2i << Common::DATA_PATH << "/" << Common::REPORTS << "/" << TGT << "/" << REF << prefix << NIST::NISTEXTi << "-2." << Common::XMLEXT;
		ss3i << Common::DATA_PATH << "/" << Common::REPORTS << "/" << TGT << "/" << REF << prefix << NIST::NISTEXTi << "-3." << Common::XMLEXT;
		ss4i << Common::DATA_PATH << "/" << Common::REPORTS << "/" << TGT << "/" << REF << prefix << NIST::NISTEXTi << "-4." << Common::XMLEXT;
		ss5i << Common::DATA_PATH << "/" << Common::REPORTS << "/" << TGT << "/" << REF << prefix << NIST::NISTEXTi << "-5." << Common::XMLEXT;

		string reportNIST1xml = ss1.str();
		string reportNIST2xml = ss2.str();
		string reportNIST3xml = ss3.str();
		string reportNIST4xml = ss4.str();
		string reportNIST5xml = ss5.str();
		string reportNISTi2xml = ss2i.str();
		string reportNISTi3xml = ss3i.str();
		string reportNISTi4xml = ss4i.str();
		string reportNISTi5xml = ss5i.str();

	    boost::filesystem::path reportNIST1xml_path(reportNIST1xml);
		boost::filesystem::path reportNIST2xml_path(reportNIST2xml);
	    boost::filesystem::path reportNIST3xml_path(reportNIST3xml);
	    boost::filesystem::path reportNIST4xml_path(reportNIST4xml);
	    boost::filesystem::path reportNIST5xml_path(reportNIST5xml);
	    boost::filesystem::path reportNISTi2xml_path(reportNISTi2xml);
	    boost::filesystem::path reportNISTi3xml_path(reportNISTi3xml);
	    boost::filesystem::path reportNISTi4xml_path(reportNISTi4xml);
	    boost::filesystem::path reportNISTi5xml_path(reportNISTi5xml);

		boost::filesystem::path reportNIST1xml_ext(reportNIST1xml + "." + Common::GZEXT);
	    boost::filesystem::path reportNIST2xml_ext(reportNIST2xml + "." + Common::GZEXT);
	    boost::filesystem::path reportNIST3xml_ext(reportNIST3xml + "." + Common::GZEXT);
	    boost::filesystem::path reportNIST4xml_ext(reportNIST4xml + "." + Common::GZEXT);
	    boost::filesystem::path reportNIST5xml_ext(reportNIST5xml + "." + Common::GZEXT);

	    boost::filesystem::path reportNISTi2xml_ext(reportNISTi2xml + "." + Common::GZEXT);
	    boost::filesystem::path reportNISTi3xml_ext(reportNISTi3xml + "." + Common::GZEXT);
	    boost::filesystem::path reportNISTi4xml_ext(reportNISTi4xml + "." + Common::GZEXT);
		boost::filesystem::path reportNISTi5xml_ext(reportNISTi5xml + "." + Common::GZEXT);


	    if ( (!exists(reportNIST1xml_path) and !exists(reportNIST1xml_ext)) or \
	    (!exists(reportNIST2xml_path) and !exists(reportNIST2xml_ext)) or \
	    (!exists(reportNIST3xml_path) and !exists(reportNIST3xml_ext)) or \
	    (!exists(reportNIST4xml_path) and !exists(reportNIST4xml_ext)) or \
	    (!exists(reportNIST5xml_path) and !exists(reportNIST5xml_ext)) or \
	    (!exists(reportNISTi2xml_path) and !exists(reportNISTi2xml_ext)) or \
	    (!exists(reportNISTi3xml_path) and !exists(reportNISTi3xml_ext)) or \
	    (!exists(reportNISTi4xml_path) and !exists(reportNISTi4xml_ext)) or \
	    (!exists(reportNISTi5xml_path) and !exists(reportNISTi5xml_ext)) or Config::remake) {
			//my ($SYS, $SEGS) = NIST::computeMultiNIST($src, $out, $Href, $remakeREPORTS, $config->{CASE}, $tools, $verbose, $hOQ );

	    	pair<vector<double>, vector<vector<double> > > res = computeNIST(TGT);
/*
			pair<vector<double>, vector<double> > doc_seg =  Core::get_seg_doc_scores(res.second[0], 0, TGT);
         	//if (Config::O_STORAGE == 1) IQXML::write_report();
         	string prefBE1 = prefix;	prefBE1 += BLEU::BLEUEXT;	prefBE1 += "-1";
	    	hOQ.save_hash_scores(prefBE1, TGT, REF, res.first[0], doc_seg.first, doc_seg.second);


			doc_seg = Core::get_seg_doc_scores(res.second[1], 0, TGT);
         	//if (Config::O_STORAGE == 1) IQXML::write_report();
	    	string prefBE2 = prefix;	prefBE1 += BLEU::BLEUEXT;	prefBE1 += "-2";
	    	hOQ.save_hash_scores(prefBE1, TGT, REF, res.first[1], doc_seg.first, doc_seg.second);

	    	hOQ.print_scores();
	    	exit(1);*/
	    }

	}

}
