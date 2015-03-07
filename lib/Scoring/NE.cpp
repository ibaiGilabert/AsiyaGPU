#include "../include/NE.hpp"
#include "../include/SP.hpp"
#include "../include/Overlap.hpp"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <iostream>
#include <fstream>
#include <sstream>

#include <boost/regex.hpp>
#include <boost/filesystem.hpp>
#include <boost/algorithm/string.hpp>


const string NE::NEEXT = "NE";
const string NE::BIOS = "bios-1.1.0";

map<string, string> NE::create_rLANG() {
	map<string, string> rLANG;
	rLANG[Common::L_ENG] = "en";
	rLANG[Common::L_SPA] = "es";
	return rLANG;
}
const map<string, string> NE::rLANG = create_rLANG();

set<string> NE::create_rNEeng() {
	set<string> rNEeng;
	rNEeng.insert(NE::NEEXT+"-Oe(ANGLE_QUANTITY)");			rNEeng.insert(NE::NEEXT+"-Oe(DATE");
	rNEeng.insert(NE::NEEXT+"-Oe(DISTANCE_QUANTITY)");		rNEeng.insert(NE::NEEXT+"Oe(LANGUAGE)");
	rNEeng.insert(NE::NEEXT+"-Oe(LOC)");					rNEeng.insert(NE::NEEXT+"-Oe(METHOD)"); 			rNEeng.insert(NE::NEEXT+"-Oe(MISC)");
    rNEeng.insert(NE::NEEXT+"-Oe(MONEY)"); 					rNEeng.insert(NE::NEEXT+"-Oe(NUM)"); 				rNEeng.insert(NE::NEEXT+"-Oe(ORG)");
    rNEeng.insert(NE::NEEXT+"-Oe(PER)"); 					rNEeng.insert(NE::NEEXT+"-Oe(PERCENT)"); 			rNEeng.insert(NE::NEEXT+"-Oe(PROJECT)");
    rNEeng.insert(NE::NEEXT+"-Oe(SIZE_QUANTITY)"); 			rNEeng.insert(NE::NEEXT+"-Oe(SPEED_QUANTITY)");
    rNEeng.insert(NE::NEEXT+"-Oe(SYSTEM)"); 				rNEeng.insert(NE::NEEXT+"-Oe(TEMPERATURE_QUANTITY)");
    rNEeng.insert(NE::NEEXT+"-Oe(WEIGHT_QUANTITY)"); 		rNEeng.insert(NE::NEEXT+"-Oe(TIME)");				rNEeng.insert(NE::NEEXT+"-Oe(MEASURE)");
    rNEeng.insert(NE::NEEXT+"-Oe(O)"); 						rNEeng.insert(NE::NEEXT+"-Oe(*)"); 					rNEeng.insert(NE::NEEXT+"-Oe(**)");
    rNEeng.insert(NE::NEEXT+"-Me(ANGLE_QUANTITY)"); 		rNEeng.insert(NE::NEEXT+"-Me(DATE)");
    rNEeng.insert(NE::NEEXT+"-Me(DISTANCE_QUANTITY)"); 		rNEeng.insert(NE::NEEXT+"-Me(LANGUAGE)");	 		rNEeng.insert(NE::NEEXT+"-Me(LOC)");
    rNEeng.insert(NE::NEEXT+"-Me(METHOD)"); 				rNEeng.insert(NE::NEEXT+"-Me(MISC)"); 				rNEeng.insert(NE::NEEXT+"-Me(MONEY)");
    rNEeng.insert(NE::NEEXT+"-Me(NUM)"); 					rNEeng.insert(NE::NEEXT+"-Me(ORG)"); 				rNEeng.insert(NE::NEEXT+"-Me(PER)");
    rNEeng.insert(NE::NEEXT+"-Me(PERCENT)"); 				rNEeng.insert(NE::NEEXT+"-Me(PROJECT)"); 			rNEeng.insert(NE::NEEXT+"-Me(SIZE_QUANTITY)");
    rNEeng.insert(NE::NEEXT+"-Me(SPEED_QUANTITY)"); 		rNEeng.insert(NE::NEEXT+"-Me(SYSTEM)");
    rNEeng.insert(NE::NEEXT+"-Me(TEMPERATURE_QUANTITY)");	rNEeng.insert(NE::NEEXT+"-Me(WEIGHT_QUANTITY)");
    rNEeng.insert(NE::NEEXT+"-Me(TIME)"); 					rNEeng.insert(NE::NEEXT+"-Me(MEASURE)"); 			rNEeng.insert(NE::NEEXT+"-Me(*)");
    return rNEeng;
}
const set<string> NE::rNEeng = create_rNEeng();

