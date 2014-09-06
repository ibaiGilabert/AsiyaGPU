#include "ESA.hpp"
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
//#include <boost/algorithm/string.hpp>


const string ESA::ESAXT = "ESA";
const string ESA::TESAdir = "esa";
const string ESA::EMPTY_ITEM = "0";

map<string, string> ESA::create_TESA() {
	map<string, string> TESA;
	TESA[ESA::ESAEXT + "-en"] = "esa/SimilarityESAqe2.jar -l en";
	TESA[ESA::ESAEXT + "-es"] = "esa/SimilarityESAqe2.jar -l es";
	TESA[ESA::ESAEXT + "-de"] = "esa/SimilarityESAqe3.jar -l de";
	TESA[ESA::ESAEXT + "-fr"] = "esa/SimilarityESAqe59.jar -l fr";
	return TESA;
}
const map<string, string> ESA::TESA = create_TESA;

map<string, string> ESA::create_TESA_java() {
	map<string, string> TESA_java;
	TESA_java[ESA::ESAEXT + "-en"] = "java ";
	TESA_java[ESA::ESAEXT + "-es"] = "java ";
	TESA_java[ESA::ESAEXT + "-de"] = "java ";
	TESA_java[ESA::ESAEXT + "-fr"] = "/usr/lib/jvm/java-7-openjdk-amd64/jre/bin/java ";
	return TESA_java;
}
const map<string, string> ESA::TESA_java = create_TESA_java;

map<string, string> ESA::create_TESA_mem() {
	map<string, string> TESA_mem;
	TESA_mem[ESA::ESAEXT + "-en"] = " -Xms1024M -Xmx3072M ";
	TESA_mem[ESA::ESAEXT + "-es"] = " -Xms1G -Xmx3G";
	TESA_mem[ESA::ESAEXT + "-de"] = " -Xmx1G -Xmx3G";
	TESA_mem[ESA::ESAEXT + "-fr"] = " -Xmx1G -Xmx3G";
	return TESA_mem;
}
const map<string, string> ESA::TESA_mem = create_TESA_mem;

map<string, string> ESA::create_TESAindex() {
	map<string, string> TESAindex;
	TESAindex[ESA::ESAEXT + "-en"] = "esa/esaindex";
	TESAindex[ESA::ESAEXT + "-es"] = "esa/es.index2";
	TESAindex[ESA::ESAEXT + "-de"] = "esa/de.index";
	TESAindex[ESA::ESAEXT + "-fr"] = "esa/fr.index";
	return TESAindex;
}
const map<string, string> ESA::TESAindex = create_TESAindex;

map<string, int> ESA::create_rESA() {
	map<string, int> rESA;
	rESA[ESA::ESAEXT + "-en"] = 1;
	rESA[ESA::ESAEXT + "-es"] = 1;
	rESA[ESA::ESAEXT + "-de"] = 1;
	rESA[ESA::ESAEXT + "-fr"] = 1;
	return rESA;
}
const map<string, int> ESA::rESA = create_rESA;

map<string, map<string, int> > ESA::create_rLANG() {
	map<string, map<string, int> > rLANG;
	map<string, int> rLANG_ENG, rLANG_SPA, rLANG_CAT, rLANG_GER, rLANG_FRN, rLANG_CZE;
	rLANG_ENG[ESA::ESAEXT + "-en"] = 1;
	rLANG_SPA[ESA::ESAEXT + "-en"] = 1;	rLANG_SPA[ESA::ESAEXT + "-es"] = 1;
	rLANG_CAT[ESA::ESAEXT + "-en"] = 1;	rLANG_CAT[ESA::ESAEXT + "-es"] = 1;
	rLANG_GER[ESA::ESAEXT + "-en"] = 1;	rLANG_GER[ESA::ESAEXT + "-de"] = 1;
	rLANG_FRN[ESA::ESAEXT + "-en"] = 1;	rLANG_FRN[ESA::ESAEXT + "-fr"] = 1;
	rLANG_CZE[ESA::ESAEXT + "-en"] = 1;
	rLANG[Common::L_ENG] = rLANG_ENG;	rLANG[Common::L_SPA] = rLANG_SPA;
	rLANG[Common::L_CAT] = rLANG_CAT;	rLANG[Common::L_GER] = rLANG_GER;
	rLANG[Common::L_FRN] = rLANG_FRN;	rLANG[Common::L_CZE] = rLANG_CZE;
	return rLANG;
}
const map<string, int> ESA::rLANG = create_rLANG;


