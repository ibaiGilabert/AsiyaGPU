#include "../include/ESA.hpp"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <iostream>
#include <fstream>
#include <sstream>

#include <boost/regex.hpp>
#include <boost/filesystem.hpp>
#include <boost/algorithm/string.hpp>


const string ESA::ESAEXT = "ESA";
const string ESA::TESAdir = "esa";
const string ESA::EMPTY_ITEM = "0";

map<string, string> ESA::create_TESA() {
	map<string, string> TESA;
	TESA[ESA::ESAEXT+"-en"] = "esa/SimilarityESAqe2.jar -l en";
	TESA[ESA::ESAEXT+"-es"] = "esa/SimilarityESAqe2.jar -l es";
	TESA[ESA::ESAEXT+"-de"] = "esa/SimilarityESAqe3.jar -l de";
	TESA[ESA::ESAEXT+"-fr"] = "esa/SimilarityESAqe59.jar -l fr";
	return TESA;
}
map<string, string> ESA::TESA = create_TESA();

map<string, string> ESA::create_TESA_java() {
	map<string, string> TESA_java;
	TESA_java[ESA::ESAEXT+"-en"] = "java ";
	TESA_java[ESA::ESAEXT+"-es"] = "java ";
	TESA_java[ESA::ESAEXT+"-de"] = "java ";
	TESA_java[ESA::ESAEXT+"-fr"] = "/usr/lib/jvm/java-7-openjdk-amd64/jre/bin/java ";
	return TESA_java;
}
map<string, string> ESA::TESA_java = create_TESA_java();

map<string, string> ESA::create_TESA_mem() {
	map<string, string> TESA_mem;
	TESA_mem[ESA::ESAEXT+"-en"] = " -Xms1024M -Xmx3072M ";
	TESA_mem[ESA::ESAEXT+"-es"] = " -Xms1G -Xmx3G";
	TESA_mem[ESA::ESAEXT+"-de"] = " -Xmx1G -Xmx3G";
	TESA_mem[ESA::ESAEXT+"-fr"] = " -Xmx1G -Xmx3G";
	return TESA_mem;
}
map<string, string> ESA::TESA_mem = create_TESA_mem();

map<string, string> ESA::create_TESAindex() {
	map<string, string> TESAindex;
	TESAindex[ESA::ESAEXT+"-en"] = "esa/esaindex";
	TESAindex[ESA::ESAEXT+"-es"] = "esa/es.index2";
	TESAindex[ESA::ESAEXT+"-de"] = "esa/de.index";
	TESAindex[ESA::ESAEXT+"-fr"] = "esa/fr.index";
	return TESAindex;
}
map<string, string> ESA::TESAindex = create_TESAindex();

set<string> ESA::create_rESA() {
	set<string> rESA;
	rESA.insert(ESA::ESAEXT+"-en");
	rESA.insert(ESA::ESAEXT+"-es");
	rESA.insert(ESA::ESAEXT+"-de");
	rESA.insert(ESA::ESAEXT+"-fr");
	return rESA;
}
set<string> ESA::rESA = create_rESA();

map<string, set<string> > ESA::create_rLANG() {
	map<string, set<string> > rLANG;
	set<string> rLANG_ENG, rLANG_SPA, rLANG_CAT, rLANG_GER, rLANG_FRN, rLANG_CZE;
	rLANG_CZE.insert(ESA::ESAEXT+"-en");	rLANG_ENG.insert(ESA::ESAEXT+"-en");
	rLANG_SPA.insert(ESA::ESAEXT+"-en");	rLANG_SPA.insert(ESA::ESAEXT+"-es");
	rLANG_CAT.insert(ESA::ESAEXT+"-en");	rLANG_CAT.insert(ESA::ESAEXT+"-es");
	rLANG_GER.insert(ESA::ESAEXT+"-en");	rLANG_GER.insert(ESA::ESAEXT+"-de");
	rLANG_FRN.insert(ESA::ESAEXT+"-en");	rLANG_FRN.insert(ESA::ESAEXT+"-fr");
	rLANG[Common::L_ENG] = rLANG_ENG;	rLANG[Common::L_SPA] = rLANG_SPA;
	rLANG[Common::L_CAT] = rLANG_CAT;	rLANG[Common::L_GER] = rLANG_GER;
	rLANG[Common::L_FRN] = rLANG_FRN;	rLANG[Common::L_CZE] = rLANG_CZE;
	return rLANG;
}
map<string, set<string> > ESA::rLANG = create_rLANG();