set<string> NE::create_rNEengSmall() {
	set<string> rNEengSmall;
	rNEengSmall.insert(NE::NEEXT+"-Oe(PER)"); 	rNEengSmall.insert(NE::NEEXT+"-Oe(LOC)"); 	rNEengSmall.insert(NE::NEEXT+"-Oe(ORG)");
	rNEengSmall.insert(NE::NEEXT+"-Oe(MISC)");	rNEengSmall.insert(NE::NEEXT+"-Oe(NUM)"); 	rNEengSmall.insert(NE::NEEXT+"-Oe(DATE)");
	rNEengSmall.insert(NE::NEEXT+"-Oe(O)"); 	rNEengSmall.insert(NE::NEEXT+"-Oe(*)"); 	rNEengSmall.insert(NE::NEEXT+"-Oe(**)");
	rNEengSmall.insert(NE::NEEXT+"-Me(PER)"); 	rNEengSmall.insert(NE::NEEXT+"-Me(LOC)"); 	rNEengSmall.insert(NE::NEEXT+"-Me(ORG)");
	rNEengSmall.insert(NE::NEEXT+"-Me(MISC)"); 	rNEengSmall.insert(NE::NEEXT+"-Me(NUM)"); 	rNEengSmall.insert(NE::NEEXT+"-Me(DATE)");
	rNEengSmall.insert(NE::NEEXT+"-Me(*)");
	return rNEengSmall;
}
const set<string> NE::rNEengSmall = create_rNEengSmall();

const set<string> NE::rNEespcat;


//typedef map<string, map< string, map<string, int> > > SNTfeatures;
void NE::SNT_extract_features(const sParsed &snt, SNTfeatures &sntEXT) {
	// description _ extracts features from a given NE-parsed sentence.
	string type = "";
	vector<string> lne;
	boost::regex reB("^B-.*");
	boost::regex reI("^I-.*");

	for(int i = 0; i < snt.size(); ++i) {
		string word = snt[i][0];
		string ne = snt[i][ snt[i].size()-1 ];

		vector<string> NE;
		boost::split(NE, ne, boost::is_any_of("-"));
		// bags-of-words ---------------
		++sntEXT["bow"][(NE.size() == 1) ? NE[0] : NE[1]][word];
		// exact matches -----------------------
	 	boost::match_results<string::const_iterator> results;
	 	if (ne == "O" or boost::regex_match(ne, results, reB)) {
	 		if (lne.size() and type != "") {
	 			string lne_aux = lne[0];
	 			for (int j = 1; j < lne.size(); ++j) lne_aux += " " + lne[i];
	 			++sntEXT["exact"][type][lne_aux];
	 			type = NE[1];
	 			lne.clear();
	 			if (boost::regex_match(ne, results, reB)) lne.push_back(word);
	 		}
	 	}
	 	else if (boost::regex_match(ne, results, reI))
	 		lne.push_back(word);
	}
}

void NE::SNT_compute_overlap_scores(SNTfeatures &Tout, SNTfeatures &Tref, map<string, double> &SCORES) {
	// description _ computes distances between a candidate and a reference sentence (+features)

	// NE::NEEXT-Me(*) ----------------------------------------------------------------------------------
	double HITS = 0, TOTAL = 0;
	set<string> F;
	for (map<string, map<string, int> >::const_iterator it = Tout["exact"].begin(); it != Tout["exact"].end(); ++it)
		F.insert(it->first);
	for (map<string, map<string, int> >::const_iterator it = Tref["exact"].begin(); it != Tref["exact"].end(); ++it)
		F.insert(it->first);

	Overlap Ov;
	for (set<string>::const_iterator it = F.begin(); it != F.end(); ++it) {
		pair<double, double> hits_total = Ov.compute_overlap(Tout["exact"][*it], Tref["exact"][*it], (Config::CASE != Common::CASE_CI));
		SCORES[ NE::NEEXT+"-Me("+(*it)+")" ] = (hits_total.second == 0) ? 0 : (hits_total.first / hits_total.second);
		HITS += hits_total.first;
		TOTAL += hits_total.second;
	}
	SCORES[ NE::NEEXT+"-Me(*)" ] = (TOTAL == 0) ? 0 : (HITS / TOTAL);

	// NE::NEEXT-Oe(*) ----------------------------------------------------------------------------------
	HITS = 0;	TOTAL = 0;
	double HITSb = 0, TOTALb = 0;
	F.clear();
	for (map<string, map<string, int> >::const_iterator it = Tout["bow"].begin(); it != Tout["bow"].end(); ++it)
		F.insert(it->first);
	for (map<string, map<string, int> >::const_iterator it = Tref["bow"].begin(); it != Tref["bow"].end(); ++it)
		F.insert(it->first);

	for (set<string>::const_iterator it = F.begin(); it != F.end(); ++it) {
		pair<double, double> hits_total = Ov.compute_overlap(Tout["bow"][*it], Tref["bow"][*it], (Config::CASE != Common::CASE_CI));
		SCORES[ NE::NEEXT+"Oe-("+(*it)+")" ] = (hits_total.second == 0) ? 0 : (hits_total.first / hits_total.second);
		HITS += hits_total.first;
		TOTAL += hits_total.second;
		if (*it != "O") {
			HITSb += hits_total.first;
			TOTALb += hits_total.second;
		}
	}
	SCORES[ NE::NEEXT+"-Oe(*)" ] = (TOTALb == 0) ? 0 : (HITSb / TOTALb);
	SCORES[ NE::NEEXT+"-Oe(**)" ] = (TOTAL == 0) ? 0 : (HITS / TOTAL);
}
	void SNT_extract_features(const sParsed &snt, SNTfeatures &sntEXT);

