#include "CE.hpp"
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


const string CE::CEEXT = Common::CE;

// metric sets

map<string, int> CE::create_rCE() {
	map<string, int> rCE;
	rCE[CE::CEEXT + "-srclen"] = 1;		rCE[CE::CEEXT + "-srclogp"] = 1;	rCE[CE::CEEXT + "-srcippl"] = 1;
	rCE[CE::CEEXT + "-srcoov"] = 1;		rCE[CE::CEEXT + "-logp"] = 1;		rCE[CE::CEEXT + "-ippl"] = 1;
	rCE[CE::CEEXT + "-oov"] = 1;
	rCE[CE::CEEXT + "-srclogpP"] = 1;	rCE[CE::CEEXT + "-srcipplP"] = 1;	rCE[CE::CEEXT + "-logpP"] = 1;	rCE[CE::CEEXT + "-ipplP"] = 1;
	rCE[CE::CEEXT + "-srclogpC"] = 1;	rCE[CE::CEEXT + "-srcipplC"] = 1;	rCE[CE::CEEXT + "-logpC"] = 1;		rCE[CE::CEEXT + "-ipplC"] = 1;
	rCE[CE::CEEXT + "-length"] = 1;		rCE[CE::CEEXT + "-long"] = 1;		rCE[CE::CEEXT + "-short"] = 1;
	rCE[CE::CEEXT + "-symbols"] = 1;	rCE[CE::CEEXT + "-Op"] = 1;			rCE[CE::CEEXT + "-Oc"] = 1;
	rCE[CE::CEEXT + "-Nc"] = 1;			rCE[CE::CEEXT + "-Oe"] = 1;			rCE[CE::CEEXT + "-Ne"] = 1;
	rCE[CE::CEEXT + "-BiDictA"] = 1;	rCE[CE::CEEXT + "-BiDictO"] = 1;
	return rCE;
}
const map<string, int> CE::rCE = create_rCE();

map<string, int> CE::create_srcENG() {
	map<string, int> srcENG;
	srcENG[CE::CEEXT + "-srclen"] = 1;		srcENG[CE::CEEXT + "-srclogp"] = 1;		srcENG[CE::CEEXT + "-srcippl"] = 1;
	srcENG[CE::CEEXT + "-srcoov"] = 1;
	srcENG[CE::CEEXT + "-srclogpP"] = 1;	srcENG[CE::CEEXT + "-srcipplP"] = 1;
	srcENG[CE::CEEXT + "-srclogpC"] = 1;	srcENG[CE::CEEXT + "-srcipplC"] = 1;
	srcENG[CE::CEEXT + "-BiDictA"] = 1;
	return srcENG;
}
const map<string, int> CE::srcENG = create_srcENG();

map<string, int> CE::create_trgENG() {
	map<string, int> trgENG;
	trgENG[CE::CEEXT + "-logp"] = 1;	trgENG[CE::CEEXT + "-ippl"] = 1;	trgENG[CE::CEEXT + "-oov"] = 1;
	trgENG[CE::CEEXT + "-logpP"] = 1;	trgENG[CE::CEEXT + "-ipplP"] = 1;
	trgENG[CE::CEEXT + "-logpC"] = 1;	trgENG[CE::CEEXT + "-ipplC"] = 1;
	return trgENG;
}
const map<string, int> CE::trgENG = create_trgENG();


map<string, int> CE::create_notENGSPA() {
	map<string, int> notENGSPA;
	notENGSPA[CE::CEEXT + "-length"] = 1;	notENGSPA[CE::CEEXT + "-long"] = 1;	notENGSPA[CE::CEEXT + "-short"] = 1;	notENGSPA[CE::CEEXT + "-symbols"] = 1;
	notENGSPA[CE::CEEXT + "-Op"] = 1;	notENGSPA[CE::CEEXT + "-Oc"] = 1;	notENGSPA[CE::CEEXT + "-Nc"] = 1;
	notENGSPA[CE::CEEXT + "-Oe"] = 1;	notENGSPA[CE::CEEXT + "-Ne"] = 1;
	return notENGSPA;
}
const map<string, int> CE::notENGSPA = create_notENGSPA();

map<string, string> CE::create_rBIDICT() {
	map<string, string> rBIDICT;
	rBIDICT[Common::L_ENG + "-" + Common::L_SPA] = "apertium-dicts/en-es.dict";
	rBIDICT[Common::L_SPA + "-" + Common::L_ENG] = "apertium-dicts/es-en.dict";
	return rBIDICT;
}
const map<string, string> CE::rBIDICT = create_rBIDICT();

