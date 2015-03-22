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

set<string> METEOR::create_rMETEOR() {
	set<string> rMETEOR;
	rMETEOR.insert(METEOR::MTREXT+"-ex");
	rMETEOR.insert(METEOR::MTREXT+"-st");
	rMETEOR.insert(METEOR::MTREXT+"-sy");
	rMETEOR.insert(METEOR::MTREXT+"-pa");
	return rMETEOR;
}
const set<string> METEOR::rMETEOR = create_rMETEOR();

set<string> METEOR::create_rLANG_STM() {
	set<string> rLANG_STM;
	rLANG_STM.insert(Common::L_ENG);	rLANG_STM.insert(Common::L_SPA);	rLANG_STM.insert(Common::L_GER);
	rLANG_STM.insert(Common::L_FRN);	rLANG_STM.insert(Common::L_DAN);	rLANG_STM.insert(Common::L_DUT);
	rLANG_STM.insert(Common::L_FIN);	rLANG_STM.insert(Common::L_HUN);	rLANG_STM.insert(Common::L_ITA);
	rLANG_STM.insert(Common::L_NOR);	rLANG_STM.insert(Common::L_POR);	rLANG_STM.insert(Common::L_ROM);
	rLANG_STM.insert(Common::L_RUS);	rLANG_STM.insert(Common::L_SWE);	rLANG_STM.insert(Common::L_TUR);
	return rLANG_STM;
}
const set<string> METEOR::rLANG_STM = create_rLANG_STM();

set<string> METEOR::create_rLANG_PARA() {
	set<string> rLANG_PARA;
	rLANG_PARA.insert(Common::L_ENG);	rLANG_PARA.insert(Common::L_SPA);	rLANG_PARA.insert(Common::L_GER);
	rLANG_PARA.insert(Common::L_FRN);	rLANG_PARA.insert(Common::L_CZE);	rLANG_PARA.insert(Common::L_ARA);
	return rLANG_PARA;
}
const set<string> METEOR::rLANG_PARA = create_rLANG_PARA();

set<string> METEOR::create_rLANG_SYN() {
	set<string> rLANG_SYN;
	rLANG_SYN.insert(Common::L_ENG);
	return rLANG_SYN;
}
const set<string> METEOR::rLANG_SYN = create_rLANG_SYN();

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


void METEOR::computeMETEOR(string TGT, string variant, MetricScore &res) {
	// description _ computes METEOR scores (exact + stem + syn + para) (multiple references)
	string mem_options = "-Xms1024M -Xmx1024M";

	string lang, t_id;
	if (METEOR::rLANG.find(Config::LANG) != METEOR::rLANG.end()) lang = "-l " + METEOR::rLANG[Config::LANG];
    if (Config::serialize) t_id = "_" + TGT;//TB_FORMAT::get_formated_thread(TGT);

	//srand(time(NULL));
	double nr = rand() % (Common::NRAND + 1);	//random number [0, Common::NRAND];

	string sysid = TESTBED::IDX[TGT][1][2];

	stringstream ssOut, ssRef;
	ssOut << Common::DATA_PATH << "/" << Common::TMP << "/" << nr << "." << Common::SYSEXT << "." << METEOR::MTREXT << t_id << "." << Common::XMLEXT;
	ssRef << Common::DATA_PATH << "/" << Common::TMP << "/" << nr << "." << Common::REFEXT << "." << METEOR::MTREXT << t_id << "." << Common::XMLEXT;

	string outMTRsgml = ssOut.str();
	string refMTRsgml = ssRef.str();

	if (!exists(boost::filesystem::path(outMTRsgml)) or Config::remake) TB_NIST::f_create_mteval_doc(TESTBED::Hsystems[TGT], outMTRsgml, TGT, Config::CASE, 1);
    if (!exists(boost::filesystem::path(refMTRsgml)) or Config::remake) TB_NIST::f_create_mteval_multidoc(TESTBED::Hrefs, refMTRsgml, Config::CASE, 2);

    string modules;
    if (variant == "exact") modules = "exact";
    else if (variant == "stem") modules = "exact stem";
    else if (variant == "syn") modules = "exact stem synonym";
    else if (variant == "para" and lang != "l -cz") modules = "exact stem paraphrase";
    else if (variant == "para" and lang == "l -cz") modules = "exact paraphrase";
    else { fprintf(stderr, "[ERROR] unknown METEOR variant <%s>\n", variant.c_str()); exit(1); }

	string toolMETEOR = "java -Dfile.encoding=UTF-8 "+mem_options+" -jar "+Config::tools+"/"+METEOR::TMETEOR+"/"+METEOR::METEORSCRIPT;

	//fprintf(stderr, "toolMETEOR -> %s\n", toolMETEOR);

	/*stringstream ssBase;
	ssBase << Common::DATA_PATH << "/" << Common::TMP << "/" << nr << TGT;	//sysid;
	string basename = ssBase.str();*/

	string basename = Common::DATA_PATH+"/"+Common::TMP+"/METEOR"+t_id;	//sysid;
	string sc = toolMETEOR +" "+outMTRsgml+" "+refMTRsgml+" -sgml -f "+basename/*Common::DATA_PATH+"/"+Common::TMP+"/"+sysid*/+" "+lang+" -m \""+modules+"\" > /dev/null 2> /dev/null";
    string ms = "[ERROR] problems running METEOR...";
	Common::execute_or_die(sc, ms);

	//string basename = Common::DATA_PATH+"/"+Common::TMP+"/"+TGT;	//sysid;

	//cout << "MetricScore BEFORE read <" << basename << "> file" << endl;
    //hOQ.print_MetricScore(res);
	res = Scores::read_scores(basename, TGT, "-", 0);
	//cout << "MetricScore AFTER read <" << basename << "> file" << endl;

	if (exists(boost::filesystem::path(outMTRsgml))) {
		string sysaux = "rm -f "+outMTRsgml;
		system (sysaux.c_str());
	}
	if (exists(boost::filesystem::path(refMTRsgml))) {
		string sysaux = "rm -f "+refMTRsgml;
		system (sysaux.c_str());
	}
}


