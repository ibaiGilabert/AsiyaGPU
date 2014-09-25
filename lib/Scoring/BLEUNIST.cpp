#include "../include/BLEUNIST.hpp"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <iostream>
#include <sstream>

#include <boost/filesystem.hpp>

const string BLEUNIST::BLEUEXT = "BLEU";
const string BLEUNIST::NISTEXT = "NIST";
const string BLEUNIST::TBLEUNIST = "mteval-kit";

map<string, int> BLEUNIST::create_rBLEUNIST() {
	map<string, int> rBLEUNIST;
	rBLEUNIST[BLEUNIST::BLEUEXT] = 1;
	rBLEUNIST[BLEUNIST::NISTEXT] = 1;
	return rBLEUNIST;
}
const map<string, int> BLEUNIST::rBLEUNIST = create_rBLEUNIST();

map<string, int> BLEUNIST::create_rBLEU() {
	map<string, int> rBLEU;
	rBLEU[BLEUNIST::BLEUEXT] = 1;
	return rBLEU;
}
const map<string, int> BLEUNIST::rBLEU = create_rBLEU();

map<string, int> BLEUNIST::create_rNIST() {
	map<string, int> rNIST;
	rNIST[BLEUNIST::NISTEXT] = 1;
	return rNIST;
}
const map<string, int> BLEUNIST::rNIST = create_rNIST();




pair<MetricScore, MetricScore> BLEUNIST::computeBLEUNIST(string TGT) {
	// description _ computes smoothed BLEU-4 score and NIST-5 score (by calling NIST mteval script) (multiple references)
	stringstream tBLEUNIST;

	tBLEUNIST << "perl " << Config::tools << "/" << BLEUNIST::TBLEUNIST << "/" << "mteval-v13a.pl --metricsMATR -d 2 ";

	if (Config::CASE == Common::CASE_CS) tBLEUNIST << "-c ";
	string toolBLEUNIST = tBLEUNIST.str();

	cout << "toolBLEUNIST ->" << toolBLEUNIST << endl << endl;

	srand(time(NULL));
	double nr = rand() % (Common::NRAND + 1);	//random number [0, Common::NRAND];
	stringstream ssSrc, ssOut, ssRef;
	ssSrc << Common::DATA_PATH << "/" << Common::TMP << "/" << nr << "." << Common::SRCEXT << "." << BLEUNIST::NISTEXT << "." << Common::XMLEXT;
	ssOut << Common::DATA_PATH << "/" << Common::TMP << "/" << nr << "." << Common::SYSEXT << "." << BLEUNIST::NISTEXT << "." << Common::XMLEXT;
	ssRef << Common::DATA_PATH << "/" << Common::TMP << "/" << nr << "." << Common::REFEXT << "." << BLEUNIST::NISTEXT << "." << Common::XMLEXT;


    boost::filesystem::path srcXML(ssSrc.str());
    boost::filesystem::path outXML(ssOut.str());
    boost::filesystem::path refXML(ssRef.str());

    if (!exists(srcXML) or Config::remake) NISTXML::f_create_mteval_doc(TESTBED::src, srcXML.string(), TGT, Common::CASE_CS, 0);
    if (!exists(outXML) or Config::remake) NISTXML::f_create_mteval_doc(TESTBED::Hsystems[TGT], outXML.string(), TGT, Common::CASE_CS,  1);
    if (!exists(refXML) or Config::remake) NISTXML::f_create_mteval_multidoc(refXML.string(), Common::CASE_CS, 2);

    stringstream sc;
    sc << "cd " << Common::DATA_PATH << "; " << toolBLEUNIST << " -s " << ssSrc.str() << " -t " << ssOut.str() << " -r " << ssRef.str() << " >/dev/null 2>/dev/null";

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

	MetricScore BLEU_scores = Scores::read_scores(Common::DATA_PATH + "/BLEU", TGT, 0);
	MetricScore NIST_scores = Scores::read_scores(Common::DATA_PATH + "/NIST", TGT, 0);

	return make_pair(BLEU_scores, NIST_scores);
}

