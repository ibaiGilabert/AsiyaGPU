#include "../include/METEOR.hpp"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <iostream>
#include <sstream>

#include <boost/filesystem.hpp>

const string METEOR::MTREXT = "METEOR";
const string METEOR::TMETEOR = "meteor-1.4";
const string METEOR::METEORSCRIPT = "meteor-1.4.jar";

map<string, int> METEOR::create_rMETEOR() {
	map<string, int> rMETEOR;
	rMETEOR[METEOR::MTREXT + "-ex"] = 1;
	rMETEOR[METEOR::MTREXT + "-st"] = 1;
	rMETEOR[METEOR::MTREXT + "-sy"] = 1;
	rMETEOR[METEOR::MTREXT + "-pa"] = 1;
	return rMETEOR;
}
const map<string, int> METEOR::rMETEOR = create_rMETEOR();

map<string, int> METEOR::create_rLANG_STM() {
	map<string, int> rLANG_STM;
	rLANG_STM[Common::L_ENG] = 1;	rLANG_STM[Common::L_SPA] = 1;	rLANG_STM[Common::L_GER] = 1;
	rLANG_STM[Common::L_FRN] = 1;	rLANG_STM[Common::L_DAN] = 1;	rLANG_STM[Common::L_DUT] = 1;
	rLANG_STM[Common::L_FIN] = 1;	rLANG_STM[Common::L_HUN] = 1;	rLANG_STM[Common::L_ITA] = 1;
	rLANG_STM[Common::L_NOR] = 1;	rLANG_STM[Common::L_POR] = 1;	rLANG_STM[Common::L_ROM] = 1;
	rLANG_STM[Common::L_RUS] = 1;	rLANG_STM[Common::L_SWE] = 1;	rLANG_STM[Common::L_TUR] = 1;
	return rLANG_STM;
}
const map<string, int> METEOR::rLANG_STM = create_rLANG_STM();

map<string, int> METEOR::create_rLANG_PARA() {
	map<string, int> rLANG_PARA;
	rLANG_PARA[Common::L_ENG] = 1;	rLANG_PARA[Common::L_SPA] = 1;	rLANG_PARA[Common::L_GER] = 1;
	rLANG_PARA[Common::L_FRN] = 1;	rLANG_PARA[Common::L_CZE] = 1;	rLANG_PARA[Common::L_ARA] = 1;
	return rLANG_PARA;
}
const map<string, int> METEOR::rLANG_PARA = create_rLANG_PARA();

map<string, int> METEOR::create_rLANG_SYN() {
	map<string, int> rLANG_SYN;
	rLANG_SYN[Common::L_ENG] = 1;
	return rLANG_SYN;
}
const map<string, int> METEOR::rLANG_SYN = create_rLANG_SYN();

map<string, string> METEOR::create_rLANG() {
	map<string, string> rLANG;
	rLANG[Common::L_ENG] = "en";	rLANG[Common::L_SPA] = "es";	rLANG[Common::L_GER] = "de";
	rLANG[Common::L_FRN] = "fr";	rLANG[Common::L_CZE] = "cz";	rLANG[Common::L_ARA] = "ar";
	rLANG[Common::L_DAN] = "da";	rLANG[Common::L_DUT] = "nl";	rLANG[Common::L_FIN] = "fi";
	rLANG[Common::L_HUN] = "hu";	rLANG[Common::L_ITA] = "it";	rLANG[Common::L_NOR] = "no";
	rLANG[Common::L_POR] = "pt";	rLANG[Common::L_ROM] = "ro";	rLANG[Common::L_RUS] = "ru";
	rLANG[Common::L_SWE] = "sv";	rLANG[Common::L_TUR] = "tr";
	return rLANG;
}
map<string, string> METEOR::rLANG = create_rLANG();