void METEOR::doMetric(string TGT, string REF, string prefix, Scores &hOQ) {
	// description _ computes METEOR scores (exact + stem + syn + para) (multiple references)
	int GO = 0;
	for (set<string>::const_iterator it = METEOR::rMETEOR.begin(); !GO and it != METEOR::rMETEOR.end(); ++it) {
		if (Config::Hmetrics.count(*it)) GO = 1;
	}

	if (GO) {
		if (Config::verbose == 1) fprintf(stderr, "%s\n", METEOR::MTREXT.c_str());

		string reportMTRexactXML = Common::DATA_PATH+"/"+Common::REPORTS+"/"+TGT+"/"+REF+"/"+METEOR::MTREXT+"-ex."+Common::XMLEXT;
		string reportMTRstemXML  = Common::DATA_PATH+"/"+Common::REPORTS+"/"+TGT+"/"+REF+"/"+METEOR::MTREXT+"-st."+Common::XMLEXT;
		string reportMTRsynXML   = Common::DATA_PATH+"/"+Common::REPORTS+"/"+TGT+"/"+REF+"/"+METEOR::MTREXT+"-sy."+Common::XMLEXT;
		string reportMTRparaXML  = Common::DATA_PATH+"/"+Common::REPORTS+"/"+TGT+"/"+REF+"/"+METEOR::MTREXT+"-pa."+Common::XMLEXT;

		string mtr_ex = METEOR::MTREXT + "-ex";
		string mtr_st = METEOR::MTREXT + "-st";
		string mtr_sy = METEOR::MTREXT + "-sy";
		string mtr_pa = METEOR::MTREXT + "-pa";

		MetricScore res;
	    if ( ((!exists(boost::filesystem::path(reportMTRexactXML)) and !exists(boost::filesystem::path(reportMTRexactXML+"."+Common::GZEXT))) or Config::remake) and Config::Hmetrics.count(mtr_ex) ) {	//exact
			computeMETEOR(TGT, "exact", res);
	    	if (Config::O_STORAGE == 1) {
	    		sc_asiya.write_report(TGT, REF, mtr_ex, res);
         		fprintf(stderr, "SC_ASIYA DOCUMENT %s\n", mtr_ex.c_str());
         	}
         	hOQ.save_hash_scores(mtr_ex, TGT, REF, res);
		}
		if ( ((!exists(boost::filesystem::path(reportMTRstemXML)) and !exists(boost::filesystem::path(reportMTRstemXML+"."+Common::GZEXT))) or Config::remake) and Config::Hmetrics.count(mtr_st) ) {	//exact + porter_stem
			if (METEOR::rLANG_STM.count(Config::LANG)) {
				computeMETEOR(TGT, "stem", res);
		    	if (Config::O_STORAGE == 1) {
		    		sc_asiya.write_report(TGT, REF, mtr_st, res);
         			fprintf(stderr, "SC_ASIYA DOCUMENT %s\n", mtr_st.c_str());
	         	}
	         	hOQ.save_hash_scores(mtr_st, TGT, REF, res);
			}
			else { fprintf(stderr, "[ERROR] %s metric not available for language '%s'\n", mtr_st.c_str(), Config::LANG.c_str()); exit(1); }

		}
		if ( ((!exists(boost::filesystem::path(reportMTRsynXML)) and !exists(boost::filesystem::path(reportMTRsynXML+"."+Common::GZEXT))) or Config::remake) and Config::Hmetrics.count(mtr_sy) ) {		//exact + porter_stem + wn_stem + wn_syn
			if (METEOR::rLANG_SYN.count(Config::LANG)) {
				computeMETEOR(TGT, "syn", res);
		    	if (Config::O_STORAGE == 1) {
		    		sc_asiya.write_report(TGT, REF, mtr_sy, res);
         			fprintf(stderr, "SC_ASIYA DOCUMENT %s\n", mtr_sy.c_str());
	         	}
	         	hOQ.save_hash_scores(mtr_sy, TGT, REF, res);
	        }
			else { fprintf(stderr, "[ERROR] %s metric not available for language '%s'\n", mtr_sy.c_str(), Config::LANG.c_str()); exit(1); }
		}
		if ( ((!exists(boost::filesystem::path(reportMTRparaXML)) and !exists(boost::filesystem::path(reportMTRparaXML+"."+Common::GZEXT))) or Config::remake) and Config::Hmetrics.count(mtr_pa) ) {		//exact + porter_stem + wn_steam + wn_syn + para
			if (METEOR::rLANG_PARA.count(Config::LANG)) {
				computeMETEOR(TGT, "para", res);
		    	if (Config::O_STORAGE == 1) {
		    		sc_asiya.write_report(TGT, REF, mtr_pa, res);
         			fprintf(stderr, "SC_ASIYA DOCUMENT %s\n", mtr_pa.c_str());
	         	}
	         	hOQ.save_hash_scores(mtr_pa, TGT, REF, res);
	        }
			else { fprintf(stderr, "[ERROR] %s metric not available for language '%s'\n", mtr_pa.c_str(), Config::LANG.c_str()); exit(1); }
		}

        if (Config::serialize) hOQ.save_struct_scores(TB_FORMAT::make_serial(METEOR::MTREXT, TGT, REF));
	}

}
