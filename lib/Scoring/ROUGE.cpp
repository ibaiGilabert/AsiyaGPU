#include "../include/ROUGE.hpp"

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

set<string> ROUGE::create_rROUGE() {
	set<string> rROUGE;
	rROUGE.insert(ROUGE::ROUGEXT+"-1");
	rROUGE.insert(ROUGE::ROUGEXT+"-2");
	rROUGE.insert(ROUGE::ROUGEXT+"-3");
	rROUGE.insert(ROUGE::ROUGEXT+"-4");
	rROUGE.insert(ROUGE::ROUGEXT+"-L");
	rROUGE.insert(ROUGE::ROUGEXT+"-S*");
	rROUGE.insert(ROUGE::ROUGEXT+"-SU*");
	rROUGE.insert(ROUGE::ROUGEXT+"-W");
	return rROUGE;
}
const set<string> ROUGE::rROUGE = create_rROUGE();


void ROUGE::read_rouge(string reportROUGE, vector<double> &SYS) {
	// description _ read ROUGE value from report file (for all segments)
	//boost::regex re("^X ROUGE-[SLW1-4][^ ]* Average_F.*");
    string str;
    map<string, double> hROUGE;

    ifstream file(reportROUGE.c_str());
    if (file) {
	    while (getline(file, str)) {
	    	boost::match_results<string::const_iterator> results;
	        if (boost::regex_match(str, results, Common::reROUGE1)) {
	            //cout << "\t That was a kind of line" << endl;

	            string s = results[0];
	            //cout << "line: |" << s << "|" << endl;

			    vector<string> laux;
			    istringstream iss(s);
			    for(std::string token; getline(iss, token, ' '); ) laux.push_back(token);

				hROUGE[laux[1]] = atof(laux[3].c_str());
	        }
	    }
        file.close();
    } else { fprintf(stderr, "couldn't open file: %s\n", reportROUGE.c_str()); exit(1); }

    //vector<double> lROUGE;
    for (map<string, double>::const_iterator it = hROUGE.begin(); it != hROUGE.end(); ++it)
    	SYS.push_back(it->second);

    //return lROUGE;
}