void NE::FILE_compute_overlap_metrics(const vector<sParsed> &FDout, const vector<sParsed> &FDref, vector< map<string, double> > &SCORES) {
	// description _ computes NE scores (single reference)
	SCORES.resize(FDref.size());
	for (int topic = 0; topic < FDref.size(); ++topic) {
		SNTfeatures outSNT, refSNT;
		SNT_extract_features(FDout[topic], outSNT);
		SNT_extract_features(FDref[topic], refSNT);
	
		map<string, double> scores;
		SNT_compute_overlap_scores(outSNT, refSNT, scores);
		SCORES[topic] = scores;
	}
}

void NE::doMetric(string TGT, string REF, string prefix, Scores &hOQ) {
	// description _ computes NE scores (multiple references)
	set<string> rF;
	if (Config::LANG == Common::L_SPA or Config::LANG == Common::L_CAT)
		rF = NE::rNEespcat;
	else
		rF = NE::rNEeng;

	int GO_ON = 0;
	for (set<string>::const_iterator it = rF.begin(); it != rF.end(); ++it)
		if (Config::Hmetrics.count(*it)) GO_ON = 1;

	if (GO_ON) {
		if (Config::verbose) fprintf(stderr, "%s\n", NE::NEEXT.c_str());
		int DO_METRICS = Config::remake;
		
		if (!DO_METRICS) {
			for (set<string>::const_iterator it = rF.begin(); it != rF.end(); ++it) {
				string report_xml = Common::DATA_PATH+"/"+Common::REPORTS+"/"+TGT+"/"+REF+"/"+(*it)+"."+Common::XMLEXT;
				if ( Config::Hmetrics.count(*it) and !exists(boost::filesystem::path(report_xml)) and !exists(boost::filesystem::path(report_xml+"."+Common::GZEXT)) )
					DO_METRICS = 1;
			}

		}

		if (DO_METRICS) {
			SP sp;
			Overlap ov;
			vector<sParsed> FDout;
			sp.FILE_parse_and_read(TESTBED::Hsystems[TGT], Config::LANG, Config::CASE, FDout);

			vector< map<string, double> > max_scores(FDout.size());		// Assume size of FDout == FDref 
			for (map<string, string>::const_iterator itr = TESTBED::Hrefs.begin(); itr != TESTBED::Hrefs.end(); ++itr) {
				vector<sParsed> FDref;
				sp.FILE_parse_and_read(itr->second, Config::LANG, Config::CASE, FDref);

				vector< map<string, double> > scores;
				FILE_compute_overlap_metrics(FDout, FDref, scores);

				for (set<string>::const_iterator itf = rF.begin(); itf != rF.end(); ++itf) {
					if (Config::Hmetrics.count(*itf)) {
						double MAXSYS, SYS;
						vector<double> MAXSEGS, SEGS;

						ov.get_segment_scores(max_scores, *itf, 0, MAXSYS, MAXSEGS);
						ov.get_segment_scores(scores, *itf, 0, SYS, SEGS);

						for (int i = 0; i < SEGS.size(); ++i) {			// update max scores
							if (MAXSEGS[i] != Common::NOT_DEFINED) {
								if (SEGS[i] > MAXSEGS[i]) {
									if (scores[i].count(*itf)) {
										max_scores[i][*itf] = scores[i][*itf];
									}
								}
							}
							else 
								max_scores[i][*itf] = scores[i][*itf];
						}
					}
				}
			}

			for (set<string>::const_iterator itf = rF.begin(); itf != rF.end(); ++itf) {
				if (Config::Hmetrics.count(*itf)) {
					string report_xml = Common::DATA_PATH+"/"+Common::REPORTS+"/"+TGT+"/"+REF+"/"+(*itf)+"."+Common::XMLEXT;
					if ( !exists(boost::filesystem::path(report_xml)) and !exists(boost::filesystem::path(report_xml+"."+Common::GZEXT)) ) {
						double SYS;
						vector<double> SEGS, d_scores, s_scores;
						
						ov.get_segment_scores(max_scores, *itf, 2, SYS, SEGS);
						TESTBED::get_seg_doc_scores(SEGS, 0, TGT, d_scores, s_scores);
						if (Config::O_STORAGE == 1) {
				    		sc_asiya.write_report(TGT, REF, *itf, SYS, d_scores, s_scores);
			         		fprintf(stderr, "SC_ASIYA DOCUMENT %s CREATED\n", itf->c_str());
			         	}
			         	hOQ.save_hash_scores(*itf, TGT, REF, SYS, d_scores, s_scores);
					}

				}
			}
		}
	}
}