const int CE::BIDICT_MAX_NGRAM_LENGTH = 5;



const string CE::LM_path = "srilm";
const string CE::LM_ext = "LM";
const string CE::lm_ext = "lm";
const string CE::raw = "raw";
const string CE::pos = "pos";
const string CE::chunk = "chunk";



map<string, string> CE::create_LM_name() {
	map<string, string> LM_name;
	r[Common::L_ENG + "-" + Common::L_SPA] = "apertium-dicts/en-es.dict";
	rBIDICT[Common::L_SPA + "-" + Common::L_ENG] = "apertium-dicts/es-en.dict";
	return rBIDICT;
}
const map<string, string> CE::rBIDICT = create_rBIDICT();
	             $Common::L_ENG => { $CE::raw => "europarl-v5",
	             	                 $CE::pos => "europarl-v5",
	             	                 $CE::chunk => "europarl-v5" },
	             $Common::L_SPA => { $CE::raw => "europarl-v5",
	             	                 $CE::pos => "europarl-v5",
	             	                 $CE::chunk => "europarl-v5" }

vector<double> CE::read_CE(string reportCE) {
	// description _ read CE value from report file (for all segments)
	boost::regex re("^X CE-[SLW1-4][^ ]* Average_F.*");

    string str;
    map<string, double> hCE;

    ifstream file(reportCE.c_str());
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

				hCE[laux[1]] = atof(laux[3].c_str());
	        }
	    }
        file.close();
    } else { fprintf(stderr, "couldn't open file: %s\n", reportCE.c_str()); exit(1); }

    vector<double> lCE;
    for (map<string, double>::const_iterator it = hCE.begin(); it != hCE.end(); ++it)
    	lCE.push_back(it->second);

    return lCE;
}

vector<vector<double> > CE::read_CE_segments(string reportCE) {
    boost::regex re("^X CE-[SLW1-4][^ ]* Eval.*");

    vector<double> lCE1, lCE2, lCE3, lCE4;
    vector<double> lCEL, lCES, lCESU, lCEW;

    vector<vector<double> > SEG(8);

    string str;
    ifstream file(reportCE.c_str());
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

				if (laux[1] == "CE-1") lCE1.push_back(atof(llF[1].c_str()));
				else if (laux[1] == "CE-2") lCE2.push_back(atof(llF[1].c_str()));
				else if (laux[1] == "CE-3") lCE3.push_back(atof(llF[1].c_str()));
				else if (laux[1] == "CE-4") lCE4.push_back(atof(llF[1].c_str()));
				else if (laux[1] == "CE-L") lCEL.push_back(atof(llF[1].c_str()));
				else if (laux[1] == "CE-S*") lCES.push_back(atof(llF[1].c_str()));
				else if (laux[1] == "CE-SU*") lCESU.push_back(atof(llF[1].c_str()));
				else if (laux[1] == "CE-W-1.2") lCEW.push_back(atof(llF[1].c_str()));
			}
	    }
        file.close();
        SEG[0] = lCE1;	SEG[1] = lCE2;	SEG[2] = lCE3;	SEG[3] = lCE4;
        SEG[4] = lCEL;	SEG[5] = lCES;	SEG[6] = lCESU;	SEG[7] = lCEW;
	} else { fprintf(stderr, "couldn't open file: reportCE.txt\n"); exit(1); }
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


