#include "ROUGE.hpp"
#include "Core.hpp"
#include "Common.hpp"
#include "Config.hpp"
//#include "NISTXML.hpp"
#include "IQXML.hpp"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <iostream>
#include <fstream>
#include <sstream>

#include <boost/regex.hpp>
#include <boost/filesystem.hpp>
#include <boost/algorithm/string.hpp>


const string ROUGE::ROUGEXT = "ROUGE";
const string ROUGE::TROUGE = "rouge-1.5.5";    // version 1.5.5
const string ROUGE::CFGEXT = "config";

map<string, int> ROUGE::create_rROUGE() {
	map<string, int> rROUGE;
	rROUGE[ROUGE::ROUGEXT + "-1"] = 1;
	rROUGE[ROUGE::ROUGEXT + "-2"] = 1;
	rROUGE[ROUGE::ROUGEXT + "-3"] = 1;
	rROUGE[ROUGE::ROUGEXT + "-4"] = 1;
	rROUGE[ROUGE::ROUGEXT + "-L"] = 1;
	rROUGE[ROUGE::ROUGEXT + "-S*"] = 1;
	rROUGE[ROUGE::ROUGEXT + "-SU*"] = 1;
	rROUGE[ROUGE::ROUGEXT + "-W"] = 1;
	return rROUGE;
}
const map<string, int> ROUGE::rROUGE = create_rROUGE();


vector<double> ROUGE::read_rouge(string reportROUGE) {
	// description _ read ROUGE value from report file (for all segments)
	boost::regex re("^X ROUGE-[SLW1-4][^ ]* Average_F.*");

    string str;
    map<string, double> hROUGE;

    ifstream file(reportROUGE.c_str());
    if (file) {
	    while (getline(file, str)) {
	    	boost::match_results<string::const_iterator> results;
	        if (boost::regex_match(str, results, re)) {
	            cout << "\t That was a kind of line" << endl;

	            string s = results[0];
	            cout << "line: |" << s << "|" << endl;

			    vector<string> laux;
			    istringstream iss(s);
			    for(std::string token; getline(iss, token, ' '); ) laux.push_back(token);

				hROUGE[laux[1]] = atof(laux[3].c_str());
	        }
	    }
        file.close();
    } else { fprintf(stderr, "couldn't open file: %s\n", reportROUGE.c_str()); exit(1); }

    vector<double> lROUGE;
    for (map<string, double>::const_iterator it = hROUGE.begin(); it != hROUGE.end(); ++it)
    	lROUGE.push_back(it->second);

    return lROUGE;
}

vector<vector<double> > ROUGE::read_rouge_segments(string reportROUGE) {
    boost::regex re("^X ROUGE-[SLW1-4][^ ]* Eval.*");

    vector<double> lROUGE1, lROUGE2, lROUGE3, lROUGE4;
    vector<double> lROUGEL, lROUGES, lROUGESU, lROUGEW;

    vector<vector<double> > SEG(8);

    string str;
    ifstream file(reportROUGE.c_str());
    if (file) {
	    while (getline(file, str)) {
	    	boost::match_results<string::const_iterator> results;

	        if (boost::regex_match(str, results, re)) {
	            cout << "\t That was a kind of line" << endl;
	            string s = results[0];
	            cout << "line: |" << s << "|" << endl;

				vector<string> laux, ll, llF;
				//istringstream buffer(s);
				boost::split(laux, s, boost::is_any_of("\t "));
				boost::split(ll, laux[3], boost::is_any_of("."));
				boost::split(llF, laux[6], boost::is_any_of(":"));

				if (laux[1] == "ROUGE-1") lROUGE1.push_back(atof(llF[1].c_str()));
				else if (laux[1] == "ROUGE-2") lROUGE2.push_back(atof(llF[1].c_str()));
				else if (laux[1] == "ROUGE-3") lROUGE3.push_back(atof(llF[1].c_str()));
				else if (laux[1] == "ROUGE-4") lROUGE4.push_back(atof(llF[1].c_str()));
				else if (laux[1] == "ROUGE-L") lROUGEL.push_back(atof(llF[1].c_str()));
				else if (laux[1] == "ROUGE-S*") lROUGES.push_back(atof(llF[1].c_str()));
				else if (laux[1] == "ROUGE-SU*") lROUGESU.push_back(atof(llF[1].c_str()));
				else if (laux[1] == "ROUGE-W-1.2") lROUGEW.push_back(atof(llF[1].c_str()));
			}
	    }
        file.close();
        SEG[0] = lROUGE1;	SEG[1] = lROUGE2;	SEG[2] = lROUGE3;	SEG[3] = lROUGE4;
        SEG[4] = lROUGEL;	SEG[5] = lROUGES;	SEG[6] = lROUGESU;	SEG[7] = lROUGEW;
	} else { fprintf(stderr, "couldn't open file: reportROUGE.txt\n"); exit(1); }
/*
		cout << "--------------------SEG-----------------" << endl;
		for (int i = 0; i < SEG.size(); ++i) {
			for (int j = 0; j < SEG[i].size(); ++j) {
				cout << "SEG[" << i << "," << j << "]: " << SEG[i][j] << "\t";
			}
			cout << endl;
		}
*/
	return SEG;
}


