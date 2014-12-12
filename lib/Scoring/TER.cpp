#include "../include/TER.hpp"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <iostream>
#include <sstream>

#include <boost/filesystem.hpp>


const string TER::TEREXT = "TER";
const string TER::TTERp = "terp.v1";	//v1

set<string> TER::create_rTER() {
	set<string> rTER;
	rTER.insert("-"+TER::TEREXT);
	rTER.insert("-"+TER::TEREXT+"base");
	rTER.insert("-"+TER::TEREXT+"p");
	rTER.insert("-"+TER::TEREXT+"p-A");
	return rTER;
}
const set<string> TER::rTER = create_rTER();


MetricScore TER::computeTER(string TGT, string variant, int do_neg, MetricScore &res) {
	// description _ computes -TERp score (multiple references)
	srand(time(NULL));
	double nr = rand() % (Common::NRAND + 1);	//random number [0, Common::NRAND];

	string sysid = TESTBED::IDX[TGT][1][2];
	string t_id;
    if (Config::serialize) t_id = "_" + TGT;//TB_FORMAT::get_formated_thread(TGT);

	stringstream ssOut, ssRef;
	ssOut << Common::DATA_PATH << "/" << Common::TMP << "/" << nr << "." << Common::SYSEXT << "." << TER::TEREXT << t_id << "." << Common::XMLEXT;
	ssRef << Common::DATA_PATH << "/" << Common::TMP << "/" << nr << "." << Common::REFEXT << "." << TER::TEREXT << t_id << "." << Common::XMLEXT;

    boost::filesystem::path outNISTxml(ssOut.str());
    boost::filesystem::path refNISTxml(ssRef.str());

    if (!exists(outNISTxml) or Config::remake)
    	TB_NIST::f_create_mteval_doc(TESTBED::Hsystems[TGT], ssOut.str(), TGT, Common::CASE_CS, 1);
    if (!exists(refNISTxml) or Config::remake)
    	TB_NIST::f_create_mteval_multidoc(ssRef.str(), Common::CASE_CS, 2);

    string mem_options = "-Xmx2G ";	//cluster executions, write minimum 1G
    string phrase_db, stop_words, wn_dict, param, caseopt;
    phrase_db = stop_words = "";
    wn_dict = param = "";

    if (caseopt == Common::CASE_CS ? "" : "-s");

    if (variant == TER::TEREXT+"base") param = Config::tools+"/"+TER::TTERp+"/data/ter.param";
    else if (variant == TER::TEREXT+"p") {
    	if (Config::LANG == Common::L_ENG) {
    		phrase_db = "-P "+Config::tools+"/"+TER::TTERp+"/data/phrases.db";
    		stop_words = "-S "+Config::tools+"/"+TER::TTERp+"/data/shift_word_stop_list.txt";
    		wn_dict = "-d "; wn_dict += getenv("WNDICT");
    	}
    }
    else if (variant == TER::TEREXT+"p-A") {
    	param = Config::tools+"/"+TER::TTERp+"/data/terpa.param";
    	if (Config::LANG == Common::L_ENG) {
    		phrase_db = "-P "+Config::tools+"/"+TER::TTERp+"/data/phrases.db";
    		stop_words = "-S "+Config::tools+"/"+TER::TTERp+"/data/shift_word_stop_list.txt";
    		wn_dict = "-d "; wn_dict += getenv("WNDICT");
    	}
    }
    else { fprintf(stderr, "[ERROR] unknown TERp variant <%s>\n", variant.c_str()); exit(1); }

    stringstream sc;
    sc<<"java -Dfile.encoding=UTF-8 -jar "<<mem_options<<Config::tools<<"/"<<TER::TTERp<<"/dist/lib/terp.jar "<<phrase_db<<" "<<wn_dict<<" "<<caseopt<<" -n "<<Common::DATA_PATH<<"/"<<Common::TMP<<"/"<<nr<<". -o nist -r "<<ssRef.str()<<" -h "<<ssOut.str()<<" "<<param<<" ";

    string ms = "[ERROR] problems running TERp...";
    cout << "[TER] execute: " << sc.str() << endl;
    Common::execute_or_die(sc.str(), ms);

    stringstream basename;
    basename << Common::DATA_PATH << "/" << Common::TMP << "/" << nr << "." << sysid;
fprintf(stderr, "[TER]: Fuck read! (%s) /TGT: (%s)\n", basename.str().c_str(), TGT.c_str());

    res = Scores::read_scores(basename.str(), TGT, ".", do_neg);

	if (exists(refNISTxml)) {
		string sysaux = "rm -f "; sysaux += ssRef.str();
		system (sysaux.c_str());
	}
	if (exists(outNISTxml)) {
		string sysaux = "rm -f "; sysaux += ssOut.str();
		system (sysaux.c_str());
	}
}