void ROUGE::read_rouge_segments(string reportROUGE, vector<vector<double> > &SEG) {
    //boost::regex re("^X ROUGE-[SLW1-4][^ ]* Eval.*");
    vector<double> lROUGE1, lROUGE2, lROUGE3, lROUGE4;
    vector<double> lROUGEL, lROUGES, lROUGESU, lROUGEW;

    //vector<vector<double> > SEG(8);
    SEG.resize(8);

    string str;
    ifstream file(reportROUGE.c_str());
    if (file) {
	    while (getline(file, str)) {
	    	boost::match_results<string::const_iterator> results;

	        if (boost::regex_match(str, results, Common::reROUGE2)) {
	            //cout << "\t That was a kind of line" << endl;
	            string s = results[0];
	            //cout << "line: |" << s << "|" << endl;

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
	//return SEG;
}


void ROUGE::computeROUGE(string TGT, int stemming, vector<double> &SYS, vector<vector<double> > &SEG) {
	stringstream tROUGE;
	// description _ computes ROUGE scores -> n = 1..4, LCS, S*, SU*, W-1.2 (multiple references)
	tROUGE << Config::tools << "/" << ROUGE::TROUGE << "/" << "ROUGE-1.5.5.pl -e " << Config::tools << "/" << ROUGE::TROUGE << "/data -z SPL -2 -1 -U -r 1000 -n 4 -w 1.2 -c 95 -d";
	if (stemming ? " -m" : "");

	string toolROUGE = tROUGE.str();
	fprintf(stderr, "toolROUGE -> %s\n", toolROUGE.c_str());

	//srand(time(NULL));
	double nr = rand() % (Common::NRAND + 1);	//random number [0, Common::NRAND];
	string t_id;
    if (Config::serialize) t_id = "_" + TGT;//TB_FORMAT::get_formated_thread(TGT);

	stringstream ssReport, ssConfig;
	ssReport << Common::DATA_PATH << "/" << Common::TMP << "/" << nr << "." << ROUGE::ROUGEXT << t_id << "." << Common::REPORTEXT;
	ssConfig << Common::DATA_PATH << "/" << Common::TMP << "/" << nr << "." << ROUGE::ROUGEXT << t_id << "." << ROUGE::CFGEXT;

	string reportROUGE = ssReport.str();
	string configROUGE = ssConfig.str();

	if (Config::verbose > 1) fprintf(stderr, "generating files for ROUGE\n");

	string str;
	map<string, double> hRAND;
	for (map<string, string>::const_iterator it = TESTBED::Hrefs.begin(); it != TESTBED::Hrefs.end(); ++it) {
		string ref = it->second;

		int j = 1;
		ifstream ref_file(ref.c_str());
		if (ref_file) {
			double random = rand() % (Common::NRAND + 1);
			hRAND[it->first] = random;

		    while (getline(ref_file, str)) {
				stringstream ssJ;
				ssJ << Common::DATA_PATH << "/" << Common::TMP << "/" << ROUGE::ROUGEXT << t_id << "." << random << "." << Common::REFEXT << "." << j;

				string ref_j = ssJ.str();
		 	    boost::filesystem::path refJ_path(ref_j);

				if (!exists(refJ_path) or Config::remake) {
					ofstream refJ_file(ref_j.c_str());
					if (refJ_file) {
				        //boost::regex re("\\s*$");	//, boost::regex::perl|boost::regex::icase);
				        //boost::regex re2("^\\s*");	//, boost::regex::perl|boost::regex::icase);
						//boost::regex re3("^[\\?\\!\\.]$");
				        str = boost::regex_replace(str, Common::reEND_SPACE, "");
				        str = boost::regex_replace(str, Common::reSTART_SPACE, "");

		    			boost::match_results<string::const_iterator> results;
				        if (str.empty() or boost::regex_match(str, results, Common::reSPECIAL_CHAR)) str = Common::EMPTY_ITEM;
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
	ifstream out_file(TESTBED::Hsystems[TGT].c_str());

    while (getline(out_file, str)) {
		stringstream ssOut_i;
		ssOut_i << Common::DATA_PATH << "/" << Common::TMP << "/" << ROUGE::ROUGEXT << t_id << "." << random << "." << Common::SYSEXT << "." << i;

		string out_i = ssOut_i.str();

		vector<string> cfgline;
		for (map<string, string>::const_iterator it = TESTBED::Hrefs.begin(); it != TESTBED::Hrefs.end(); ++it) {
			stringstream ssRef_i;
			ssRef_i << Common::DATA_PATH << "/" << Common::TMP << "/" << ROUGE::ROUGEXT << t_id << "." << hRAND[it->first] << "." << Common::REFEXT << "." << i;

			string ref_i = ssRef_i.str();
			cfgline.push_back(ref_i);
    	}

 	    boost::filesystem::path outI_path(out_i);

    	if (!exists(outI_path) or Config::remake) {
			ofstream outI_file(out_i.c_str());
			if (outI_file) {
				//boost::regex re("\\s*$");	//, boost::regex::perl|boost::regex::icase);
				//boost::regex re2("^\\s*");	//, boost::regex::perl|boost::regex::icase);
				//boost::regex re3("^[\\?\\!\\.]$");
				str = boost::regex_replace(str, Common::reEND_SPACE, "");
				str = boost::regex_replace(str, Common::reSTART_SPACE, "");

	    		boost::match_results<string::const_iterator> results;
				if (str.empty() or boost::regex_match(str, results, Common::reSPECIAL_CHAR)) str = Common::EMPTY_ITEM;
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

	/*string sysaux = "rm -f " + configROUGE;
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

	for (map<string, string>::const_iterator it = TESTBED::Hrefs.begin(); it != TESTBED::Hrefs.end(); ++it) {
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
	}*/

	read_rouge(reportROUGE, SYS);
	read_rouge_segments(reportROUGE, SEG);
}

void ROUGE::doMetric(string TGT, string REF, string prefix, int stemming, Scores &hOQ) {
   // description _ computes ROUGE score (by calling NIST mteval script) -> n = 1..4 (multiple references)
	int GO = 0;
	for (set<string>::const_iterator it = ROUGE::rROUGE.begin(); !GO and it != ROUGE::rROUGE.end(); ++it) {
		if (Config::Hmetrics.count(prefix+(*it))) GO = 1;
	}
	if (GO) {
		if (Config::verbose == 1) fprintf(stderr, "%s\n", ROUGE::ROUGEXT.c_str());
	
		string reportROUGE1xml  = Common::DATA_PATH+"/"+Common::REPORTS+"/"+TGT+"/"+REF+"/"+prefix+ROUGE::ROUGEXT+"-1."+Common::XMLEXT;
		string reportROUGE2xml  = Common::DATA_PATH+"/"+Common::REPORTS+"/"+TGT+"/"+REF+"/"+prefix+ROUGE::ROUGEXT+"-2."+Common::XMLEXT;
		string reportROUGE3xml  = Common::DATA_PATH+"/"+Common::REPORTS+"/"+TGT+"/"+REF+"/"+prefix+ROUGE::ROUGEXT+"-3."+Common::XMLEXT;
		string reportROUGE4xml  = Common::DATA_PATH+"/"+Common::REPORTS+"/"+TGT+"/"+REF+"/"+prefix+ROUGE::ROUGEXT+"-4."+Common::XMLEXT;
		string reportROUGELxml  = Common::DATA_PATH+"/"+Common::REPORTS+"/"+TGT+"/"+REF+"/"+prefix+ROUGE::ROUGEXT+"-L."+Common::XMLEXT;
		string reportROUGESxml  = Common::DATA_PATH+"/"+Common::REPORTS+"/"+TGT+"/"+REF+"/"+prefix+ROUGE::ROUGEXT+"-S*."+Common::XMLEXT;
		string reportROUGESUxml = Common::DATA_PATH+"/"+Common::REPORTS+"/"+TGT+"/"+REF+"/"+prefix+ROUGE::ROUGEXT+"-SU*."+Common::XMLEXT;
		string reportROUGEWxml  = Common::DATA_PATH+"/"+Common::REPORTS+"/"+TGT+"/"+REF+"/"+prefix+ROUGE::ROUGEXT+"-W."+Common::XMLEXT;

	    if ((!exists(boost::filesystem::path(reportROUGE1xml)) and !exists(boost::filesystem::path(reportROUGE1xml+"."+Common::GZEXT))) or
	    	(!exists(boost::filesystem::path(reportROUGE2xml)) and !exists(boost::filesystem::path(reportROUGE2xml+"."+Common::GZEXT))) or
	    	(!exists(boost::filesystem::path(reportROUGE3xml)) and !exists(boost::filesystem::path(reportROUGE3xml+"."+Common::GZEXT))) or
	    	(!exists(boost::filesystem::path(reportROUGE4xml)) and !exists(boost::filesystem::path(reportROUGE4xml+"."+Common::GZEXT))) or
	    	(!exists(boost::filesystem::path(reportROUGELxml)) and !exists(boost::filesystem::path(reportROUGELxml+"."+Common::GZEXT))) or
	    	(!exists(boost::filesystem::path(reportROUGESxml)) and !exists(boost::filesystem::path(reportROUGESxml+"."+Common::GZEXT))) or
	    	(!exists(boost::filesystem::path(reportROUGESUxml)) and !exists(boost::filesystem::path(reportROUGESUxml+"."+Common::GZEXT))) or
	    	(!exists(boost::filesystem::path(reportROUGEWxml)) and !exists(boost::filesystem::path(reportROUGEWxml+"."+Common::GZEXT))) or Config::remake) {

	    	vector<double> SYS;
	    	vector<vector<double> > SEG;
	    	computeROUGE(TGT, stemming, SYS, SEG);

         	string prefR = prefix + ROUGE::ROUGEXT + "-1";
        	vector<double> d_scores, s_scores;
        	TESTBED::get_seg_doc_scores(SEG[0], 0, TGT, d_scores, s_scores);

			SC_ASIYA sc_asiya;

	    	if (Config::O_STORAGE == 1) {
	    		sc_asiya.write_report(TGT, REF, prefR, SYS[0], d_scores, s_scores);
         		fprintf(stderr, "SC_ASIYA DOCUMENT %s CREATED\n", prefR.c_str());
         	}
         	hOQ.save_hash_scores(prefR, TGT, REF, SYS[0], d_scores, s_scores);

			prefR = prefix + ROUGE::ROUGEXT + "-2";
			TESTBED::get_seg_doc_scores(SEG[1], 0, TGT, d_scores, s_scores);
         	if (Config::O_STORAGE == 1) {
	    		sc_asiya.write_report(TGT, REF, prefR, SYS[1], d_scores, s_scores);
         		fprintf(stderr, "SC_ASIYA DOCUMENT %s CREATED\n", prefR.c_str());
         	}
	    	hOQ.save_hash_scores(prefR, TGT, REF, SYS[1], d_scores, s_scores);

	    	prefR = prefix + ROUGE::ROUGEXT + "-3";
			TESTBED::get_seg_doc_scores(SEG[2], 0, TGT, d_scores, s_scores);
         	if (Config::O_STORAGE == 1) {
	    		sc_asiya.write_report(TGT, REF, prefR, SYS[2], d_scores, s_scores);
         		fprintf(stderr, "SC_ASIYA DOCUMENT %s CREATED\n", prefR.c_str());
         	}
         	hOQ.save_hash_scores(prefR, TGT, REF, SYS[2], d_scores, s_scores);

	    	prefR = prefix + ROUGE::ROUGEXT + "-4";
			TESTBED::get_seg_doc_scores(SEG[3], 0, TGT, d_scores, s_scores);
         	if (Config::O_STORAGE == 1) {
	    		sc_asiya.write_report(TGT, REF, prefR, SYS[3], d_scores, s_scores);
         		fprintf(stderr, "SC_ASIYA DOCUMENT %s CREATED\n", prefR.c_str());
         	}
	    	hOQ.save_hash_scores(prefR, TGT, REF, SYS[3], d_scores, s_scores);

	    	prefR = prefix + ROUGE::ROUGEXT + "-L";
			TESTBED::get_seg_doc_scores(SEG[4], 0, TGT, d_scores, s_scores);
         	if (Config::O_STORAGE == 1) {
	    		sc_asiya.write_report(TGT, REF, prefR, SYS[4], d_scores, s_scores);
         		fprintf(stderr, "SC_ASIYA DOCUMENT %s CREATED\n", prefR.c_str());
         	}
	    	hOQ.save_hash_scores(prefR, TGT, REF, SYS[4], d_scores, s_scores);

			prefR = prefix + ROUGE::ROUGEXT + "-S*";
			TESTBED::get_seg_doc_scores(SEG[5], 0, TGT, d_scores, s_scores);
         	if (Config::O_STORAGE == 1) {
	    		sc_asiya.write_report(TGT, REF, prefR, SYS[5], d_scores, s_scores);
         		fprintf(stderr, "SC_ASIYA DOCUMENT %s CREATED\n", prefR.c_str());
         	}
         	hOQ.save_hash_scores(prefR, TGT, REF, SYS[5], d_scores, s_scores);

	    	prefR = prefix + ROUGE::ROUGEXT + "-SU*";
	    	TESTBED::get_seg_doc_scores(SEG[6], 0, TGT, d_scores, s_scores);
         	if (Config::O_STORAGE == 1) {
	    		sc_asiya.write_report(TGT, REF, prefR, SYS[6], d_scores, s_scores);
         		fprintf(stderr, "SC_ASIYA DOCUMENT %s CREATED\n", prefR.c_str());
         	}
	    	hOQ.save_hash_scores(prefR, TGT, REF, SYS[6], d_scores, s_scores);

	    	prefR = prefix + ROUGE::ROUGEXT + "-W";
	    	TESTBED::get_seg_doc_scores(SEG[7], 0, TGT, d_scores, s_scores);
	    	if (Config::O_STORAGE == 1) {
	    		sc_asiya.write_report(TGT, REF, prefR, SYS[7], d_scores, s_scores);
         		fprintf(stderr, "SC_ASIYA DOCUMENT %s CREATED\n", prefR.c_str());
         	}
	    	hOQ.save_hash_scores(prefR, TGT, REF, SYS[7], d_scores, s_scores);

            if (Config::serialize) hOQ.save_struct_scores(TB_FORMAT::make_serial("ROUGE", TGT, REF));

                /*cout << "-----------------------------------------ROUGE-SCORES---------------------------------" << endl;
                hOQ.print_scores();
                cout << "-------------------------------------------------------------------------------------" << endl;
                exit(1);*/

	    }

	}

}