pair<vector<double>, vector<vector<double> > > ROUGE::computeROUGE(string TGT, int stemming) {
	stringstream tROUGE;
	// description _ computes ROUGE scores -> n = 1..4, LCS, S*, SU*, W-1.2 (multiple references)
	tROUGE << Config::tools << "/" << ROUGE::TROUGE << "/" << "ROUGE-1.5.5.pl -e " << Config::tools << "/" << ROUGE::TROUGE << "/data -z SPL -2 -1 -U -r 1000 -n 4 -w 1.2 -c 95 -d";
	if (stemming ? " -m" : "");

	string toolROUGE = tROUGE.str();
	cout << "toolROUGE ->" << toolROUGE << endl << endl;

	srand(time(NULL));
	double nr = rand() % (Common::NRAND + 1);	//random number [0, Common::NRAND];
	stringstream ssReport, ssConfig;
	ssReport << Common::DATA_PATH << "/" << Common::TMP << "/" << nr << "." << ROUGE::ROUGEXT << "." << Common::REPORTEXT;
	ssConfig << Common::DATA_PATH << "/" << Common::TMP << "/" << nr << "." << ROUGE::ROUGEXT << "." << ROUGE::CFGEXT;

	string reportROUGE = ssReport.str();
	string configROUGE = ssConfig.str();

	if (Config::verbose > 1) fprintf(stderr, "generating files for ROUGE\n");

	string str;
	map<string, double> hRAND;
	for (map<string, string>::const_iterator it = Config::Hrefs.begin(); it != Config::Hrefs.end(); ++it) {
		string ref = it->second;

		int j = 1;
		ifstream ref_file(ref.c_str());
		if (ref_file) {
			double random = rand() % (Common::NRAND + 1);
			hRAND[it->first] = random;

		    while (getline(ref_file, str)) {
				stringstream ssJ;
				ssJ << Common::DATA_PATH << "/" << Common::TMP << "/" << ROUGE::ROUGEXT << "." << random << "." << Common::REFEXT << "." << j;

				string ref_j = ssJ.str();
		 	    boost::filesystem::path refJ_path(ref_j);

				if (!exists(refJ_path) or Config::remake) {
					ofstream refJ_file(ref_j.c_str());
					if (refJ_file) {
				        boost::regex re("\\s*$");	//, boost::regex::perl|boost::regex::icase);
				        boost::regex re2("^\\s*");	//, boost::regex::perl|boost::regex::icase);
						boost::regex re3("^[\\?\\!\\.]$");
				        str = boost::regex_replace(str, re, "");
				        str = boost::regex_replace(str, re2, "");

		    			boost::match_results<string::const_iterator> results;
				        if (str == "" or boost::regex_match(str, results, re3)) str = Common::EMPTY_ITEM;
						refJ_file << str << endl;

				        refJ_file.close();
					} else { fprintf(stderr, "couldn't open input file: %s\n", ref_j.c_str());   exit(1); }
				}
				++j;
			}
			ref_file.close();
		} else { fprintf(stderr, "couldn't open input file: %s\n", ref.c_str());   exit(1); }
	}

	int i = 1;
	double random = rand() % (Common::NRAND + 1);

	ofstream cfg_file(configROUGE.c_str());
	ifstream out_file(Config::Hsystems[TGT].c_str());

    while (getline(out_file, str)) {
		stringstream ssOut_i;
		ssOut_i << Common::DATA_PATH << "/" << Common::TMP << "/" << ROUGE::ROUGEXT << "." << random << "." << Common::SYSEXT << "." << i;

		string out_i = ssOut_i.str();

		vector<string> cfgline;
		for (map<string, string>::const_iterator it = Config::Hrefs.begin(); it != Config::Hrefs.end(); ++it) {
			stringstream ssRef_i;
			ssRef_i << Common::DATA_PATH << "/" << Common::TMP << "/" << ROUGE::ROUGEXT << "." << hRAND[it->first] << "." << Common::REFEXT << "." << i;

			string ref_i = ssRef_i.str();
			cfgline.push_back(ref_i);
    	}

 	    boost::filesystem::path outI_path(out_i);

    	if (!exists(outI_path) or Config::remake) {
			ofstream outI_file(out_i.c_str());
			if (outI_file) {
				boost::regex re("\\s*$");	//, boost::regex::perl|boost::regex::icase);
				boost::regex re2("^\\s*");	//, boost::regex::perl|boost::regex::icase);
				boost::regex re3("^[\\?\\!\\.]$");
				str = boost::regex_replace(str, re, "");
				str = boost::regex_replace(str, re2, "");

	    		boost::match_results<string::const_iterator> results;
				if (str == "" or boost::regex_match(str, results, re3)) str = Common::EMPTY_ITEM;
				outI_file << str << endl;

				outI_file.close();
			} else { fprintf(stderr, "couldn't open input file: %s\n", out_i.c_str());   exit(1); }
    	}
    	if (Config::verbose > 1) {
    		if (i%10 == 0) fprintf(stderr, ".");
    		if (i%100 == 0) fprintf(stderr, "%d\n", i);
    	}
    	++i;

    	cfg_file << out_i;
    	for (int k = 0; k < cfgline.size(); ++k) cfg_file << " " << cfgline[k];
    	cfg_file << endl;
    }
    if (Config::verbose > 1) fprintf(stderr, "..%d segments [DONE]", (i-1));

    out_file.close();
    cfg_file.close();

    if (Config::verbose > 1) fprintf(stderr, "building %s...\n", reportROUGE.c_str());

	string sc = toolROUGE + " " + configROUGE + " > " + reportROUGE;
    string ms = "[ERROR] problems running ROUGE...";
	Common::execute_or_die(sc, ms);

	string sysaux = "rm -f " + configROUGE;
	system(sysaux.c_str());

	int j = 1;
	while(j < 1) {
		stringstream ssAux;
		ssAux << Common::DATA_PATH << "/" << Common::TMP << "/" << ROUGE::ROUGEXT << "." << random << "." << Common::SYSEXT << "." << j;
		string ss_aux;
	    boost::filesystem::path aux_path(ss_aux);

		if (!exists(aux_path)) {
			string rm_aux = "rm -f " + ss_aux;
			system(rm_aux.c_str());
		}
		++j;
	}

	for (map<string, string>::const_iterator it = Config::Hrefs.begin(); it != Config::Hrefs.end(); ++it) {
		string ref = it->second;
		int j = 1;
		while (j < 1) {
			stringstream ssAux;
			ssAux << Common::DATA_PATH << "/" << Common::TMP << "/" << ROUGE::ROUGEXT << "." << hRAND[it->first] << "." << Common::REFEXT << "." << j;
			string ss_aux;
		    boost::filesystem::path aux_path(ss_aux);

			if (!exists(aux_path)) {
				string rm_aux = "rm -f " + ss_aux;
				system(rm_aux.c_str());
			}
			++j;
		}
	}

	vector<double> SYS = read_rouge(reportROUGE);
	vector<vector<double> > SEG = read_rouge_segments(reportROUGE);

	return make_pair(SYS, SEG);
}