MetricScore METEOR::computeMETEOR(string TGT, string variant) {
	// description _ computes METEOR scores (exact + stem + syn + para) (multiple references)
	string mem_options = " -Xms1024M -Xmx1024M ";

	string lang;
	if (METEOR::rLANG.find(Config::LANG) != METEOR::rLANG.end()) lang = "-l " + METEOR::rLANG[Config::LANG];

	srand(time(NULL));
	double nr = rand() % (Common::NRAND + 1);	//random number [0, Common::NRAND];

	string sysid = TESTBED::IDX[TGT][1][2];


	stringstream ssOut, ssRef;
	ssOut << Common::DATA_PATH << "/" << Common::TMP << "/" << nr << "." << Common::SYSEXT << "." << METEOR::MTREXT << "." << Common::XMLEXT;
	ssRef << Common::DATA_PATH << "/" << Common::TMP << "/" << nr << "." << Common::REFEXT << "." << METEOR::MTREXT << "." << Common::XMLEXT;

	string outMTRsgml = ssOut.str();
	string refMTRsgml = ssRef.str();

    boost::filesystem::path outMTRsgml_path(outMTRsgml);
    boost::filesystem::path refMTRsgml_path(refMTRsgml);

	if (!exists(outMTRsgml_path) or Config::remake) TB_NIST::f_create_mteval_doc(TESTBED::src, outMTRsgml, TGT, Config::CASE, 1);
    if (!exists(refMTRsgml_path) or Config::remake) TB_NIST::f_create_mteval_multidoc(refMTRsgml, Config::CASE, 2);

    string modules;
    if (variant == "exact") modules = "exact";
    else if (variant == "stem") modules == "exact stem";
    else if (variant == "syn") modules == "exact stem synonym";
    else if (variant == "para" and lang != "l -cz") modules == "exact stem paraphrase";
    else if (variant == "para" and lang == "l -cz") modules == "exact paraphrase";
    else { fprintf(stderr, "[ERROR] unknown METEOR variant <%s>\n", variant.c_str()); exit(1); }

	string toolMETEOR = "java -Dfile.encoding=UTF-8 "+mem_options+" -jar "+Config::tools+"/"+METEOR::TMETEOR+"/"+METEOR::METEORSCRIPT;

	cout << "toolMETEOR ->" << toolMETEOR << endl << endl;

	string sc = toolMETEOR +" "+outMTRsgml+" "+refMTRsgml+" -sgml -f "+Common::DATA_PATH+"/"+Common::TMP+"/"+sysid+" "+lang+" -m \""+modules+"\" > /dev/null 2> /dev/null";
    string ms = "[ERROR] problems running METEOR...";
	Common::execute_or_die(sc, ms);

	string basename = Common::DATA_PATH+"/"+Common::TMP+"/"+sysid;
	MetricScore res = Scores::read_scores(basename, TGT, 0);

	if (exists(outMTRsgml_path)) {
		string sysaux = "rm -f "+outMTRsgml;
		system (sysaux.c_str());
	}
	if (exists(refMTRsgml_path)) {
		string sysaux = "rm -f "+refMTRsgml;
		system (sysaux.c_str());
	}
	return res;
}