pair<vector<double>, vector<vector<double> > > CE::computeCE(string TGT, int stemming) {
	stringstream tCE;
	// description _ computes CE scores -> n = 1..4, LCS, S*, SU*, W-1.2 (multiple references)
	tCE << Config::tools << "/" << CE::TCE << "/" << "CE-1.5.5.pl -e " << Config::tools << "/" << CE::TCE << "/data -z SPL -2 -1 -U -r 1000 -n 4 -w 1.2 -c 95 -d";
	if (stemming ? " -m" : "");

	string toolCE = tCE.str();
	cout << "toolCE ->" << toolCE << endl << endl;

	srand(time(NULL));
	double nr = rand() % (Common::NRAND + 1);	//random number [0, Common::NRAND];
	stringstream ssReport, ssConfig;
	ssReport << Common::DATA_PATH << "/" << Common::TMP << "/" << nr << "." << CE::CEEXT << "." << Common::REPORTEXT;
	ssConfig << Common::DATA_PATH << "/" << Common::TMP << "/" << nr << "." << CE::CEEXT << "." << CE::CFGEXT;

	string reportCE = ssReport.str();
	string configCE = ssConfig.str();

	if (Config::verbose > 1) fprintf(stderr, "generating files for CE\n");

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
				ssJ << Common::DATA_PATH << "/" << Common::TMP << "/" << CE::CEEXT << "." << random << "." << Common::REFEXT << "." << j;

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

	ofstream cfg_file(configCE.c_str());
	ifstream out_file(Config::Hsystems[TGT].c_str());

    while (getline(out_file, str)) {
		stringstream ssOut_i;
		ssOut_i << Common::DATA_PATH << "/" << Common::TMP << "/" << CE::CEEXT << "." << random << "." << Common::SYSEXT << "." << i;

		string out_i = ssOut_i.str();

		vector<string> cfgline;
		for (map<string, string>::const_iterator it = Config::Hrefs.begin(); it != Config::Hrefs.end(); ++it) {
			stringstream ssRef_i;
			ssRef_i << Common::DATA_PATH << "/" << Common::TMP << "/" << CE::CEEXT << "." << hRAND[it->first] << "." << Common::REFEXT << "." << i;

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

    if (Config::verbose > 1) fprintf(stderr, "building %s...\n", reportCE.c_str());

	string sc = toolCE + " " + configCE + " > " + reportCE;
    string ms = "[ERROR] problems running CE...";
	Common::execute_or_die(sc, ms);

	string sysaux = "rm -f " + configCE;
	system(sysaux.c_str());

	int j = 1;
	while(j < 1) {
		stringstream ssAux;
		ssAux << Common::DATA_PATH << "/" << Common::TMP << "/" << CE::CEEXT << "." << random << "." << Common::SYSEXT << "." << j;
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
			ssAux << Common::DATA_PATH << "/" << Common::TMP << "/" << CE::CEEXT << "." << hRAND[it->first] << "." << Common::REFEXT << "." << j;
			string ss_aux;
		    boost::filesystem::path aux_path(ss_aux);

			if (!exists(aux_path)) {
				string rm_aux = "rm -f " + ss_aux;
				system(rm_aux.c_str());
			}
			++j;
		}
	}

	vector<double> SYS = read_CE(reportCE);
	vector<vector<double> > SEG = read_CE_segments(reportCE);

	return make_pair(SYS, SEG);
}

pair<double, vector<double> > CE::computeCE_segment_length() {
	// description _ computes segment length scores   (no references)
	double SUM;
	vector<double> SEGS;
    ifstream F(Config::src.c_str());
    if (F) {
        string line;
        while (getline(F, line)) {

			vector<string> l;
		    istringstream buf(line);
		    for(string token; getline(buf, token, ' '); ) l.push_back(token);

		    double SEGscore = Common::safe_division(1, l.size());
			if (Config::verbose) fprintf(stderr, "score = %d\n", SEGscore);
            SUM += SEGscore;
            SEGS.push_back(SEGscore);
        }
        F.close();
    } else { fprintf(stderr, "Couldn't open input file: %s\n", Config::src.c_str());  exit(1); }

    double SYS = Common::safe_division(SUM, SEGS.size());

    return make_pair(SYS, SEGS);
}


void CE::doMetric(string TGT, string REF, string prefix, int stemming, Scores &hOQ) {
	// description _ computes CE scores   (no references)

	//map<string, int> M = Config::Hmetrics;
	vector<string> mCE(CE::rCE.size());

	int GO, i;
	GO = i = 0;
	for (map<string, int>::const_iterator it = CE::rCE.begin(); it != CE::rCE.end(); ++it, ++i) {
		mCE[i] = it->first;
	}
	for (i = 0; i < mCE.size() and !GO; ++i) {
		string aux = prefix + mCE[i];
		if (Config::Hmetrics.find(aux) != Config::Hmetrics.end()) GO = 1;
	}

	cout << "CE ei!" << endl;
	if (GO) {
		cout << "GO! CE GO!" << endl;
		if (Config::verbose == 1) fprintf(stderr, "%s\n", CE::CEEXT.c_str());
		// TRANSLATION DIFFICULTY ###
       	// LENGTH
		stringstream ssReportCEsrclen;
		ssReportCEsrclen << Common::DATA_PATH << "/" << Common::REPORTS << "/" << TGT << "/" << CE::CEEXT << "/" << CE::CEEXT << "-srclen." << Common::XMLEXT;
		ssReportCEsrclogp << Common::DATA_PATH << "/" << Common::REPORTS << "/" << TGT << "/" << CE::CEEXT << "/" << CE::CEEXT << "-srclogp." << Common::XMLEXT;
		ssReportCEsrcippl << Common::DATA_PATH << "/" << Common::REPORTS << "/" << TGT << "/" << CE::CEEXT << "/" << CE::CEEXT << "-srcippl." << Common::XMLEXT;
		ssReportCEsrcoov << Common::DATA_PATH << "/" << Common::REPORTS << "/" << TGT << "/" << CE::CEEXT << "/" << CE::CEEXT << "-srcoov." << Common::XMLEXT;

		string reportCEsrclenXML = ssReportCEsrclen.str();
		string reporCEsrclogpXML = ssReportCEsrclogp.str();
		string reportCEsrcipplXML = ssReportCEsrcippl.str(),
		string reportCEsrcoovXML = ssReportCEsrcoov.str();

	    boost::filesystem::path reportCEsrclenXML_path(reportCEsrclenXML);
	    boost::filesystem::path reportCEsrclenXML_gz(reportCEsrclenXML_path + "." + Common::GZEXT);

	    string ce_srclen = CE::CEEXT + "-srclen";
	    if ( ((!exists(reportCEsrclenXML_path) and !exists(reportCEsrclenXML_gz)) or Config::remake) and Config::Hmetrics[ce_srclen]) {	//source length ratio
	    	pair<double, vector<double> > res = computeCE_segment_length();
	    	pair<vector<double>, vector<double> > doc_seg = Core::get_seg_doc_scores(res.second[0], TGT);
			//my ($doc_scores, $seg_scores) = Metrics::get_seg_doc_scores($SEGS, 0, $config->{IDX}->{$TGT});
         	if (Config::O_STORAGE == 1) {
	    		IQXML::write_report(TGT, CE::CEEXT, ce_srclen, res.first[0], doc_seg.first, doc_seg.second);
         		cout << "IQXML DOCUMENT " << ce_srclen << " CREATED" << endl;
         	}
         	hOQ.save_hash_scores(ce_srclen, TGT, REF, res.first[0], doc_seg.first, doc_seg.second);
	    }
	    // LANGUAGE MODELING
	    stringstream ssReportCEsrclogp, ssReportCEsrcippl, ssReportCEsrcoov;
		ssReportCEsrclogp << Common::DATA_PATH << "/" << Common::REPORTS << "/" << TGT << "/" << CE::CEEXT << "/" << CE::CEEXT << "-srclogp." << Common::XMLEXT;
		ssReportCEsrcippl << Common::DATA_PATH << "/" << Common::REPORTS << "/" << TGT << "/" << CE::CEEXT << "/" << CE::CEEXT << "-srcippl." << Common::XMLEXT;
		ssReportCEsrcoov << Common::DATA_PATH << "/" << Common::REPORTS << "/" << TGT << "/" << CE::CEEXT << "/" << CE::CEEXT << "-srcoov." << Common::XMLEXT;

		string reporCEsrclogpXML = ssReportCEsrclogp.str();
		string reportCEsrcipplXML = ssReportCEsrcippl.str(),
		string reportCEsrcoovXML = ssReportCEsrcoov.str();

	    boost::filesystem::path reportCEsrclogpXML_path(reportCEsrclogpXML);
	    boost::filesystem::path reportCEsrcipplXML_path(reportCEsrcipplXML);
	    boost::filesystem::path reportCEsrcoovXML_path(reportCEsrcoovXML);

	    boost::filesystem::path reportCEsrclogpXML_gz(reportCEsrclogpXML_path + "." + Common::GZEXT);
	    boost::filesystem::path reportCEsrcipplXML_gz(reportCEsrcipplXML_path + "." + Common::GZEXT);
	    boost::filesystem::path reportCEsrcoovXML_gz(reportCEsrcoovXML_path + "." + Common::GZEXT);

	    string ce_srclogp = CE::CEEXT + "-srclogp";
	    string ce_srcippl = CE::CEEXT + "-srcippl";
	    string ce_srcoov = CE::CEEXT + "-srcoov";
	    if ( (!exists(reporCEsrclogpXML_path) and !exists(reporCEsrclogpXML_gz)) or \
	    	(!exists(reporCEsrcipplXML_path) and !exists(reporCEsrcipplXML_gz)) or \
    		(!exists(reporCEsrcoovXML_path) and !exists(reporCEsrcoovXML_gz)) or Config::remake and \
    		(Config::Hmetrics[ce_srclogp]) or Config::Hmetrics[ce_srcippl] or Config::Metrics[ce_srcoov] ) {	//source language modeling

	    	pair< > res = compute_language_modeling_features();

	    }

	    s
		ss2 << Common::DATA_PATH << "/" << Common::REPORTS << "/" << TGT << "/" << REF << prefix << CE::CEEXT << "-2." << Common::XMLEXT;
		ss3 << Common::DATA_PATH << "/" << Common::REPORTS << "/" << TGT << "/" << REF << prefix << CE::CEEXT << "-3." << Common::XMLEXT;
		ss4 << Common::DATA_PATH << "/" << Common::REPORTS << "/" << TGT << "/" << REF << prefix << CE::CEEXT << "-4." << Common::XMLEXT;
		ssL << Common::DATA_PATH << "/" << Common::REPORTS << "/" << TGT << "/" << REF << prefix << CE::CEEXT << "-L." << Common::XMLEXT;
		ssS << Common::DATA_PATH << "/" << Common::REPORTS << "/" << TGT << "/" << REF << prefix << CE::CEEXT << "-S*." << Common::XMLEXT;
		ssSU << Common::DATA_PATH << "/" << Common::REPORTS << "/" << TGT << "/" << REF << prefix << CE::CEEXT << "-SU*." << Common::XMLEXT;
		ssW << Common::DATA_PATH << "/" << Common::REPORTS << "/" << TGT << "/" << REF << prefix << CE::CEEXT << "-W." << Common::XMLEXT;

		string reportCE1xml = ss1.str();
		string reportCE2xml = ss2.str();
		string reportCE3xml = ss3.str();
		string reportCE4xml = ss4.str();
		string reportCELxml = ssL.str();
		string reportCESxml = ssS.str();
		string reportCESUxml = ssSU.str();
		string reportCEWxml = ssW.str();

	    boost::filesystem::path reportCE1xml_path(reportCE1xml);
		boost::filesystem::path reportCE2xml_path(reportCE2xml);
	    boost::filesystem::path reportCE3xml_path(reportCE3xml);
	    boost::filesystem::path reportCE4xml_path(reportCE4xml);
	    boost::filesystem::path reportCELxml_path(reportCELxml);
	    boost::filesystem::path reportCESxml_path(reportCESxml);
	    boost::filesystem::path reportCESUxml_path(reportCESUxml);
	    boost::filesystem::path reportCEWxml_path(reportCEWxml);

	    boost::filesystem::path reportCE1xml_gz(reportCE1xml + "." + Common::GZEXT);
		boost::filesystem::path reportCE2xml_gz(reportCE2xml + "." + Common::GZEXT);
	    boost::filesystem::path reportCE3xml_gz(reportCE3xml + "." + Common::GZEXT);
	    boost::filesystem::path reportCE4xml_gz(reportCE4xml + "." + Common::GZEXT);
	    boost::filesystem::path reportCELxml_gz(reportCELxml + "." + Common::GZEXT);
	    boost::filesystem::path reportCESxml_gz(reportCESxml + "." + Common::GZEXT);
	    boost::filesystem::path reportCESUxml_gz(reportCESUxml + "." + Common::GZEXT);
	    boost::filesystem::path reportCEWxml_gz(reportCEWxml + "." + Common::GZEXT);

	    if ( (!exists(reportCE1xml_path) and !exists(reportCE1xml_gz)) or \
	    (!exists(reportCE2xml_path) and !exists(reportCE2xml_gz)) or \
	    (!exists(reportCE3xml_path) and !exists(reportCE3xml_gz)) or \
	    (!exists(reportCE4xml_path) and !exists(reportCE4xml_gz)) or \
	    (!exists(reportCELxml_path) and !exists(reportCELxml_gz)) or \
	    (!exists(reportCESxml_path) and !exists(reportCESxml_gz)) or \
	    (!exists(reportCESUxml_path) and !exists(reportCESUxml_gz)) or \
	    (!exists(reportCEWxml_path) and !exists(reportCEWxml_gz)) or Config::remake) {
        	//my ($SYS, $SEGS) = CE::computeMultiCE($src, $out, $Href, $remakeREPORTS, $TGT, $REF, $tools, $stemming, $verbose);
	    	pair<vector<double>, vector<vector<double> > > res = computeCE(TGT, stemming);

         	string prefR = prefix + CE::CEEXT + "-1";
			pair<vector<double>, vector<double> > doc_seg =  Core::get_seg_doc_scores(res.second[0], 0, TGT);
	    	if (Config::O_STORAGE == 1) {
	    		IQXML::write_report(TGT, REF, prefR, res.first[0], doc_seg.first, doc_seg.second);
         		cout << "IQXML DOCUMENT " << prefR << " CREATED" << endl;
         	}
         	hOQ.save_hash_scores(prefR, TGT, REF, res.first[0], doc_seg.first, doc_seg.second);

			prefR = prefix + CE::CEEXT + "-2";
			doc_seg = Core::get_seg_doc_scores(res.second[1], 0, TGT);
         	if (Config::O_STORAGE == 1) {
	    		IQXML::write_report(TGT, REF, prefR, res.first[1], doc_seg.first, doc_seg.second);
         		cout << "IQXML DOCUMENT " << prefR << " CREATED" << endl;
         	}
	    	hOQ.save_hash_scores(prefR, TGT, REF, res.first[1], doc_seg.first, doc_seg.second);

	    	prefR = prefix + CE::CEEXT + "-3";
			doc_seg = Core::get_seg_doc_scores(res.second[2], 0, TGT);
         	if (Config::O_STORAGE == 1) {
	    		IQXML::write_report(TGT, REF, prefR, res.first[2], doc_seg.first, doc_seg.second);
         		cout << "IQXML DOCUMENT " << prefR << " CREATED" << endl;
         	}
         	hOQ.save_hash_scores(prefR, TGT, REF, res.first[2], doc_seg.first, doc_seg.second);

	    	prefR = prefix + CE::CEEXT + "-4";
			doc_seg = Core::get_seg_doc_scores(res.second[3], 0, TGT);
         	if (Config::O_STORAGE == 1) {
	    		IQXML::write_report(TGT, REF, prefR, res.first[3], doc_seg.first, doc_seg.second);
         		cout << "IQXML DOCUMENT " << prefR << " CREATED" << endl;
         	}
	    	hOQ.save_hash_scores(prefR, TGT, REF, res.first[3], doc_seg.first, doc_seg.second);

	    	prefR = prefix + CE::CEEXT + "-L";
			doc_seg = Core::get_seg_doc_scores(res.second[4], 0, TGT);
         	if (Config::O_STORAGE == 1) {
	    		IQXML::write_report(TGT, REF, prefR, res.first[4], doc_seg.first, doc_seg.second);
         		cout << "IQXML DOCUMENT " << prefR << " CREATED" << endl;
         	}
	    	hOQ.save_hash_scores(prefR, TGT, REF, res.first[4], doc_seg.first, doc_seg.second);

			prefR = prefix + CE::CEEXT + "-S*";
			doc_seg = Core::get_seg_doc_scores(res.second[5], 0, TGT);
         	if (Config::O_STORAGE == 1) {
	    		IQXML::write_report(TGT, REF, prefR, res.first[5], doc_seg.first, doc_seg.second);
         		cout << "IQXML DOCUMENT " << prefR << " CREATED" << endl;
         	}
         	hOQ.save_hash_scores(prefR, TGT, REF, res.first[5], doc_seg.first, doc_seg.second);

	    	prefR = prefix + CE::CEEXT + "-SU*";
	    	doc_seg = Core::get_seg_doc_scores(res.second[6], 0, TGT);
         	if (Config::O_STORAGE == 1) {
	    		IQXML::write_report(TGT, REF, prefR, res.first[6], doc_seg.first, doc_seg.second);
         		cout << "IQXML DOCUMENT " << prefR << " CREATED" << endl;
         	}
	    	hOQ.save_hash_scores(prefR, TGT, REF, res.first[6], doc_seg.first, doc_seg.second);

	    	prefR = prefix + CE::CEEXT + "-W";
	    	doc_seg = Core::get_seg_doc_scores(res.second[7], 0, TGT);
	    	if (Config::O_STORAGE == 1) {
	    		IQXML::write_report(TGT, REF, prefR, res.first[7], doc_seg.first, doc_seg.second);
         		cout << "IQXML DOCUMENT " << prefR << " CREATED" << endl;
         	}
	    	hOQ.save_hash_scores(prefR, TGT, REF, res.first[7], doc_seg.first, doc_seg.second);
                /*cout << "-----------------------------------------CE-SCORES---------------------------------" << endl;
                hOQ.print_scores();
                cout << "-------------------------------------------------------------------------------------" << endl;
                exit(1);*/

	    }

	}

}