void BLEUNIST::doMetric(string TGT, string REF, string prefix, Scores &hOQ) {
	// description _ computes smoothed BLEU-4 score and NIST-5 score (multiple references)
	//map<string, int> M = Config::Hmetrics;
	vector<string> mBLEUNIST(BLEUNIST::rBLEUNIST.size());

	int GO , i;
	GO = i = 0;
	for (map<string, int>::const_iterator it = BLEUNIST::rBLEUNIST.begin(); it != BLEUNIST::rBLEUNIST.end(); ++it) mBLEUNIST[i++] = it->first;

	i = 0;
	while (i < mBLEUNIST.size() and !GO) {
		string aux = prefix; aux += mBLEUNIST[i];
		if (Config::Hmetrics.find(aux) != Config::Hmetrics.end()) GO = 1;
		++i;
	}

	if (GO) {
		if (Config::verbose == 1) fprintf(stderr, "%s..%s..\n", BLEUNIST::BLEUEXT.c_str(), BLEUNIST::NISTEXT.c_str());
		stringstream ssB, ssN;
		ssB << Common::DATA_PATH << "/" << Common::REPORTS << "/" << TGT << "/" << REF << prefix << BLEUNIST::BLEUEXT << "." << Common::XMLEXT;
		ssN << Common::DATA_PATH << "/" << Common::REPORTS << "/" << TGT << "/" << REF << prefix << BLEUNIST::NISTEXT << "." << Common::XMLEXT;


		string reportBLEUxml = ssB.str();
		string reportNISTxml = ssN.str();

	    boost::filesystem::path reportBLEUxml_path(reportBLEUxml);
		boost::filesystem::path reportNISTxml_path(reportNISTxml);

		boost::filesystem::path reportBLEUxml_ext(reportBLEUxml + "." + Common::GZEXT);
	    boost::filesystem::path reportNISTxml_ext(reportNISTxml + "." + Common::GZEXT);

	    if ( (!exists(reportBLEUxml_path) and !exists(reportBLEUxml_ext)) or \
	    (!exists(reportNISTxml_path) and !exists(reportNISTxml_ext)) or Config::remake) {
            // BLEUNIST::computeMultiBLEUNIST( $src, $out, $Href, $TGT, $config->{IDX}, $remakeREPORTS, $config->{CASE}, $tools, $verbose);
	    	pair<MetricScore, MetricScore> res = computeBLEUNIST(TGT);
	    	MetricScore BLEUscores = res.first;
	    	MetricScore NISTscores = res.second;

         	string pref = prefix + BLEUNIST::BLEUEXT;
	    	if (Config::O_STORAGE == 1) {
	    		IQXML::write_report(TGT, REF, pref, BLEUscores.sys_score, BLEUscores.doc_scores, BLEUscores.seg_scores);
         		cout << "IQXML DOCUMENT " << pref << " CREATED" << endl;
         	}
         	//hOQ.save_hash_scores(pref, TGT, REF, BLEUscores.sys_score, BLEUscores.doc_scores, BLEUscores.seg_scores);
         	hOQ.save_hash_scores(pref, TGT, REF, BLEUscores);

			pref = prefix + BLEUNIST::NISTEXT;
			if (Config::O_STORAGE == 1) {
	    		IQXML::write_report(TGT, REF, pref, NISTscores.sys_score, NISTscores.doc_scores, NISTscores.seg_scores);
         		cout << "IQXML DOCUMENT " << pref << " CREATED" << endl;
         	}
	    	//hOQ.save_hash_scores(pref, TGT, REF, NISTscores.sys_score, NISTscores.doc_scores, NISTscores.seg_scores);
	    	hOQ.save_hash_scores(pref, TGT, REF, NISTscores);


	    	cout << "------------SCORES: BLEUNIST-----------" << endl;
	    	hOQ.print_scores();
	    	cout << "---------------------------------------" << endl;
	    	//exit(1);
	    }

	}

}