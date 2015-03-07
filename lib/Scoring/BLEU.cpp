#include "../include/BLEU.hpp"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <iostream>
#include <fstream>
#include <sstream>

#include <boost/regex.hpp>
#include <boost/filesystem.hpp>
#include <boost/algorithm/string.hpp>


const string BLEU::BLEUEXT = "BLEU";
const string BLEU::BLEUEXTi = "BLEUi";
const string BLEU::TBLEU = "mteval-kit";

map<string, int> BLEU::create_rBLEU() {
	map<string, int> rBLEU;
	rBLEU[BLEU::BLEUEXT] = 1;
	rBLEU[BLEU::BLEUEXT + "-1"] = 1;
	rBLEU[BLEU::BLEUEXT + "-2"] = 1;
	rBLEU[BLEU::BLEUEXT + "-3"] = 1;
	rBLEU[BLEU::BLEUEXT + "-4"] = 1;
	rBLEU[BLEU::BLEUEXTi + "-2"] = 1;
	rBLEU[BLEU::BLEUEXTi + "-3"] = 1;
	rBLEU[BLEU::BLEUEXTi + "-4"] = 1;
	return rBLEU;
}
const map<string, int> BLEU::rBLEU = create_rBLEU();


vector<double> BLEU::read_bleu(string reportBLEU) {
	// description _ read BLEU value from report file
    boost::regex re("^ +BLEU:.*");

    string str;
    bool individual = false;
    vector<double> lbleu(4), lbleui(4);
    ifstream file(reportBLEU.c_str());
    if (file) {
	    while (getline(file, str)) {
	    	boost::match_results<string::const_iterator> results;
	        if (boost::regex_match(str, results, re)) {
	            //cout << "\t That was a kind of line" << endl;
	            string s = results[0];
	            //cout << "line: |" << s << "|" << endl;

				boost::regex re2("^\\s+BLEU:\\s+");	//, boost::regex::perl|boost::regex::icase);
				s = boost::regex_replace(s, re2, "");

				//cout << "\tline1: " << s << endl;

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
    } else { fprintf(stderr, "couldn't open file: %s\n", reportBLEU.c_str()); exit(1); }
	    //for (int i = 0; i < 4; ++i) cout << "lbleu[" << i << "]: " << lbleu[i] << endl;
	    //for (int i = 0; i < 4; ++i) cout << "lbleui[" << i << "]: " << lbleui[i] << endl;

    vector<double> l(0);
    l.insert(l.begin(), lbleu.begin(), lbleu.end());
	    /*cout << "l after first insertion: ";
	    for (int i = 0; i < l.size(); ++i) cout << l[i] << ", ";
	    cout << endl;*/
    l.insert(l.begin() + 4, lbleui.begin(), lbleui.end());
	    /*cout << "l after second insertion: ";
	    for (int i = 0; i < l.size(); ++i) cout << l[i] << ", ";
	    cout << endl;*/

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
    ifstream file(reportBLEU.c_str());
    if (file) {
	    while (getline(file, str)) {
	    	boost::match_results<string::const_iterator> results;

	        if (boost::regex_match(str, results, re1)) {
	            //cout << "\t That was a kind of line" << endl;
	            string s = results[0];
	            //cout << "line: |" << s << "|" << endl;

				vector<string> strs;
				boost::split(strs, s, boost::is_any_of("\t "));
				lbleu1.push_back(atof(strs[7].c_str()));
				lbleu2.push_back(atof(strs[8].c_str()));
				lbleu3.push_back(atof(strs[9].c_str()));
				lbleu4.push_back(atof(strs[10].c_str()));
	   			//for (int i = 0; i < strs.size(); ++i) cout << "strs[" << i << "]: " << strs[i] << endl;
			}
			else if (boost::regex_match(str, results, re2)) {
	            //cout << "\t That was a kind of line" << endl;
	            string s = results[0];
	            //cout << "line: |" << s << "|" << endl;

				vector<string> strs;
				boost::split(strs, s, boost::is_any_of("\t "));
				lbleu1.push_back(atof(strs[7].c_str()));
				lbleu2.push_back(atof(strs[8].c_str()));
				lbleu3.push_back(atof(strs[9].c_str()));
				lbleu4.push_back(atof(strs[10].c_str()));
	   			//for (int i = 0; i < strs.size(); ++i) cout << "strs[" << i << "]: " << strs[i] << endl;
			}
			else if (boost::regex_match(str, results, re3)) {
	            //cout << "\t That was a kind of line" << endl;
	            string s = results[0];
	            //cout << "line: |" << s << "|" << endl;

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
		/*cout << "--------------------SEG-----------------" << endl;
		for (int i = 0; i < SEG.size(); ++i) {
			for (int j = 0; j < SEG[i].size(); ++j) {
				cout << "SEG[" << i << "," << j << "]: " << SEG[i][j] << "\t";
			}
			cout << endl;
		}*/

	return SEG;
}


void BLEU::computeBLEU(string TGT, vector<double> &SYS, vector<vector<double> > &SEG) {
	stringstream tBLEU;
	tBLEU << "perl " << Config::tools << "/" << BLEU::TBLEU << "/" << "mteval-v13a.pl -b -d 2 ";

	if (Config::CASE == Common::CASE_CS) tBLEU << "-c "; //toolBLEU += "-c ";
	string toolBLEU = tBLEU.str();
	fprintf(stderr, "toolBLEU -> %s\n", toolBLEU.c_str());

	srand(time(NULL));
	double nr = rand() % (Common::NRAND + 1);	//random number [0, Common::NRAND];
	stringstream ssRef, ssSrc, ssOut, ssReport;

	ssRef << Common::DATA_PATH << "/" << Common::TMP << "/" << nr << "." << Common::REFEXT << "." << BLEU::BLEUEXT << "." << Common::SGMLEXT;
	ssSrc << Common::DATA_PATH << "/" << Common::TMP << "/" << nr << "." << Common::SRCEXT << "." << BLEU::BLEUEXT << "." << Common::SGMLEXT;
	ssOut << Common::DATA_PATH << "/" << Common::TMP << "/" << nr << "." << Common::SYSEXT << "." << BLEU::BLEUEXT << "." << Common::SGMLEXT;
	ssReport << Common::DATA_PATH << "/" << Common::TMP << "/" << nr << "." << BLEU::BLEUEXT << "." << Common::REPORTEXT;

    boost::filesystem::path refBLEUsgml(ssRef.str());
    boost::filesystem::path srcBLEUsgml(ssSrc.str());
    boost::filesystem::path outBLEUsgml(ssOut.str());
    boost::filesystem::path reportBLEUsgml(ssReport.str());

	if (!exists(refBLEUsgml) or Config::remake) TB_NIST::SGML_f_create_mteval_multidoc(TESTBED::Hrefs, refBLEUsgml.string(), 2);
	if (!exists(srcBLEUsgml) or Config::remake) TB_NIST::SGML_f_create_mteval_doc(TESTBED::src, srcBLEUsgml.string(), 0);
	if (!exists(outBLEUsgml) or Config::remake) TB_NIST::SGML_f_create_mteval_doc(TESTBED::Hsystems[TGT], outBLEUsgml.string(), 1);

	if (Config::verbose) fprintf(stderr, "building %s\n", reportBLEUsgml.string().c_str());

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

	SYS = read_bleu(ssReport.str());
	SEG = read_bleu_segments(ssReport.str());
}

MetricScore BLEU::computeBLEUN(string TGT) {
	// description _ computes smoothed BLEU-4 score (by calling NIST mteval script) (multiple references)
	stringstream tBLEUN;
	tBLEUN << "perl " << Config::tools << "/" << BLEU::TBLEU << "/mteval-v13a.pl -b --metricsMATR -d 2 ";

	if (Config::CASE == Common::CASE_CS) tBLEUN << "-c ";
	string toolBLEUN = tBLEUN.str();

	//fprintf(stderr, "toolBLEUN ->%s\n\n", toolBLEUN.c_str());

	double nr = rand() % (Common::NRAND + 1);	//random number [0, Common::NRAND];
	stringstream ssSrc, ssOut, ssRef;
	ssSrc << Common::DATA_PATH << "/" << Common::TMP << "/" << nr << "." << Common::SRCEXT << ".NIST." << Common::XMLEXT;
	ssOut << Common::DATA_PATH << "/" << Common::TMP << "/" << nr << "." << Common::SYSEXT << ".NIST." << Common::XMLEXT;
	ssRef << Common::DATA_PATH << "/" << Common::TMP << "/" << nr << "." << Common::REFEXT << ".NIST." << Common::XMLEXT;


    boost::filesystem::path srcXML(ssSrc.str());
    boost::filesystem::path outXML(ssOut.str());
    boost::filesystem::path refXML(ssRef.str());

    if (!exists(srcXML) or Config::remake) TB_NIST::f_create_mteval_doc(TESTBED::src, srcXML.string(), TGT, Common::CASE_CS, 0);
    if (!exists(outXML) or Config::remake) TB_NIST::f_create_mteval_doc(TESTBED::Hsystems[TGT], outXML.string(), TGT, Common::CASE_CS,  1);
    if (!exists(refXML) or Config::remake) TB_NIST::f_create_mteval_multidoc(TESTBED::Hrefs, refXML.string(), Common::CASE_CS, 2);

    stringstream sc;
    sc << "cd " << Common::DATA_PATH << "; " << toolBLEUN << " -s " << ssSrc.str() << " -t " << ssOut.str() << " -r " << ssRef.str() << " >/dev/null 2>/dev/null";

    string ms = "[ERROR] problems running BLEUN...";
	Common::execute_or_die(sc.str(), ms);

	if (exists(refXML)) {
		string sysaux = "rm -f "; sysaux += ssRef.str();
		system (sysaux.c_str());
	}
	if (exists(outXML)) {
		string sysaux = "rm -f "; sysaux += ssOut.str();
		system (sysaux.c_str());
	}
	if (exists(srcXML)) {
		string sysaux = "rm -f "; sysaux += ssSrc.str();
		system (sysaux.c_str());
	}
	MetricScore BLEU_scores = Scores::read_scores(Common::DATA_PATH + "/BLEU", TGT, "-", 0);

	return BLEU_scores;
}

void BLEU::doMetric(string TGT, string REF, string prefix, Scores &hOQ) {
   // description _ computes BLEU score (by calling NIST mteval script) -> n = 1..4 (multiple references)

	//map<string, int> M = Config::Hmetrics;
	vector<string> mBLEU(BLEU::rBLEU.size());

	int GO , i;
	GO = i = 0;
	for (map<string, int>::const_iterator it = BLEU::rBLEU.begin(); it != BLEU::rBLEU.end(); ++it, ++i) {
		//mBLEU.insert(it->first);
		mBLEU[i] = it->first;
	}

	for (i = 0; i < mBLEU.size() and !GO; ++i) {
		string aux = prefix + mBLEU[i];
		if (Config::Hmetrics.find(aux) != Config::Hmetrics.end()) { GO = 1; }
	}

	if (GO) {
		if (Config::verbose) fprintf(stderr, "%s\n", BLEU::BLEUEXT.c_str());
		stringstream ss1, ss2, ss3, ss4, ss2i, ss3i, ss4i, ssB;
		ss1 << Common::DATA_PATH << "/" << Common::REPORTS << "/" << TGT << "/" << REF << "/" << prefix << BLEU::BLEUEXT << "-1." << Common::XMLEXT;
		ss2 << Common::DATA_PATH << "/" << Common::REPORTS << "/" << TGT << "/" << REF << "/" << prefix << BLEU::BLEUEXT << "-2." << Common::XMLEXT;
		ss3 << Common::DATA_PATH << "/" << Common::REPORTS << "/" << TGT << "/" << REF << "/" << prefix << BLEU::BLEUEXT << "-3." << Common::XMLEXT;
		ss4 << Common::DATA_PATH << "/" << Common::REPORTS << "/" << TGT << "/" << REF << "/" << prefix << BLEU::BLEUEXT << "-4." << Common::XMLEXT;
		ss2i << Common::DATA_PATH << "/" << Common::REPORTS << "/" << TGT << "/" << REF << "/" << prefix << BLEU::BLEUEXTi << "-2." << Common::XMLEXT;
		ss3i << Common::DATA_PATH << "/" << Common::REPORTS << "/" << TGT << "/" << REF << "/" << prefix << BLEU::BLEUEXTi << "-3." << Common::XMLEXT;
		ss4i << Common::DATA_PATH << "/" << Common::REPORTS << "/" << TGT << "/" << REF << "/" << prefix << BLEU::BLEUEXTi << "-4." << Common::XMLEXT;
		ssB << Common::DATA_PATH << "/" << Common::REPORTS << "/" << TGT << "/" << REF << "/" << prefix << BLEU::BLEUEXT << "." << Common::XMLEXT;

		string reportBLEU1xml = ss1.str();
		string reportBLEU2xml = ss2.str();
		string reportBLEU3xml = ss3.str();
		string reportBLEU4xml = ss4.str();
		string reportBLEUi2xml = ss2i.str();
		string reportBLEUi3xml = ss3i.str();
		string reportBLEUi4xml = ss4i.str();
		string reportBLEUNxml = ssB.str();

	    boost::filesystem::path reportBLEU1xml_path(reportBLEU1xml);
		boost::filesystem::path reportBLEU2xml_path(reportBLEU2xml);
	    boost::filesystem::path reportBLEU3xml_path(reportBLEU3xml);
	    boost::filesystem::path reportBLEU4xml_path(reportBLEU4xml);
	    boost::filesystem::path reportBLEUi2xml_path(reportBLEUi2xml);
	    boost::filesystem::path reportBLEUi3xml_path(reportBLEUi3xml);
	    boost::filesystem::path reportBLEUi4xml_path(reportBLEUi4xml);
	    boost::filesystem::path reportBLEUNxml_path(reportBLEUNxml);
		boost::filesystem::path reportBLEU1xml_ext(reportBLEU1xml + "." + Common::GZEXT);
	    boost::filesystem::path reportBLEU2xml_ext(reportBLEU2xml + "." + Common::GZEXT);
	    boost::filesystem::path reportBLEU3xml_ext(reportBLEU3xml + "." + Common::GZEXT);
	    boost::filesystem::path reportBLEU4xml_ext(reportBLEU4xml + "." + Common::GZEXT);
	    boost::filesystem::path reportBLEUi2xml_ext(reportBLEUi2xml + "." + Common::GZEXT);
	    boost::filesystem::path reportBLEUi3xml_ext(reportBLEUi3xml + "." + Common::GZEXT);
	    boost::filesystem::path reportBLEUi4xml_ext(reportBLEUi4xml + "." + Common::GZEXT);
	    boost::filesystem::path reportBLEUNxml_ext(reportBLEUNxml + "." + Common::GZEXT);

	    if ( (!exists(reportBLEU1xml_path) and !exists(reportBLEU1xml_ext)) or \
	    (!exists(reportBLEU2xml_path) and !exists(reportBLEU2xml_ext)) or \
	    (!exists(reportBLEU3xml_path) and !exists(reportBLEU3xml_ext)) or \
	    (!exists(reportBLEU4xml_path) and !exists(reportBLEU4xml_ext)) or \
	    (!exists(reportBLEUi2xml_path) and !exists(reportBLEUi2xml_ext)) or \
	    (!exists(reportBLEUi3xml_path) and !exists(reportBLEUi3xml_ext)) or \
	    (!exists(reportBLEUi4xml_path) and !exists(reportBLEUi4xml_ext)) or \
	    (!exists(reportBLEUNxml_path) and !exists(reportBLEUNxml_ext)) or Config::remake) {
	     	//my ($SYS, $SEGS) = BLEU::computeMultiBLEU($src, $out, $Href, $remakeREPORTS, $config->{CASE}, $tools, $verbose);
	    	vector<double> SYS;
	    	vector<vector<double> > SEG;
	    	computeBLEU(TGT, SYS, SEG);

                /*vector<double> SYS = res.first;
                vector<vector<double> > SEG = res.second;
                cout << "--------------------------------BLEU::SYS---------------------------------" << endl;
                for (int i = 0; i < SYS.size(); ++i) {
                        cout << "\tSYS[" << i << "]: " << SYS[i] << endl;
                }
                cout << "--------------------------------BLEU::SEG---------------------------------" << endl;
                for (int i = 0; i < SEG.size(); ++i) {
                        cout << "\tSEG[" << i << "]" << endl;
                        for(int j = 0; j < SEG[i].size(); ++j) {
                                cout << "\t\tSEG[" << i << "][" << j << "]: " << SEG[i][j] << endl;
                        }
                        cout << endl;
                }
                cout << "--------------------------------------------------------------------------" << endl;*/


	    	//Scores::save_hash_scores(string metric_name, string system_name, string refere_name, double sys_score, const vector<double> &doc_scores, const vector<double> &seg_scores) {

         	string prefB = prefix;	prefB += BLEU::BLEUEXT;	prefB += "-1";
			vector<double> d_scores, s_scores;
			TESTBED::get_seg_doc_scores(SEG[0], 0, TGT, d_scores, s_scores);

	            /*fprintf(stderr, "res.second[0]: [");
	            for(int i = 0; i < res.second[0].size(); ++i) fprintf(stderr, "%f,", res.second[0][i]);
	            fprintf(stderr, "]\n; %s: \n", TGT.c_str());
	        	fprintf(stderr, "---doc_seg.first: [");
	            for(int i = 0; i < doc_seg.first.size(); ++i) fprintf(stderr, "%f,", doc_seg.first[i]);
	            fprintf(stderr, "]\n---doc_seg.second: [");
	            for(int i = 0; i < doc_seg.second.size(); ++i) fprintf(stderr, "%f,", doc_seg.second[i]);
	            fprintf(stderr, "]\n");*/

	    	if (Config::O_STORAGE == 1) {
	    		sc_asiya.write_report(TGT, REF, prefB, SYS[0], d_scores, s_scores);
	    		fprintf(stderr, "SC_ASIYA DOCUMENT %s CREATED\n", prefB.c_str());
         	}
         	hOQ.save_hash_scores(prefB, TGT, REF, SYS[0], d_scores, s_scores);

			prefB = prefix + BLEU::BLEUEXT + "-2";
			TESTBED::get_seg_doc_scores(SEG[1], 0, TGT, d_scores, s_scores);
         	if (Config::O_STORAGE == 1) {
	    		sc_asiya.write_report(TGT, REF, prefB, SYS[1], d_scores, s_scores);
         		fprintf(stderr, "SC_ASIYA DOCUMENT %s CREATED\n", prefB.c_str());
         	}
	    	hOQ.save_hash_scores(prefB, TGT, REF, SYS[1], d_scores, s_scores);

	    	prefB = prefix + BLEU::BLEUEXT + "-3";
			TESTBED::get_seg_doc_scores(SEG[2], 0, TGT, d_scores, s_scores);
         	if (Config::O_STORAGE == 1) {
	    		sc_asiya.write_report(TGT, REF, prefB, SYS[2], d_scores, s_scores);
         		fprintf(stderr, "SC_ASIYA DOCUMENT %s CREATED\n", prefB.c_str());
         	}
         	hOQ.save_hash_scores(prefB, TGT, REF, SYS[2], d_scores, s_scores);

	    	prefB = prefix + BLEU::BLEUEXT + "-4";
			TESTBED::get_seg_doc_scores(SEG[3], 0, TGT, d_scores, s_scores);
         	if (Config::O_STORAGE == 1) {
	    		sc_asiya.write_report(TGT, REF, prefB, SYS[3], d_scores, s_scores);
         		fprintf(stderr, "SC_ASIYA DOCUMENT %s CREATED\n", prefB.c_str());
         	}
	    	hOQ.save_hash_scores(prefB, TGT, REF, SYS[3], d_scores, s_scores);

			prefB = prefix + BLEU::BLEUEXTi + "-2";
			TESTBED::get_seg_doc_scores(SEG[5], 0, TGT, d_scores, s_scores);
         	if (Config::O_STORAGE == 1) {
	    		sc_asiya.write_report(TGT, REF, prefB, SYS[5], d_scores, s_scores);
         		fprintf(stderr, "SC_ASIYA DOCUMENT %s CREATED\n", prefB.c_str());
         	}
         	hOQ.save_hash_scores(prefB, TGT, REF, SYS[5], d_scores, s_scores);

	    	prefB = prefix + BLEU::BLEUEXTi + "-3";
	    	TESTBED::get_seg_doc_scores(SEG[6], 0, TGT, d_scores, s_scores);
         	if (Config::O_STORAGE == 1) {
	    		sc_asiya.write_report(TGT, REF, prefB, SYS[6], d_scores, s_scores);
         		fprintf(stderr, "SC_ASIYA DOCUMENT %s CREATED\n", prefB.c_str());
         	}
	    	hOQ.save_hash_scores(prefB, TGT, REF, SYS[6], d_scores, s_scores);

	    	prefB = prefix + BLEU::BLEUEXTi + "-4";
	    	TESTBED::get_seg_doc_scores(SEG[7], 0, TGT, d_scores, s_scores);
	    	if (Config::O_STORAGE == 1) {
	    		sc_asiya.write_report(TGT, REF, prefB, SYS[7], d_scores, s_scores);
         		fprintf(stderr, "SC_ASIYA DOCUMENT %s CREATED\n", prefB.c_str());
         	}
	    	hOQ.save_hash_scores(prefB, TGT, REF, SYS[7], d_scores, s_scores);


	    	MetricScore m = computeBLEUN(TGT);

	    	if (Config::O_STORAGE == 1) {
	    		sc_asiya.write_report(TGT, REF, BLEU::BLEUEXT, m);
         		fprintf(stderr, "SC_ASIYA DOCUMENT %s CREATED\n", BLEU::BLEUEXT.c_str());
         	}
         	hOQ.save_hash_scores(BLEU::BLEUEXT, TGT, REF, m);

                /*cout << "-----------------------------------------BLEU-SCORES---------------------------------" << endl;
                hOQ.print_scores();
                cout << "-------------------------------------------------------------------------------------" << endl;
                exit(1);*/

	    }

	}

}

/*void BLEU::processMetric(string TGT, string REF, string prefix, Scores &hOQ) {
	stringstream ss1, ss2, ss3, ss4, ss2i, ss3i, ss4i, ssB;
	ss1 << Common::DATA_PATH << "/" << Common::REPORTS << "/" << TGT << "/" << REF << "/" << prefix << BLEU::BLEUEXT << "-1." << Common::XMLEXT;
	ss2 << Common::DATA_PATH << "/" << Common::REPORTS << "/" << TGT << "/" << REF << "/" << prefix << BLEU::BLEUEXT << "-2." << Common::XMLEXT;
	ss3 << Common::DATA_PATH << "/" << Common::REPORTS << "/" << TGT << "/" << REF << "/" << prefix << BLEU::BLEUEXT << "-3." << Common::XMLEXT;
	ss4 << Common::DATA_PATH << "/" << Common::REPORTS << "/" << TGT << "/" << REF << "/" << prefix << BLEU::BLEUEXT << "-4." << Common::XMLEXT;
	ss2i << Common::DATA_PATH << "/" << Common::REPORTS << "/" << TGT << "/" << REF << "/" << prefix << BLEU::BLEUEXTi << "-2." << Common::XMLEXT;
	ss3i << Common::DATA_PATH << "/" << Common::REPORTS << "/" << TGT << "/" << REF << "/" << prefix << BLEU::BLEUEXTi << "-3." << Common::XMLEXT;
	ss4i << Common::DATA_PATH << "/" << Common::REPORTS << "/" << TGT << "/" << REF << "/" << prefix << BLEU::BLEUEXTi << "-4." << Common::XMLEXT;
	ssB << Common::DATA_PATH << "/" << Common::REPORTS << "/" << TGT << "/" << REF << "/" << prefix << BLEU::BLEUEXT << "." << Common::XMLEXT;

    boost::filesystem::path reportBLEU1xml_path(ss1.str());
	boost::filesystem::path reportBLEU2xml_path(ss2.str());
    boost::filesystem::path reportBLEU3xml_path(ss3.str());
    boost::filesystem::path reportBLEU4xml_path(ss4.str());
    boost::filesystem::path reportBLEUi2xml_path(ss2i.str());
    boost::filesystem::path reportBLEUi3xml_path(ss3i.str());
    boost::filesystem::path reportBLEUi4xml_path(ss4i.str());
    boost::filesystem::path reportBLEUNxml_path(ssB.str());

	boost::filesystem::path reportBLEU1xml_ext(ss1.str() + "." + Common::GZEXT);
    boost::filesystem::path reportBLEU2xml_ext(ss2.str() + "." + Common::GZEXT);
    boost::filesystem::path reportBLEU3xml_ext(ss3.str() + "." + Common::GZEXT);
    boost::filesystem::path reportBLEU4xml_ext(ss4.str() + "." + Common::GZEXT);
    boost::filesystem::path reportBLEUi2xml_ext(ss2i.str() + "." + Common::GZEXT);
    boost::filesystem::path reportBLEUi3xml_ext(ss3i.str() + "." + Common::GZEXT);
    boost::filesystem::path reportBLEUi4xml_ext(ss4i.str() + "." + Common::GZEXT);
    boost::filesystem::path reportBLEUNxml_ext(ssB.str() + "." + Common::GZEXT);

    if ( (exists(reportBLEU1xml_path) and exists(reportBLEU1xml_ext)) or \
    (exists(reportBLEU2xml_path) and exists(reportBLEU2xml_ext)) or \
    (exists(reportBLEU3xml_path) and exists(reportBLEU3xml_ext)) or \
    (exists(reportBLEU4xml_path) and exists(reportBLEU4xml_ext)) or \
    (exists(reportBLEUi2xml_path) and exists(reportBLEUi2xml_ext)) or \
    (exists(reportBLEUi3xml_path) and exists(reportBLEUi3xml_ext)) or \
    (exists(reportBLEUi4xml_path) and exists(reportBLEUi4xml_ext)) or \
    (exists(reportBLEUNxml_path) and exists(reportBLEUNxml_ext)) or Config::remake) {

 		SC_ASIYA sc_asiya;

		string prefB = prefix;	prefB += BLEU::BLEUEXT;	prefB += "-1";
		sc_asiya.read_report(TGT, REF, prefB);

		prefB = prefix + BLEU::BLEUEXT + "-2";
		sc_asiya.read_report(TGT, REF, prefB);

		prefB = prefix + BLEU::BLEUEXT + "-3";
		sc_asiya.read_report(TGT, REF, prefB);

		prefB = prefix + BLEU::BLEUEXT + "-4";
		sc_asiya.read_report(TGT, REF, prefB);

		prefB = prefix + BLEU::BLEUEXTi + "-2";
		sc_asiya.read_report(TGT, REF, prefB);

		prefB = prefix + BLEU::BLEUEXTi + "-3";
		sc_asiya.read_report(TGT, REF, prefB);

		prefB = prefix + BLEU::BLEUEXTi + "-4";
		sc_asiya.read_report(TGT, REF, prefB);

		sc_asiya.read_report(TGT, REF, BLEU::BLEUEXT);
	}

}*/