void ROUGE::doMetric(string TGT, string REF, string prefix, int stemming, Scores &hOQ) {
   // description _ computes ROUGE score (by calling NIST mteval script) -> n = 1..4 (multiple references)

	//map<string, int> M = Config::Hmetrics;
	vector<string> mROUGE(ROUGE::rROUGE.size());

	int GO, i;
	GO = i = 0;
	for (map<string, int>::const_iterator it = ROUGE::rROUGE.begin(); it != ROUGE::rROUGE.end(); ++it, ++i) {
		mROUGE[i] = it->first;
	}
	for (i = 0; i < mROUGE.size() and !GO; ++i) {
		string aux = prefix + mROUGE[i];
		if (Config::Hmetrics.find(aux) != Config::Hmetrics.end()) GO = 1;
	}

	cout << "ROUGE ei!" << endl;
	if (GO) {
		cout << "GO! ROUGE GO!" << endl;
		if (Config::verbose == 1) fprintf(stderr, "%s\n", ROUGE::ROUGEXT.c_str());
		stringstream ss1, ss2, ss3, ss4, ssL, ssS, ssSU, ssW;
		ss1 << Common::DATA_PATH << "/" << Common::REPORTS << "/" << TGT << "/" << REF << prefix << ROUGE::ROUGEXT << "-1." << Common::XMLEXT;
		ss2 << Common::DATA_PATH << "/" << Common::REPORTS << "/" << TGT << "/" << REF << prefix << ROUGE::ROUGEXT << "-2." << Common::XMLEXT;
		ss3 << Common::DATA_PATH << "/" << Common::REPORTS << "/" << TGT << "/" << REF << prefix << ROUGE::ROUGEXT << "-3." << Common::XMLEXT;
		ss4 << Common::DATA_PATH << "/" << Common::REPORTS << "/" << TGT << "/" << REF << prefix << ROUGE::ROUGEXT << "-4." << Common::XMLEXT;
		ssL << Common::DATA_PATH << "/" << Common::REPORTS << "/" << TGT << "/" << REF << prefix << ROUGE::ROUGEXT << "-L." << Common::XMLEXT;
		ssS << Common::DATA_PATH << "/" << Common::REPORTS << "/" << TGT << "/" << REF << prefix << ROUGE::ROUGEXT << "-S*." << Common::XMLEXT;
		ssSU << Common::DATA_PATH << "/" << Common::REPORTS << "/" << TGT << "/" << REF << prefix << ROUGE::ROUGEXT << "-SU*." << Common::XMLEXT;
		ssW << Common::DATA_PATH << "/" << Common::REPORTS << "/" << TGT << "/" << REF << prefix << ROUGE::ROUGEXT << "-W." << Common::XMLEXT;

		string reportROUGE1xml = ss1.str();
		string reportROUGE2xml = ss2.str();
		string reportROUGE3xml = ss3.str();
		string reportROUGE4xml = ss4.str();
		string reportROUGELxml = ssL.str();
		string reportROUGESxml = ssS.str();
		string reportROUGESUxml = ssSU.str();
		string reportROUGEWxml = ssW.str();

	    boost::filesystem::path reportROUGE1xml_path(reportROUGE1xml);
		boost::filesystem::path reportROUGE2xml_path(reportROUGE2xml);
	    boost::filesystem::path reportROUGE3xml_path(reportROUGE3xml);
	    boost::filesystem::path reportROUGE4xml_path(reportROUGE4xml);
	    boost::filesystem::path reportROUGELxml_path(reportROUGELxml);
	    boost::filesystem::path reportROUGESxml_path(reportROUGESxml);
	    boost::filesystem::path reportROUGESUxml_path(reportROUGESUxml);
	    boost::filesystem::path reportROUGEWxml_path(reportROUGEWxml);

	    boost::filesystem::path reportROUGE1xml_gz(reportROUGE1xml + "." + Common::GZEXT);
		boost::filesystem::path reportROUGE2xml_gz(reportROUGE2xml + "." + Common::GZEXT);
	    boost::filesystem::path reportROUGE3xml_gz(reportROUGE3xml + "." + Common::GZEXT);
	    boost::filesystem::path reportROUGE4xml_gz(reportROUGE4xml + "." + Common::GZEXT);
	    boost::filesystem::path reportROUGELxml_gz(reportROUGELxml + "." + Common::GZEXT);
	    boost::filesystem::path reportROUGESxml_gz(reportROUGESxml + "." + Common::GZEXT);
	    boost::filesystem::path reportROUGESUxml_gz(reportROUGESUxml + "." + Common::GZEXT);
	    boost::filesystem::path reportROUGEWxml_gz(reportROUGEWxml + "." + Common::GZEXT);

	    if ( (!exists(reportROUGE1xml_path) and !exists(reportROUGE1xml_gz)) or \
	    (!exists(reportROUGE2xml_path) and !exists(reportROUGE2xml_gz)) or \
	    (!exists(reportROUGE3xml_path) and !exists(reportROUGE3xml_gz)) or \
	    (!exists(reportROUGE4xml_path) and !exists(reportROUGE4xml_gz)) or \
	    (!exists(reportROUGELxml_path) and !exists(reportROUGELxml_gz)) or \
	    (!exists(reportROUGESxml_path) and !exists(reportROUGESxml_gz)) or \
	    (!exists(reportROUGESUxml_path) and !exists(reportROUGESUxml_gz)) or \
	    (!exists(reportROUGEWxml_path) and !exists(reportROUGEWxml_gz)) or Config::remake) {
        	//my ($SYS, $SEGS) = ROUGE::computeMultiROUGE($src, $out, $Href, $remakeREPORTS, $TGT, $REF, $tools, $stemming, $verbose);
	    	pair<vector<double>, vector<vector<double> > > res = computeROUGE(TGT, stemming);

         	string prefR = prefix + ROUGE::ROUGEXT + "-1";
			pair<vector<double>, vector<double> > doc_seg =  Core::get_seg_doc_scores(res.second[0], 0, TGT);
	    	if (Config::O_STORAGE == 1) {
	    		IQXML::write_report(TGT, REF, prefR, res.first[0], doc_seg.first, doc_seg.second);
         		cout << "IQXML DOCUMENT " << prefR << " CREATED" << endl;
         	}
         	hOQ.save_hash_scores(prefR, TGT, REF, res.first[0], doc_seg.first, doc_seg.second);

			prefR = prefix + ROUGE::ROUGEXT + "-2";
			doc_seg = Core::get_seg_doc_scores(res.second[1], 0, TGT);
         	if (Config::O_STORAGE == 1) {
	    		IQXML::write_report(TGT, REF, prefR, res.first[1], doc_seg.first, doc_seg.second);
         		cout << "IQXML DOCUMENT " << prefR << " CREATED" << endl;
         	}
	    	hOQ.save_hash_scores(prefR, TGT, REF, res.first[1], doc_seg.first, doc_seg.second);

	    	prefR = prefix + ROUGE::ROUGEXT + "-3";
			doc_seg = Core::get_seg_doc_scores(res.second[2], 0, TGT);
         	if (Config::O_STORAGE == 1) {
	    		IQXML::write_report(TGT, REF, prefR, res.first[2], doc_seg.first, doc_seg.second);
         		cout << "IQXML DOCUMENT " << prefR << " CREATED" << endl;
         	}
         	hOQ.save_hash_scores(prefR, TGT, REF, res.first[2], doc_seg.first, doc_seg.second);

	    	prefR = prefix + ROUGE::ROUGEXT + "-4";
			doc_seg = Core::get_seg_doc_scores(res.second[3], 0, TGT);
         	if (Config::O_STORAGE == 1) {
	    		IQXML::write_report(TGT, REF, prefR, res.first[3], doc_seg.first, doc_seg.second);
         		cout << "IQXML DOCUMENT " << prefR << " CREATED" << endl;
         	}
	    	hOQ.save_hash_scores(prefR, TGT, REF, res.first[3], doc_seg.first, doc_seg.second);

	    	prefR = prefix + ROUGE::ROUGEXT + "-L";
			doc_seg = Core::get_seg_doc_scores(res.second[4], 0, TGT);
         	if (Config::O_STORAGE == 1) {
	    		IQXML::write_report(TGT, REF, prefR, res.first[4], doc_seg.first, doc_seg.second);
         		cout << "IQXML DOCUMENT " << prefR << " CREATED" << endl;
         	}
	    	hOQ.save_hash_scores(prefR, TGT, REF, res.first[4], doc_seg.first, doc_seg.second);

			prefR = prefix + ROUGE::ROUGEXT + "-S*";
			doc_seg = Core::get_seg_doc_scores(res.second[5], 0, TGT);
         	if (Config::O_STORAGE == 1) {
	    		IQXML::write_report(TGT, REF, prefR, res.first[5], doc_seg.first, doc_seg.second);
         		cout << "IQXML DOCUMENT " << prefR << " CREATED" << endl;
         	}
         	hOQ.save_hash_scores(prefR, TGT, REF, res.first[5], doc_seg.first, doc_seg.second);

	    	prefR = prefix + ROUGE::ROUGEXT + "-SU*";
	    	doc_seg = Core::get_seg_doc_scores(res.second[6], 0, TGT);
         	if (Config::O_STORAGE == 1) {
	    		IQXML::write_report(TGT, REF, prefR, res.first[6], doc_seg.first, doc_seg.second);
         		cout << "IQXML DOCUMENT " << prefR << " CREATED" << endl;
         	}
	    	hOQ.save_hash_scores(prefR, TGT, REF, res.first[6], doc_seg.first, doc_seg.second);

	    	prefR = prefix + ROUGE::ROUGEXT + "-W";
	    	doc_seg = Core::get_seg_doc_scores(res.second[7], 0, TGT);
	    	if (Config::O_STORAGE == 1) {
	    		IQXML::write_report(TGT, REF, prefR, res.first[7], doc_seg.first, doc_seg.second);
         		cout << "IQXML DOCUMENT " << prefR << " CREATED" << endl;
         	}
	    	hOQ.save_hash_scores(prefR, TGT, REF, res.first[7], doc_seg.first, doc_seg.second);
                /*cout << "-----------------------------------------ROUGE-SCORES---------------------------------" << endl;
                hOQ.print_scores();
                cout << "-------------------------------------------------------------------------------------" << endl;
                exit(1);*/

	    }

	}

}