void TER::doMetric(string TGT, string REF, string prefix, Scores &hOQ) {
	// description _ computes -TER, -TERp and -TERp-A scores (multiple references)
	vector<string> mTER(TER::rTER.size());

	int GO , i;
	GO = i = 0;
	for (set<string>::const_iterator it = TER::rTER.begin(); it != TER::rTER.end(); ++it, ++i)
		mTER[i] = *it;

	for (i = 0; i < mTER.size() and !GO; ++i) {
		if (Config::Hmetrics.find(mTER[i]) != Config::Hmetrics.end()) GO = 1;
	}

	if (GO) {
		if (Config::verbose) fprintf(stderr, "%sp...\n", TER::TEREXT.c_str());

	    SC_ASIYA sc_asiya;

	    string pref_ter = "-"+TER::TEREXT+"base";
		string reportTERxml = Common::DATA_PATH + "/" + Common::REPORTS + "/" + TGT + "/" + REF + "/" + pref_ter + "." + Common::XMLEXT;
    	if ( ((!exists(boost::filesystem::path(reportTERxml)) and !exists(boost::filesystem::path(reportTERxml+"."+Common::GZEXT))) or Config::remake) and Config::Hmetrics[pref_ter]) {
	     	MetricScore res;
	     	computeTER(TGT, TER::TEREXT+"base", 1, res);

 			if (Config::O_STORAGE == 1) {
	    		sc_asiya.write_report(TGT, REF, pref_ter, res);
         		cout << "SC_ASIYA DOCUMENT " << pref_ter << " CREATED" << endl;
         	}
         	hOQ.save_hash_scores(pref_ter, TGT, REF, res);
	    }
	    pref_ter = TER::TEREXT + "base";
    	reportTERxml = Common::DATA_PATH + "/" + Common::REPORTS + "/" + TGT + "/" + REF + "/" + pref_ter + "." + Common::XMLEXT;
	    if ( ((!exists(boost::filesystem::path(reportTERxml)) and !exists(boost::filesystem::path(reportTERxml+"."+Common::GZEXT))) or Config::remake) and Config::Hmetrics[pref_ter]) {
	     	MetricScore res;
	     	computeTER(TGT, TER::TEREXT+"base", 0, res);

	     	if (Config::O_STORAGE == 1) {
	    		sc_asiya.write_report(TGT, REF, pref_ter, res);
         		cout << "SC_ASIYA DOCUMENT " << pref_ter << " CREATED" << endl;
         	}
         	hOQ.save_hash_scores(pref_ter, TGT, REF, res);
	    }
	    pref_ter = "-"+TER::TEREXT;
	    reportTERxml = Common::DATA_PATH + "/" + Common::REPORTS + "/" + TGT + "/" + REF + "/" + pref_ter + "." + Common::XMLEXT;
	    if ( ((!exists(boost::filesystem::path(reportTERxml)) and !exists(boost::filesystem::path(reportTERxml+"."+Common::GZEXT))) or Config::remake) and Config::Hmetrics[pref_ter]) {
	     	MetricScore res;
	     	computeTER(TGT, TER::TEREXT, 1, res);

	     	if (Config::O_STORAGE == 1) {
	    		sc_asiya.write_report(TGT, REF, pref_ter, res);
         		cout << "SC_ASIYA DOCUMENT " << pref_ter << " CREATED" << endl;
         	}
         	hOQ.save_hash_scores(pref_ter, TGT, REF, res);
	    }
	    pref_ter = TER::TEREXT;
	    reportTERxml = Common::DATA_PATH + "/" + Common::REPORTS + "/" + TGT + "/" + REF + "/" + pref_ter + "." + Common::XMLEXT;
	    if ( ((!exists(boost::filesystem::path(reportTERxml)) and !exists(boost::filesystem::path(reportTERxml+"."+Common::GZEXT))) or Config::remake) and Config::Hmetrics[pref_ter]) {
	     	MetricScore res;
	     	computeTER(TGT, TER::TEREXT, 0, res);

	     	if (Config::O_STORAGE == 1) {
	    		sc_asiya.write_report(TGT, REF, pref_ter, res);
         		cout << "SC_ASIYA DOCUMENT " << pref_ter << " CREATED" << endl;
         	}
         	hOQ.save_hash_scores(pref_ter, TGT, REF, res);
	    }
	    pref_ter = "-" + TER::TEREXT + "p";
	    reportTERxml = Common::DATA_PATH + "/" + Common::REPORTS + "/" + TGT + "/" + REF + "/" + pref_ter + "." + Common::XMLEXT;
	    if ( ((!exists(boost::filesystem::path(reportTERxml)) and !exists(boost::filesystem::path(reportTERxml+"."+Common::GZEXT))) or Config::remake) and Config::Hmetrics[pref_ter]) {
	     	MetricScore res;
	     	computeTER(TGT, TER::TEREXT+"p", 1, res);

	     	if (Config::O_STORAGE == 1) {
	    		sc_asiya.write_report(TGT, REF, pref_ter, res);
         		cout << "SC_ASIYA DOCUMENT " << pref_ter << " CREATED" << endl;
         	}
         	hOQ.save_hash_scores(pref_ter, TGT, REF, res);
	    }
	    pref_ter = TER::TEREXT + "p";
	    reportTERxml = Common::DATA_PATH + "/" + Common::REPORTS + "/" + TGT + "/" + REF + "/" + pref_ter + "." + Common::XMLEXT;
	    if ( ((!exists(boost::filesystem::path(reportTERxml)) and !exists(boost::filesystem::path(reportTERxml+"."+Common::GZEXT))) or Config::remake) and Config::Hmetrics[pref_ter]) {
	     	MetricScore res;
	     	computeTER(TGT, TER::TEREXT+"p", 0, res);

	     	if (Config::O_STORAGE == 1) {
	    		sc_asiya.write_report(TGT, REF, pref_ter, res);
         		cout << "SC_ASIYA DOCUMENT " << pref_ter << " CREATED" << endl;
         	}
         	hOQ.save_hash_scores(pref_ter, TGT, REF, res);
	    }
	    pref_ter = "-" + TER::TEREXT + "p-A";
	    reportTERxml = Common::DATA_PATH + "/" + Common::REPORTS + "/" + TGT + "/" + REF + "/" + pref_ter + "." + Common::XMLEXT;
	    if ( ((!exists(boost::filesystem::path(reportTERxml)) and !exists(boost::filesystem::path(reportTERxml+"."+Common::GZEXT))) or Config::remake) and Config::Hmetrics[pref_ter]) {
	     	MetricScore res;
	     	computeTER(TGT, TER::TEREXT+"p-A", 1, res);

	     	if (Config::O_STORAGE == 1) {
	    		sc_asiya.write_report(TGT, REF, pref_ter, res);
         		cout << "SC_ASIYA DOCUMENT " << pref_ter << " CREATED" << endl;
         	}
         	hOQ.save_hash_scores(pref_ter, TGT, REF, res);
	    }
	    pref_ter = TER::TEREXT + "p-A";
	    reportTERxml = Common::DATA_PATH + "/" + Common::REPORTS + "/" + TGT + "/" + REF + "/" + pref_ter + "." + Common::XMLEXT;
	    if ( ((!exists(boost::filesystem::path(reportTERxml)) and !exists(boost::filesystem::path(reportTERxml+"."+Common::GZEXT))) or Config::remake) and Config::Hmetrics[pref_ter]) {
	     	MetricScore res;
	     	computeTER(TGT, TER::TEREXT+"p-A", 0, res);

	     	if (Config::O_STORAGE == 1) {
	    		sc_asiya.write_report(TGT, REF, pref_ter, res);
         		cout << "SC_ASIYA DOCUMENT " << pref_ter << " CREATED" << endl;
         	}
         	hOQ.save_hash_scores(pref_ter, TGT, REF, res);
	    }
	}
}