void ESA::ESA_f_create_doc(string input, string output) {
	// description _ creation of a RAW evaluation document
	if (Config::verbose) fprintf(stderr, "OPENING <%s> for ESA parsing...\n", input.c_str());

	if (exists(boost::filesystem::path(input))) {
		if (Config::verbose) fprintf(stderr, "reading <%s>\n", input.c_str());

	    ifstream input_file(input.c_str());
	    ofstream output_file(output.c_str());
	    if (!output_file) { fprintf(stderr, "couldn't open output file: %s\n", output.c_str()); exit(1); }
	    if (input_file) {
	    	string str;
  			boost::regex re("\\s*$"), re_1("^$"), re_2("^[!?.]+$");
			boost::match_results<string::const_iterator> results;
  			while (getline(input_file, str)) {
				str = boost::regex_replace(str, re, "");

				if (boost::regex_match(str, results, re_1) or boost::regex_match(str, results, re_2)) str = ESA::EMPTY_ITEM;

				//if (Config::CASE == Common::CASE_CI) boost::to_lower(str);
				boost::to_lower(str);
				output_file << str << endl;
			}
			output_file.close();
	        input_file.close();
	    } else { fprintf(stderr, "couldn't open input file: %s\n", input.c_str()); exit(1); }
	} else { fprintf(stderr, "\n[ERROR] UNAVAILABLE file <%s>!!!\n", input.c_str()); exit(1); }
}

vector<double> ESA::read_ESA_segments(string reportESA) {
	// description _ read ESA value from report file (for all segments)
    vector<double> aESA;

    ifstream file(reportESA.c_str());
    if (file) {
    	string str;
		getline(file, str);    // remove the header
	    while (getline(file, str))
	    	aESA.push_back(atof(str.c_str()));

	    file.close();
	} else { fprintf(stderr, "couldn't open file: %s\n", reportESA.c_str()); exit(1); }

	return aESA;
}

void ESA::computeESA(string metric, string out, string ref, vector<double> &SEG) {
	string outRND = out+"."+ESA::ESAEXT+"."+Config::CASE;
	string refRND = ref+"."+ESA::ESAEXT+"."+Config::CASE;

	ESA_f_create_doc(out, outRND);
	ESA_f_create_doc(ref, refRND);

	string outRND_gz = outRND+".esarep.obj.gz";
	string refRND_gz = refRND+".esarep.obj.gz";

	if (exists(boost::filesystem::path(outRND_gz))) {
		string sys_aux = "gunzip " + outRND_gz;
		system(sys_aux.c_str());
	}
	if (exists(boost::filesystem::path(refRND_gz))) {
		string sys_aux = "gunzip " + refRND_gz;
		system(sys_aux.c_str());
	}

	srand(time(NULL));
	stringstream ssReport;
	ssReport << Common::DATA_PATH << "/" << Common::TMP << "/" << rand()%(Common::NRAND + 1) << "." << ESA::ESAEXT << "." << Common::REPORTEXT;
	string reportESA = ssReport.str();

	if (Config::verbose) fprintf(stderr, "building %s...\n", reportESA.c_str());

	string pwd = boost::filesystem::current_path().string();

	boost::regex re("\\.\\/");
    boost::match_results<string::const_iterator> results;
    if (boost::regex_match(outRND, results, re)) {
		boost::regex_replace(outRND, re, "");
		outRND = pwd+"/"+outRND;
	}
	if (boost::regex_match(refRND, results, re)) {
    	boost::regex_replace(refRND, re, "");
		refRND = pwd+"/"+refRND;
	}
    if (boost::regex_match(reportESA, results, re)) {
		boost::regex_replace(reportESA, re, "");
		reportESA = pwd+"/"+reportESA;
	}

	string toolESA = ESA::TESA_java[metric]+" -Dfile.encoding=UTF-8 "+ESA::TESA_mem[metric]+" -jar "+Config::tools+"/"+ESA::TESA[metric];

	string sc = "cd "+Config::tools+"/"+ESA::TESAdir+"; "+toolESA+" -w "+Config::tools+"/"+ESA::TESAindex[metric]+" -i "+outRND+" -j "+refRND+" -o "+reportESA+" 2>"+reportESA+".err; cd "+pwd+";";
    cout << "[ESA] execute: " << sc << "|" << endl;

	Common::execute_or_die(sc, "[ERROR] problems running ESA...");

	SEG = read_ESA_segments(reportESA);

	string sysaux;
	sysaux = "rm -f "+refRND;				system(sysaux.c_str());
	sysaux = "gzip "+refRND+".esarep.obj";	system(sysaux.c_str());
	sysaux = "rm -f "+outRND;				system(sysaux.c_str());
	sysaux = "gzip "+outRND+".esarep.obj";	system(sysaux.c_str());
	sysaux = "rm -f "+reportESA;			system(sysaux.c_str());
	sysaux = "rm -f "+reportESA+".err";		system(sysaux.c_str());
}