void METEOR::doMetric(string TGT, string REF, string prefix, Scores &hOQ) {
	// description _ computes METEOR scores (exact + stem + syn + para) (multiple references)
	vector<string> mMETEOR(METEOR::rMETEOR.size());

	int GO , i;
	GO = i = 0;
	for (map<string, int>::const_iterator it = METEOR::rMETEOR.begin(); it != METEOR::rMETEOR.end(); ++it, ++i)
		mMETEOR[i] = it->first;

	i = 0;
	while (i < mMETEOR.size() and !GO) {
		if (Config::Hmetrics.find(mMETEOR[i]) != Config::Hmetrics.end()) GO = 1;
		++i;
	}

	cout << "METEOR ei!" << endl;
	if (GO) {
		cout << "GO! METEOR GO!" << endl;
		if (Config::verbose == 1) fprintf(stderr, "%s\n", METEOR::MTREXT.c_str());
		stringstream ss1, ss2, ss3, ss4;
		ss1 << Common::DATA_PATH << "/" << Common::REPORTS << "/" << TGT << "/" << REF << METEOR::MTREXT << "-ex." << Common::XMLEXT;
		ss2 << Common::DATA_PATH << "/" << Common::REPORTS << "/" << TGT << "/" << REF << METEOR::MTREXT << "-st." << Common::XMLEXT;
		ss3 << Common::DATA_PATH << "/" << Common::REPORTS << "/" << TGT << "/" << REF << METEOR::MTREXT << "-sy." << Common::XMLEXT;
		ss4 << Common::DATA_PATH << "/" << Common::REPORTS << "/" << TGT << "/" << REF << METEOR::MTREXT << "-pa." << Common::XMLEXT;

		string reportMTRexactXML = ss1.str();
		string reportMTRstemXML = ss2.str();
		string reportMTRsynXML = ss3.str();
		string reportMTRparaXML = ss4.str();

	    boost::filesystem::path reportMTRexactXML_path(reportMTRexactXML);
		boost::filesystem::path reportMTRstemXML_path(reportMTRstemXML);
	    boost::filesystem::path reportMTRsynXML_path(reportMTRsynXML);
	    boost::filesystem::path reportMTRparaXML_path(reportMTRparaXML);

	    boost::filesystem::path reportMTRexactXML_ext(reportMTRexactXML + "." + Common::GZEXT);
		boost::filesystem::path reportMTRstemXML_ext(reportMTRstemXML + "." + Common::GZEXT);
	    boost::filesystem::path reportMTRsynXML_ext(reportMTRsynXML + "." + Common::GZEXT);
	    boost::filesystem::path reportMTRparaXML_ext(reportMTRparaXML + "." + Common::GZEXT);

		string mtr_ex = METEOR::MTREXT + "-ex";
		string mtr_st = METEOR::MTREXT + "-st";
		string mtr_sy = METEOR::MTREXT + "-sy";
		string mtr_pa = METEOR::MTREXT + "-pa";

		bool m_ex = Config::Hmetrics.find(mtr_ex) != Config::Hmetrics.end();
		bool m_st = Config::Hmetrics.find(mtr_st) != Config::Hmetrics.end();
		bool m_sy = Config::Hmetrics.find(mtr_sy) != Config::Hmetrics.end();
		bool m_pa = Config::Hmetrics.find(mtr_pa) != Config::Hmetrics.end();

		SC_ASIYA sc_asiya;

	    if ( ((!exists(reportMTRexactXML_path) and !exists(reportMTRexactXML_ext)) or Config::remake) and m_ex) {	//exact
			MetricScore res = computeMETEOR(TGT, "exact");
	    	if (Config::O_STORAGE == 1) {
	    		sc_asiya.write_report(TGT, REF, mtr_ex, res);
         		cout << "IQXML DOCUMENT " << mtr_ex << " CREATED" << endl;
         	}
         	hOQ.save_hash_scores(mtr_ex, TGT, REF, res);
		}
	    if ( ((!exists(reportMTRstemXML_path) and !exists(reportMTRstemXML_ext)) or Config::remake) and m_st) {	//exact + porter_stem
			if (METEOR::rLANG_STM.find(Config::LANG) != METEOR::rLANG_STM.end()) {
				MetricScore res = computeMETEOR(TGT, "stem");
		    	if (Config::O_STORAGE == 1) {
		    		sc_asiya.write_report(TGT, REF, mtr_st, res);
	         		cout << "IQXML DOCUMENT " << mtr_st << " CREATED" << endl;
	         	}
	         	hOQ.save_hash_scores(mtr_st, TGT, REF, res);
			}
			else { fprintf(stderr, "[ERROR] %s metric not available for language '%s'\n", mtr_st.c_str(), Config::LANG.c_str()); exit(1); }

		}
	    if ( ((!exists(reportMTRsynXML_path) and !exists(reportMTRsynXML_ext)) or Config::remake) and m_sy) {	//exact + porter_stem + wn_stem + wn_syn
			if (METEOR::rLANG_SYN.find(Config::LANG) != METEOR::rLANG_SYN.end()) {
				MetricScore res = computeMETEOR(TGT, "syn");
		    	if (Config::O_STORAGE == 1) {
		    		sc_asiya.write_report(TGT, REF, mtr_sy, res);
	         		cout << "IQXML DOCUMENT " << mtr_sy << " CREATED" << endl;
	         	}
	         	hOQ.save_hash_scores(mtr_sy, TGT, REF, res);
	        }
			else { fprintf(stderr, "[ERROR] %s metric not available for language '%s'\n", mtr_sy.c_str(), Config::LANG.c_str()); exit(1); }
		}
	    if ( ((!exists(reportMTRparaXML_path) and !exists(reportMTRparaXML_ext)) or Config::remake) and m_pa) {	//exact + porter_stem + wn_steam + wn_syn + para
			if (METEOR::rLANG_PARA.find(Config::LANG) != METEOR::rLANG_PARA.end()) {
				MetricScore res = computeMETEOR(TGT, "para");
		    	if (Config::O_STORAGE == 1) {
		    		sc_asiya.write_report(TGT, REF, mtr_pa, res);
	         		cout << "IQXML DOCUMENT " << mtr_pa << " CREATED" << endl;
	         	}
	         	hOQ.save_hash_scores(mtr_pa, TGT, REF, res);
	        }
			else { fprintf(stderr, "[ERROR] %s metric not available for language '%s'\n", mtr_pa.c_str(), Config::LANG.c_str()); exit(1); }
		}
	}

}