ESA::ESA_f_create_doc(string input, string output) {
	// description _ creation of a RAW evaluation document
	if (Config::verbose > 1) fprintf(stderr, "OPENING <%s> for ESA parsing...\n", input.c_str());

    boost::filesystem::path input_path(input);
    if (exists(input_path)) {
    	if (Config::verbose > 1) fprintf(stderr, "reading <%s>\n", input.c_str());

    	ifstream input_file(input.c_str());
    }
}
ESA::computeESA(string TGT, string ref) {
	string outRND = Config::Hsystems[TGT]+"."+ESA::ESAEXT+"."+Config::CASE;;
	string refRND = ref+"."+ESA::ESAEXT+"."+Config::CASE;

	ESA_f_create_doc(Config::Hsystems[TGT], outRND);
	ESA_f_create_doc(ref, refRND);

	stringstream ssReport;
	ssReport << Common::DATA_PATH << "/" << Common::TMP << "/" << rand() % (Common::NRAND + 1) << "." << ESA::ESAEXT << "." << Common::REPORTEXT;
	string reportESA = ssReport.str();

	if (Config::verbose > 1) fprintf(stderr, "building %s...\n", reportESA.c_str());

	boost::filesystem::path path( boost::filesystem::current_path() );

	bost::regex re("")
    boost::match_results<string::const_iterator> results;
	if (boost::regex_match(str, results, re)) {
		s
	}

}



            boost::match_results<string::const_iterator> results;
            if (boost::regex_match(str, results, re)) {
                //cout << "\t That was a kind of line" << endl;

                string s = results[0];

                boost::regex reeq("=");
                boost::sregex_token_iterator i(s.begin(), s.end(), reeq, -1);

                string type = *i++;
                string data = *i;

                boost::regex re("\\s*$");//, boost::regex::perl|boost::regex::icase);
                boost::regex re2("^\\s*");//, boost::regex::perl|boost::regex::icase);

                type = boost::regex_replace(type, re, "");
                data = boost::regex_replace(data, re2, "");




pair<vector<double>, vector<vector<double> > > ESA::computeMultiESA(string TGT) {
	// description _ computes ESA score (multiple references)
    for (map<string, string>::const_iterator it = Config::Hrefs.begin(); it != Config::Hrefs.end(); ++it) {
    	computeESA(TGT, it->second);

	}
}

void ESA::doMetric(string TGT, string REF, string prefix, int stemming, Scores &hOQ) {
	// description _ computes ESA score (multiple references)
	vector<string> mESA(ESA::rESA.size());

	int GO, i;
	GO = i = 0;
	for (map<string, int>::const_iterator it = ESA::rESA[Config::LANG].begin(); it != ESA::rESA[Config::LANG].end(); ++it, ++i) {
		mESA[i] = it->first;
	}
	for (i = 0; i < mESA.size() and !GO; ++i) {
		if (Config::Hmetrics.find(mESA[i]) != Config::Hmetrics.end()) GO = 1;
	}

	cout << "ESA ei!" << endl;
	if (GO) {
		cout << "GO! ESA GO!" << endl;
		if (Config::verbose == 1) fprintf(stderr, "%s...\n", ESA::ESAXT.c_str());
		for (i = 0; i < mESA.size() and !GO; ++i) {
			ss << Common::DATA_PATH << "/" << Common::REPORTS << "/" << TGT << "/" << REF << "/" << prefix << mESA[i] << "." << Common::XMLEXT;
			string reportESAxml = ss.string();
		    boost::filesystem::path reportESAxml_path(reportESAxml);
	   		boost::filesystem::path reportESAxml_gz(reportESAxml + "." + Common::GZEXT);

	   		if ( (!exists(reportESAxml_path) and !exists(reportESAxml_gz)) or Config::remake) {
	    		pair<vector<double>, vector<vector<double> > > res = computeMultiESA(TGT);
	   		}
		}
	}
}
