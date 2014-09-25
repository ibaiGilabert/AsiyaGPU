#include "../include/TER.hpp"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <iostream>
#include <sstream>

#include <boost/filesystem.hpp>


const string TER::TEREXT = "TER";
const string TER::TTERp = "terp.v1";	//v1

map<string, int> TER::create_rTER() {
	map<string, int> rTER;
	rTER["-" + TER::TEREXT] 			= 1;
	rTER["-" + TER::TEREXT + "base"]	= 1;
	rTER["-" + TER::TEREXT + "p"] 		= 1;
	rTER["-" + TER::TEREXT + "p-A"] 	= 1;
	return rTER;
}
const map<string, int> TER::rTER = create_rTER();


MetricScore TER::computeTER(string TGT, string variant, int do_neg) {
	// description _ computes -TERp score (multiple references)
	srand(time(NULL));
	double nr = rand() % (Common::NRAND + 1);	//random number [0, Common::NRAND];

	string sysid = TESTBED::IDX[TGT][1][2];

	stringstream ssOut, ssRef;
	ssOut << Common::DATA_PATH << "/" << Common::TMP << "/" << nr << "." << Common::SYSEXT << "." << TER::TEREXT << "." << Common::XMLEXT;
	ssRef << Common::DATA_PATH << "/" << Common::TMP << "/" << nr << "." << Common::REFEXT << "." << TER::TEREXT << "." << Common::XMLEXT;

    boost::filesystem::path outNISTxml(ssOut.str());
    boost::filesystem::path refNISTxml(ssRef.str());

    if (!exists(outNISTxml) or Config::remake)
    	NISTXML::f_create_mteval_doc(TESTBED::Hsystems[TGT], ssOut.str(), TGT, Common::CASE_CS, 1);
    if (!exists(refNISTxml) or Config::remake)
    	NISTXML::f_create_mteval_multidoc(ssRef.str(), Common::CASE_CS, 2);

    string mem_options = " -Xmx1024M ";	//cluster executions, write minimum 1G
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
    sc<<"java -Dfile.encoding=UTF-8 -jar "<<mem_options<<" "<<Config::tools<<"/"<<TER::TTERp<<"/dist/lib/terp.jar "<<phrase_db<<" "<<wn_dict<<" "<<caseopt<<" -n "<<Common::DATA_PATH<<"/"<<Common::TMP<<"/"<<nr<<". -o nist -r "<<ssRef.str()<<" -h "<<ssOut.str()<<" "<<param<<" ";
    string ms = "[ERROR] problems running TERp...";
    Common::execute_or_die(sc.str(), ms);

    stringstream aux;
    aux << Common::DATA_PATH << "/" << Common::TMP << "/" << nr << "." << sysid;
    MetricScore m_scores = Scores::read_scores(aux.str(), TGT, do_neg);

	if (exists(refNISTxml)) {
		string sysaux = "rm -f "; sysaux += ssRef.str();
		system (sysaux.c_str());
	}
	if (exists(outNISTxml)) {
		string sysaux = "rm -f "; sysaux += ssOut.str();
		system (sysaux.c_str());
	}

	return m_scores;
}

void TER::doMetric(string TGT, string REF, string prefix, Scores &hOQ) {
	// description _ computes -TER, -TERp and -TERp-A scores (multiple references)
	vector<string> mTER(TER::rTER.size());

	int GO , i;
	GO = i = 0;
	for (map<string, int>::const_iterator it = TER::rTER.begin(); it != TER::rTER.end(); ++it, ++i) {
		//mTER.insert(it->first);
		mTER[i] = it->first;
	}
	for (i = 0; i < mTER.size() and !GO; ++i) {
		if (Config::Hmetrics.find(mTER[i]) != Config::Hmetrics.end()) GO = 1;
	}

	cout << "TER ei!" << endl;
	if (GO) {
		cout << "GO! TER GO!" << endl;
		if (Config::verbose == 1) fprintf(stderr, "%sp...\n", TER::TEREXT.c_str());
		stringstream ssReport;
		ssReport << Common::DATA_PATH << "/" << Common::REPORTS << "/" << TGT << "/" << REF << "-" << TER::TEREXT << "base." << Common::XMLEXT;
		string reportTERreport = ssReport.str();
	    boost::filesystem::path reportTERreport_path(reportTERreport);
		boost::filesystem::path reportTERreport_gz(reportTERreport + "." + Common::GZEXT);

		string  ter_base = "-" + TER::TEREXT + "base";

	    if ( ((!exists(reportTERreport_path) and !exists(reportTERreport_gz)) or Config::remake) and Config::Hmetrics[ter_base]) {
	     	MetricScore res = computeTER(TGT, TER::TEREXT+"base", 1);

	    	if (Config::O_STORAGE == 1) {
	    		IQXML::write_report(TGT, REF, ter_base, res);
         		cout << "IQXML DOCUMENT " << ter_base << " CREATED" << endl;
         	}
         	hOQ.save_hash_scores(ter_base, TGT, REF, res);
	    }

	}
}
