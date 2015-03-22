#include "../include/NIST.hpp"

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

set<string> NIST::create_rNIST() {
	set<string> rNIST;
	rNIST.insert(NIST::NISTEXT);
	rNIST.insert(NIST::NISTEXT+"-1");
	rNIST.insert(NIST::NISTEXT+"-2");
	rNIST.insert(NIST::NISTEXT+"-3");
	rNIST.insert(NIST::NISTEXT+"-4");
	rNIST.insert(NIST::NISTEXT+"-5");
	rNIST.insert(NIST::NISTEXTi+"-2");
	rNIST.insert(NIST::NISTEXTi+"-3");
	rNIST.insert(NIST::NISTEXTi+"-4");
	rNIST.insert(NIST::NISTEXTi+"-5");
	return rNIST;
}
const set<string> NIST::rNIST = create_rNIST();

void NIST::read_nist(string reportNIST, vector<double> &SYS) {
	// description _ read NIST value from report file
    //boost::regex re("^ +NIST:.*");
    string str;
    bool individual = false;
    vector<double> lnist(5), lnisti(5);
    ifstream file(reportNIST.c_str());
    if (file) {
	    while (getline(file, str)) {
	    	boost::match_results<string::const_iterator> results;
	        if (boost::regex_match(str, results, Common::reNIST1)) {
	            //cout << "\t That was a kind of line" << endl;
	            string s = results[0];
	            //cout << "line: |" << s << "|" << endl;

				//boost::regex re2("^\\s+NIST:\\s+");	//, boost::regex::perl|boost::regex::icase);
				s = boost::regex_replace(s, Common::reNIST2, "");

				//cout << "\tline1: " << s << endl;

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

	    //for (int i = 0; i < 5; ++i) cout << "lnist[" << i << "]: " << lnist[i] << endl;
	    //for (int i = 0; i < 5; ++i) cout << "lnisti[" << i << "]: " << lnisti[i] << endl;

    //vector<double> SYS(0);
    SYS.clear();
    SYS.insert(SYS.begin(), lnist.begin(), lnist.end());
	    /*cout << "l after first insertion: ";
	    for (int i = 0; i < l.size(); ++i) cout << l[i] << ", ";
	    cout << endl;*/

    SYS.insert(SYS.begin() + 5, lnisti.begin(), lnisti.end());
	    /*cout << "l after second insertion: ";
	    for (int i = 0; i < l.size(); ++i) cout << l[i] << ", ";
	    cout << endl;*/

	//return l;
}

void NIST::read_nist_segments(string reportNIST, vector<vector<double> > &SEG) {
	// description _ read NIST-5 value from report file (for all segments)
    //boost::regex re1("^ +NIST score using.*");
    //boost::regex re2("^ +cumulative-NIST score using.*");
    //boost::regex re3("^ +individual-NIST score using.*");

    vector<double> lnist1, lnist2, lnist3, lnist4, lnist5;
    vector<double> lnist1i, lnist2i, lnist3i, lnist4i, lnist5i;

    //vector<vector<double> > SEG(10);
    SEG.resize(10);

    string str;
    ifstream file(reportNIST.c_str());
    if (file) {
	    while (getline(file, str)) {
	    	boost::match_results<string::const_iterator> results;

	        if (boost::regex_match(str, results, Common::reNIST3)) {
	            //cout << "\t That was a kind of line" << endl;
	            string s = results[0];
	            //cout << "line: |" << s << "|" << endl;

				vector<string> strs;
				boost::split(strs, s, boost::is_any_of("\t "));
				lnist1.push_back(atof(strs[7].c_str()));
				lnist2.push_back(atof(strs[8].c_str()));
				lnist3.push_back(atof(strs[9].c_str()));
				lnist4.push_back(atof(strs[10].c_str()));
				lnist5.push_back(atof(strs[11].c_str()));

	   			//for (int i = 0; i < strs.size(); ++i) cout << "strs[" << i << "]: " << strs[i] << endl;
			}
			else if (boost::regex_match(str, results, Common::reNIST4)) {
	            //cout << "\t That was a kind of line" << endl;
	            string s = results[0];
	            //cout << "line: |" << s << "|" << endl;

				vector<string> strs;
				boost::split(strs, s, boost::is_any_of("\t "));
				lnist1.push_back(atof(strs[7].c_str()));
				lnist2.push_back(atof(strs[8].c_str()));
				lnist3.push_back(atof(strs[9].c_str()));
				lnist4.push_back(atof(strs[10].c_str()));
				lnist5.push_back(atof(strs[11].c_str()));

	   			//for (int i = 0; i < strs.size(); ++i) cout << "strs[" << i << "]: " << strs[i] << endl;
			}
			else if (boost::regex_match(str, results, Common::reNIST5)) {
	            //cout << "\t That was a kind of line" << endl;
	            string s = results[0];
	            //cout << "line: |" << s << "|" << endl;

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

		/*cout << "--------------------SEG-----------------" << endl;
		for (int i = 0; i < SEG.size(); ++i) {
			for (int j = 0; j < SEG[i].size(); ++j) {
				cout << "SEG[" << i << "," << j << "]: " << SEG[i][j] << "\t";
			}
			cout << endl;
		}*/

	//return SEG;
}

void NIST::computeNIST(string TGT, string out, const map<string, string> &HREF, vector<double> &SYS, vector<vector<double> > &SEG) {
	// description _ computes NIST score (by calling NIST mteval script) -> n = 1..4 (multiple references)
	stringstream tNIST;

	tNIST << "perl " << Config::tools << "/" << NIST::TNIST << "/mteval-v13a.pl -n -d 2 ";

	if (Config::CASE == Common::CASE_CS) tNIST << "-c "; //toolBLEU += "-c ";
	string toolNIST = tNIST.str();

	//cout << "toolNIST ->" << toolNIST << endl << endl;

	//srand(time(NULL));
	double nr = rand() % (Common::NRAND + 1);	//random number [0, Common::NRAND];
	stringstream ssRef, ssSrc, ssOut, ssReport;
	ssRef << Common::DATA_PATH << "/" << Common::TMP << "/" << nr << "." << Common::REFEXT << "." << NIST::NISTEXT << "." << Common::SGMLEXT;
	ssSrc << Common::DATA_PATH << "/" << Common::TMP << "/" << nr << "." << Common::SRCEXT << "." << NIST::NISTEXT << "." << Common::SGMLEXT;
	ssOut << Common::DATA_PATH << "/" << Common::TMP << "/" << nr << "." << Common::SYSEXT << "." << NIST::NISTEXT << "." << Common::SGMLEXT;
	ssReport << Common::DATA_PATH << "/" << Common::TMP << "/" << nr << "." << NIST::NISTEXT << "." << Common::REPORTEXT;

    boost::filesystem::path refNISTsgml(ssRef.str());
    boost::filesystem::path srcNISTsgml(ssSrc.str());
    boost::filesystem::path outNISTsgml(ssOut.str());
    boost::filesystem::path reportNISTsgml(ssReport.str());

	if (!exists(refNISTsgml) or Config::remake) TB_NIST::SGML_f_create_mteval_multidoc(HREF, refNISTsgml.string(), 2);
	if (!exists(srcNISTsgml) or Config::remake) TB_NIST::SGML_f_create_mteval_doc(TESTBED::src, srcNISTsgml.string(), 0);
	if (!exists(outNISTsgml) or Config::remake) TB_NIST::SGML_f_create_mteval_doc(/*TESTBED::Hsystems[TGT]*/out, outNISTsgml.string(), 1);

	if (Config::verbose) fprintf(stderr, "building %s\n", reportNISTsgml.string().c_str());

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

	read_nist(ssReport.str(), SYS);
	read_nist_segments(ssReport.str(), SEG);
}


MetricScore NIST::computeNISTN(string TGT, string out, const map<string, string> &HREF) {
	// description _ computes smoothed and NIST-5 score (by calling NIST mteval script) (multiple references)
	stringstream tNISTN;

	tNISTN << "perl " << Config::tools << "/" << NIST::TNIST << "/mteval-v13a.pl -d 2 -n --metricsMATR ";

	if (Config::CASE == Common::CASE_CS) tNISTN << "-c ";
	string toolNISTN = tNISTN.str();

	//cout << "toolNISTN ->" << toolNISTN << endl << endl;

	double nr = rand() % (Common::NRAND + 1);	//random number [0, Common::NRAND];
	stringstream ssSrc, ssOut, ssRef;
	ssSrc << Common::DATA_PATH << "/" << Common::TMP << "/" << nr << "." << Common::SRCEXT << ".NIST." << Common::XMLEXT;
	ssOut << Common::DATA_PATH << "/" << Common::TMP << "/" << nr << "." << Common::SYSEXT << ".NIST." << Common::XMLEXT;
	ssRef << Common::DATA_PATH << "/" << Common::TMP << "/" << nr << "." << Common::REFEXT << ".NIST." << Common::XMLEXT;

    boost::filesystem::path srcXML(ssSrc.str());
    boost::filesystem::path outXML(ssOut.str());
    boost::filesystem::path refXML(ssRef.str());

    if (!exists(srcXML) or Config::remake) TB_NIST::f_create_mteval_doc(TESTBED::src, srcXML.string(), TGT, Common::CASE_CS, 0);
    if (!exists(outXML) or Config::remake) TB_NIST::f_create_mteval_doc(/*TESTBED::Hsystems[TGT]*/out, outXML.string(), TGT, Common::CASE_CS,  1);
    if (!exists(refXML) or Config::remake) TB_NIST::f_create_mteval_multidoc(HREF, refXML.string(), Common::CASE_CS, 2);

    stringstream sc;
    sc << "cd " << Common::DATA_PATH << "; " << toolNISTN << " -s " << ssSrc.str() << " -t " << ssOut.str() << " -r " << ssRef.str() << " >/dev/null 2>/dev/null";

    string ms = "[ERROR] problems running BLEU_NIST...";
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
	MetricScore NIST_scores = Scores::read_scores(Common::DATA_PATH + "/NIST", TGT, "-", 0);

	return NIST_scores;
}

void NIST::doMetric(string TGT, string out, string REF, const map<string, string> &HREF, string prefix, Scores &hOQ) {
   // description _ computes NIST score (by calling NIST mteval script) -> n = 1..4 (multiple references)
	int GO = 0;
	for (set<string>::const_iterator it = NIST::rNIST.begin(); !GO and it != NIST::rNIST.end(); ++it) {
		if (Config::Hmetrics.count(prefix+(*it))) GO = 1;
	}

	if (GO) {
		if (Config::verbose) fprintf(stderr, "%s\n", NIST::NISTEXT.c_str());

		string reportNIST1xml  = Common::DATA_PATH+"/"+Common::REPORTS+"/"+TGT+"/"+REF+"/"+prefix+NIST::NISTEXT+"-1."+Common::XMLEXT;
		string reportNIST2xml  = Common::DATA_PATH+"/"+Common::REPORTS+"/"+TGT+"/"+REF+"/"+prefix+NIST::NISTEXT+"-2."+Common::XMLEXT;
		string reportNIST3xml  = Common::DATA_PATH+"/"+Common::REPORTS+"/"+TGT+"/"+REF+"/"+prefix+NIST::NISTEXT+"-3."+Common::XMLEXT;
		string reportNIST4xml  = Common::DATA_PATH+"/"+Common::REPORTS+"/"+TGT+"/"+REF+"/"+prefix+NIST::NISTEXT+"-4."+Common::XMLEXT;
		string reportNIST5xml  = Common::DATA_PATH+"/"+Common::REPORTS+"/"+TGT+"/"+REF+"/"+prefix+NIST::NISTEXT+"-5."+Common::XMLEXT;
		string reportNISTi2xml = Common::DATA_PATH+"/"+Common::REPORTS+"/"+TGT+"/"+REF+"/"+prefix+NIST::NISTEXTi+"-2."+Common::XMLEXT;
		string reportNISTi3xml = Common::DATA_PATH+"/"+Common::REPORTS+"/"+TGT+"/"+REF+"/"+prefix+NIST::NISTEXTi+"-3."+Common::XMLEXT;
		string reportNISTi4xml = Common::DATA_PATH+"/"+Common::REPORTS+"/"+TGT+"/"+REF+"/"+prefix+NIST::NISTEXTi+"-4."+Common::XMLEXT;
		string reportNISTi5xml = Common::DATA_PATH+"/"+Common::REPORTS+"/"+TGT+"/"+REF+"/"+prefix+NIST::NISTEXTi+"-5."+Common::XMLEXT;
		string reportNISTNxml  = Common::DATA_PATH+"/"+Common::REPORTS+"/"+TGT+"/"+REF+"/"+prefix+NIST::NISTEXT+"."+Common::XMLEXT;

	    if ((!exists(boost::filesystem::path(reportNIST1xml)) and !exists(boost::filesystem::path(reportNIST1xml+"."+Common::GZEXT))) or
	    	(!exists(boost::filesystem::path(reportNIST2xml)) and !exists(boost::filesystem::path(reportNIST2xml+"."+Common::GZEXT))) or
	    	(!exists(boost::filesystem::path(reportNIST3xml)) and !exists(boost::filesystem::path(reportNIST3xml+"."+Common::GZEXT))) or
	    	(!exists(boost::filesystem::path(reportNIST4xml)) and !exists(boost::filesystem::path(reportNIST4xml+"."+Common::GZEXT))) or
	    	(!exists(boost::filesystem::path(reportNIST5xml)) and !exists(boost::filesystem::path(reportNIST5xml+"."+Common::GZEXT))) or
	    	(!exists(boost::filesystem::path(reportNISTi2xml)) and !exists(boost::filesystem::path(reportNISTi2xml+"."+Common::GZEXT))) or
	    	(!exists(boost::filesystem::path(reportNISTi3xml)) and !exists(boost::filesystem::path(reportNISTi3xml+"."+Common::GZEXT))) or
	    	(!exists(boost::filesystem::path(reportNISTi4xml)) and !exists(boost::filesystem::path(reportNISTi3xml+"."+Common::GZEXT))) or
	    	(!exists(boost::filesystem::path(reportNISTi5xml)) and !exists(boost::filesystem::path(reportNISTi5xml+"."+Common::GZEXT))) or
	    	(!exists(boost::filesystem::path(reportNISTNxml)) and !exists(boost::filesystem::path(reportNISTNxml+"."+Common::GZEXT))) or Config::remake) {

	    	vector<double> SYS;
	    	vector<vector<double> > SEG;
	    	computeNIST(TGT, out, HREF, SYS, SEG);

         	string prefN = prefix;	prefN += NIST::NISTEXT;	prefN += "-1";
	    	vector<double> d_scores, s_scores;
	    	TESTBED::get_seg_doc_scores(SEG[0], 0, TGT, d_scores, s_scores);

	    	if (Config::O_STORAGE == 1) {
	    		sc_asiya.write_report(TGT, REF, prefN, SYS[0], d_scores, s_scores);
         		fprintf(stderr, "SC_ASIYA DOCUMENT %s\n", prefN.c_str());
         	}
         	hOQ.save_hash_scores(prefN, TGT, REF, SYS[0], d_scores, s_scores);

	    	prefN = prefix + NIST::NISTEXT + "-2";
			TESTBED::get_seg_doc_scores(SEG[1], 0, TGT, d_scores, s_scores);
			if (Config::O_STORAGE == 1) {
	    		sc_asiya.write_report(TGT, REF, prefN, SYS[1], d_scores, s_scores);
         		fprintf(stderr, "SC_ASIYA DOCUMENT %s\n", prefN.c_str());
         	}
         	hOQ.save_hash_scores(prefN, TGT, REF, SYS[1], d_scores, s_scores);

	    	prefN = prefix + NIST::NISTEXT + "-3";
			TESTBED::get_seg_doc_scores(SEG[2], 0, TGT, d_scores, s_scores);
         	if (Config::O_STORAGE == 1) {
	    		sc_asiya.write_report(TGT, REF, prefN, SYS[2], d_scores, s_scores);
         		fprintf(stderr, "SC_ASIYA DOCUMENT %s\n", prefN.c_str());
         	}
	    	hOQ.save_hash_scores(prefN, TGT, REF, SYS[2], d_scores, s_scores);

	    	prefN = prefix + NIST::NISTEXT + "-4";
			TESTBED::get_seg_doc_scores(SEG[3], 0, TGT, d_scores, s_scores);
         	if (Config::O_STORAGE == 1) {
	    		sc_asiya.write_report(TGT, REF, prefN, SYS[3], d_scores, s_scores);
         		fprintf(stderr, "SC_ASIYA DOCUMENT %s\n", prefN.c_str());
         	}
	    	hOQ.save_hash_scores(prefN, TGT, REF, SYS[3], d_scores, s_scores);

	    	prefN = prefix + NIST::NISTEXT + "-5";
			TESTBED::get_seg_doc_scores(SEG[4], 0, TGT, d_scores, s_scores);
         	if (Config::O_STORAGE == 1) {
	    		sc_asiya.write_report(TGT, REF, prefN, SYS[4], d_scores, s_scores);
         		fprintf(stderr, "SC_ASIYA DOCUMENT %s\n", prefN.c_str());
         	}
	    	hOQ.save_hash_scores(prefN, TGT, REF, SYS[4], d_scores, s_scores);

	    	prefN = prefix + NIST::NISTEXTi + "-2";
			TESTBED::get_seg_doc_scores(SEG[5], 0, TGT, d_scores, s_scores);
         	if (Config::O_STORAGE == 1) {
	    		sc_asiya.write_report(TGT, REF, prefN, SYS[5], d_scores, s_scores);
         		fprintf(stderr, "SC_ASIYA DOCUMENT %s\n", prefN.c_str());
         	}
	    	hOQ.save_hash_scores(prefN, TGT, REF, SYS[5], d_scores, s_scores);

	    	prefN = prefix + NIST::NISTEXTi + "-3";
	    	TESTBED::get_seg_doc_scores(SEG[6], 0, TGT, d_scores, s_scores);
         	if (Config::O_STORAGE == 1) {
	    		sc_asiya.write_report(TGT, REF, prefN, SYS[6], d_scores, s_scores);
         		fprintf(stderr, "SC_ASIYA DOCUMENT %s\n", prefN.c_str());
         	}
	    	hOQ.save_hash_scores(prefN, TGT, REF, SYS[6], d_scores, s_scores);

	    	prefN = prefix + NIST::NISTEXTi + "-3";
	    	TESTBED::get_seg_doc_scores(SEG[7], 0, TGT, d_scores, s_scores);
         	if (Config::O_STORAGE == 1) {
	    		sc_asiya.write_report(TGT, REF, prefN, SYS[7], d_scores, s_scores);
         		fprintf(stderr, "SC_ASIYA DOCUMENT %s\n", prefN.c_str());
         	}
	    	hOQ.save_hash_scores(prefN, TGT, REF, SYS[7], d_scores, s_scores);

	    	prefN = prefix + NIST::NISTEXTi + "-4";
	    	TESTBED::get_seg_doc_scores(SEG[8], 0, TGT, d_scores, s_scores);
         	if (Config::O_STORAGE == 1) {
	    		sc_asiya.write_report(TGT, REF, prefN, SYS[8], d_scores, s_scores);
         		fprintf(stderr, "SC_ASIYA DOCUMENT %s\n", prefN.c_str());
         	}
	    	hOQ.save_hash_scores(prefN, TGT, REF, SYS[8], d_scores, s_scores);

	    	prefN = prefix + NIST::NISTEXTi + "-5";
	    	TESTBED::get_seg_doc_scores(SEG[9], 0, TGT, d_scores, s_scores);
         	if (Config::O_STORAGE == 1) {
	    		sc_asiya.write_report(TGT, REF, prefN, SYS[9], d_scores, s_scores);
         		fprintf(stderr, "SC_ASIYA DOCUMENT %s\n", prefN.c_str());
         	}
	    	hOQ.save_hash_scores(prefN, TGT, REF, SYS[9], d_scores, s_scores);

	    	MetricScore m = computeNISTN(TGT, out, HREF);
	    	prefN = prefix + NIST::NISTEXT;
	    	if (Config::O_STORAGE == 1) {
	    		sc_asiya.write_report(TGT, REF, prefN, m);
         		fprintf(stderr, "SC_ASIYA DOCUMENT %s\n", prefN.c_str());
         	}
         	hOQ.save_hash_scores(prefN, TGT, REF, m);
	    }

	}

}