void ESA::computeMultiESA(string metric, string out, double &MAXSYS, vector<double> &MAXSEG) {
	// description _ computes ESA score (multiple references)
    map<int, double> max_seg;
    for (map<string, string>::const_iterator it = TESTBED::Hrefs.begin(); it != TESTBED::Hrefs.end(); ++it) {
    	vector<double> hSEGS;
    	computeESA(metric, out, it->second, hSEGS);

    	for (int i = 0; i < hSEGS.size(); ++i) {
    		if (max_seg.find(i) != max_seg.end()) max_seg[i] = hSEGS[i];
    		else if (hSEGS[i] > max_seg[i]) max_seg[i] = hSEGS[i];
   		}
	}

	int i = 0;
	MAXSEG.resize(max_seg.size());
	for(map<int, double>::const_iterator it = max_seg.begin(); it != max_seg.end(); ++it, ++i) {
		MAXSEG[i] = it->second;
		MAXSYS += it->second;
	}

	MAXSYS /= MAXSEG.size();
}

void ESA::doMetric(string TGT, string REF, string prefix, Scores &hOQ) {
	// description _ computes ESA score (multiple references)
	vector<string> mESA(ESA::rESA.size());

	int GO, i;
	GO = i = 0;
	for (set<string>::const_iterator it = ESA::rLANG[Config::LANG].begin(); it != ESA::rLANG[Config::LANG].end(); ++it, ++i)
		mESA[i] = *it;

cout << "[ESA] Haviam el metric_set aquest si xuta..." << endl;
cout << "\t[ESA] mESA: ";
for (int k = 0; k < mESA.size(); ++k) cout << mESA[k] << ", ";
cout << endl;

	for (i = 0; i < mESA.size() and !GO; ++i) {
		if (Config::Hmetrics.find(mESA[i]) != Config::Hmetrics.end()) GO = 1;
	}

	if (GO) {
		if (Config::verbose) fprintf(stderr, "%s...\n", ESA::ESAEXT.c_str());

		for (i = 0; i < mESA.size() and !GO; ++i) {
			string reportESAxml = Common::DATA_PATH+"/"+Common::REPORTS+"/"+TGT+"/"+REF+"/"+prefix+mESA[i]+"."+Common::XMLEXT;
		    boost::filesystem::path reportESAxml_path(reportESAxml);
	   		boost::filesystem::path reportESAxml_gz(reportESAxml+"."+Common::GZEXT);
	   		if ( (!exists(reportESAxml_path) and !exists(reportESAxml_gz)) or Config::remake) {
	   			double SYS;
	   			vector<double> SEG, d_scores, s_scores;

	   			computeMultiESA(mESA[i], TESTBED::Hsystems[TGT], SYS, SEG);
				TESTBED::get_seg_doc_scores(SEG, 0, TGT, d_scores, s_scores);

				SC_ASIYA sc_asiya;
		    	string pref = prefix + mESA[i];
		    	if (Config::O_STORAGE == 1) {
					sc_asiya.write_report(TGT, REF, pref, SYS, d_scores, s_scores);
					fprintf(stderr, "SC_ASIYA DOCUMENT %s CREATED\n", pref.c_str());
				}
	         	hOQ.save_hash_scores(pref, TGT, REF, SYS, d_scores, s_scores);
		        if (Config::serialize) hOQ.save_struct_scores(TB_FORMAT::make_serial(ESA::ESAEXT, TGT, REF));
	   		}
		}
	}
}
