#include "BLEU.hpp"
#include "Common.hpp"
#include "NISTXML.hpp"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <boost/filesystem.hpp>


const string BLEU::BLEUEXT = "BLEU";
const string BLEU::BLEUEXTi = "BLEUi";
const string BLEU::TBLEU = "mteval-kit";
map<string, int> create_rBLEU() {
	map<string, int> rBLEU;
	string aux;
	aux = BLEU::BLEUEXT + "-1";		rBLEU[aux] = 1;
	aux = BLEU::BLEUEXT + "-2";		rBLEU[aux] = 1;
	aux = BLEU::BLEUEXT + "-3";		rBLEU[aux] = 1;
	aux = BLEU::BLEUEXT + "-4";		rBLEU[aux] = 1;
	aux = BLEU::BLEUEXTi + "-2";		rBLEU[aux] = 1;
	aux = BLEU::BLEUEXTi + "-3";		rBLEU[aux] = 1;
	aux = BLEU::BLEUEXTi + "-4";		rBLEU[aux] = 1;
	return rBLEU;
}
const map<string, int> rBLEU = create_rBLEU();

read_bleu() {

}

pair<> computeBLEU() {
	string toolBLEU = "perl $tools/$BLEU::TBLEU/mteval-v13a.pl -b -d 2 ";
	if (case == Common::CASE_CS) toolBLEU += "-c ";

	srand(time(NULL));
	//double nr = rand() % (Common::NRAND + 1);	//random number [0, Common::NRAND];
	stringstream ssRef, ssSrc, ssOut, ssReport;
	ssRef << Common::DATA_PATH << "/" << Common::TMP << "/" << rand() % (Common::NRAND + 1) << "." << Common::REFEXT << "." << BLEU::BLEUEXT << "." << Common::SGMLEXT;
	ssSrc << Common::DATA_PATH << "/" << Common::TMP << "/" << rand() % (Common::NRAND + 1) << "." << Common::SRCEXT << "." << BLEU::BLEUEXT << "." << Common::SGMLEXT;
	ssOut << Common::DATA_PATH << "/" << Common::TMP << "/" << rand() % (Common::NRAND + 1) << "." << Common::SYSEXT << "." << BLEU::BLEUEXT << "." << Common::SGMLEXT;
	ssReport << Common::DATA_PATH << "/" << Common::TMP << "/" << rand() % (Common::NRAND + 1) << "." << BLEU::BLEUEXT << "." << Common::REPORTEXT;

    boost::filesystem::path refBLEUsgml(ssRef.str()));
    boost::filesystem::path srcBLEUsgml(ssSrc.str()));
    boost::filesystem::path outBLEUsgml(ssOut.str()));
    boost::filesystem::path reportBLEUsgml(ssReport.str()));

	if (!exists(refBLEUsgml) or remakeREPORTS) NISTXML::SGML_f_create_mteval_multidoc(refBLEUsgml.string(), 2, $verbose);
	if (!exists(srcBLEUsgml) or remakeREPORTS) NISTXML::SGML_f_create_mteval_multidoc(refBLEUsgml.string(), 0, $verbose);
	if (!exists(refBLEUsgml) or remakeREPORTS) NISTXML::SGML_f_create_mteval_multidoc(refBLEUsgml.string(), 1, $verbose);
	if (verbose > 1) fprintf(stderr, "building %s\n", reportBLEUsgml.string().c_str());

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

	SYS = read_bleu(reportBLEU);
	SEG = read_bleu_segments(reportBLEU);

	return make_pair(SYS, SEG);
}


void BLEU::doMetric(string TGT, string REF, string prefix, map<string, double> &hOQ) {
   // description _ computes BLEU score (by calling NIST mteval script) -> n = 1..4 (multiple references)
	string src = Config::src;
	int remakeREPORTS = Config::remake;
	string tools = Config::tools;
	map<string, int> M = Config::Hmetrics;
	int verbose = Config::verbose;

	int GO = 0;
	int i = 0;
	set<string> mBLEU;
	for (map<string, int>::const_iterator it = BLEU::rBLEU.begin(); it != rBLEU.end(); ++it) {
		mBLEU.insert(it->first);
	}
	while (i < mBLEU.size() and !GO) {
		string aux = prefix; aux += $mBLEU[i];
		if (M.find(aux) != M.end()) { GO = 1; }
		++i;
	}

	if (GO) {
		if (verbose == 1) fprintf(stderr, "%s\n", BLEU::BLEUEXT);
		stringstream ss1, ss2, ss3, ss4, ss2i, ss3i, ss4i;
		ss1 << Common::DATA_PATH << "/" << Common::REPORTS << "/" << TGT << "/" << REF << prefix << BLEU::BLEUEXT << "-1." << Common::XMLEXT;
		ss2 << Common::DATA_PATH << "/" << Common::REPORTS << "/" << TGT << "/" << REF << prefix << BLEU::BLEUEXT << "-2." << Common::XMLEXT;
		ss3 << Common::DATA_PATH << "/" << Common::REPORTS << "/" << TGT << "/" << REF << prefix << BLEU::BLEUEXT << "-3." << Common::XMLEXT;
		ss4 << Common::DATA_PATH << "/" << Common::REPORTS << "/" << TGT << "/" << REF << prefix << BLEU::BLEUEXT << "-4." << Common::XMLEXT;
		ss2i << Common::DATA_PATH << "/" << Common::REPORTS << "/" << TGT << "/" << REF << prefix << BLEU::BLEUEXTi << "-2." << Common::XMLEXT;
		ss3i << Common::DATA_PATH << "/" << Common::REPORTS << "/" << TGT << "/" << REF << prefix << BLEU::BLEUEXTi << "-3." << Common::XMLEXT;
		ss4i << Common::DATA_PATH << "/" << Common::REPORTS << "/" << TGT << "/" << REF << prefix << BLEU::BLEUEXTi << "-4." << Common::XMLEXT;

		string reportBLEU1xml = ss1.str();
		string reportBLEU2xml = ss2.str();
		string reportBLEU3xml = ss3.str();
		string reportBLEU4xml = ss4.str();
		string reportBLEUi2xml = ss2i.str();
		string reportBLEUi3xml = ss3i.str();
		string reportBLEUi4xml = ss4i.str();

	    boost::filesystem::path reportBLEU1xml_path(reportBLEU1xml);
		boost::filesystem::path reportBLEU2xml_pathreportBLEU1xml);
	    boost::filesystem::path reportBLEU3xml_path(reportBLEU1xml);
	    boost::filesystem::path reportBLEU4xml_path(reportBLEU1xml);
	    boost::filesystem::path reportBLEU2ixml_path(reportBLEU1xml);
	    boost::filesystem::path reportBLEU3ixml_path(reportBLEU1xml);
	    boost::filesystem::path reportBLEU4ixml_path(reportBLEU1xml);
		boost::filesystem::path reportBLEU1xml_ext(reportBLEU1xml + "." + Common::CZEXT);
	    boost::filesystem::path reportBLEU1xml_ext(reportBLEU1xml + "." + Common::CZEXT);
	    boost::filesystem::path reportBLEU1xml_ext(reportBLEU1xml + "." + Common::CZEXT);
	    boost::filesystem::path reportBLEU1xml_ext(reportBLEU1xml + "." + Common::CZEXT);
	    boost::filesystem::path reportBLEU1xml_ext(reportBLEU1xml + "." + Common::CZEXT);
	    boost::filesystem::path reportBLEU1xml_ext(reportBLEU1xml + "." + Common::CZEXT);
	    boost::filesystem::path reportBLEU1xml_ext(reportBLEU1xml + "." + Common::CZEXT);


	    if ( (!exists(reportBLEU1xml_path) and !exists(reportBLEU1xml_ext)) or \
	    (!exists(reportBLEU2xml_path) and !exists(reportBLEU2xml_ext)) or \
	    (!exists(reportBLEU3xml_path) and !exists(reportBLEU3xml_ext)) or \
	    (!exists(reportBLEU4xml_path) and !exists(reportBLEU4xml_ext)) or \
	    (!exists(reportBLEU2ixml_path) and !exists(reportBLEU2ixml_ext)) or \
	    (!exists(reportBLEU3ixml_path) and !exists(reportBLEU3ixml_ext)) or \
	    (!exists(reportBLEU4ixml_path) and !exists(reportBLEU4ixml_ext)) or remakeREPORTS) {


	    }

	}

}
