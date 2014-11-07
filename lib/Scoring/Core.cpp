#include "../Config.hpp"
#include "../include/TESTBED.hpp"
#include "../include/Core.hpp"
#include "../include/BLEU.hpp"
#include "../include/NIST.hpp"
//#include "../include/BLEUNIST.hpp"
#include "../include/METEOR.hpp"
#include "../include/ROUGE.hpp"
#include "../include/GTM.hpp"
#include "../include/TER.hpp"
#include "../include/SC_RAW.hpp"

#include <omp.h>
#include <stdio.h>
#include <iostream>
#include <fstream>

#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
//#include <boost/serialization/string.hpp>
//#include <boost/serialization/map.hpp>

vector<string> Core::get_sorted_metrics() {
	vector<string> sorted_metrics;

	set<string> st = Config::metrics;
	if (Config::eval_schemes[Common::S_SINGLE]) {
		sorted_metrics = vector<string>(st.begin(), st.end());

			//sorted_metrics = vector<string>(Config::metrics.begin(), Config::metrics().end());
		//if (Config::SORT == Common::SORT_NAME) //already sorted (set)
	}
//if (Config::eval_schemes[Common::S_ULC]) sorted_metrics.push_back(ULC::ULC_NAME);
//if (Config::eval_schemes[Common::S_QUEEN]) sorted_metrics.push_back(QARLA::QUEEN);

	return sorted_metrics;
}

vector<string> Core::get_sorted_systems() {
	vector<string> sorted_systems;

	set<string> st = Config::systems;
	sorted_systems = vector<string>(Config::systems.begin(), Config::systems.end());

	return sorted_systems;
}
/*
   my %HREF;
   my @sorted_refs = sort @{$Lref};
   foreach my $r (@sorted_refs) { if (exists($Href->{$r})) { $HREF{$r} = $Href->{$r}; } }
   my $REF = join("_", sort keys %HREF);

   if ($verbose > 1) { print STDERR "computing similarities [$HYP]...\n"; }
   elsif ($verbose == 1) { print STDERR "$HYP - $REF ["; }


   CE::doCE($config, $HYP, $HYP_file, $REF, $hOQ);			//Confident Estimation
   LeM::doMultiLeM($config, $HYP, $HYP_file, $REF, $hOQ);

   if (scalar(@{$Lref}) > 0) {
      BLEU::doMultiBLEU($config, $HYP, $HYP_file, $REF, \%HREF, "", $hOQ);
      NIST::doMultiNIST($config, $HYP, $HYP_file, $REF, \%HREF, "", $hOQ);
      BLEUNIST::doMultiBLEUNIST($config, $HYP, $HYP_file, $REF, \%HREF, "", $hOQ);
      NGRAM::doMultiNGRAM($config, $HYP, $HYP_file, $REF, \%HREF, "", $hOQ);
      ESA::doMultiESA($config, $HYP, $HYP_file, $REF, \%HREF, "", $hOQ);
      WER::doMultiWER($config, $HYP, $HYP_file, $REF, \%HREF, $hOQ);
      PER::doMultiPER($config, $HYP, $HYP_file, $REF, \%HREF, $hOQ);
      TERp::doMultiTER($config, $HYP, $HYP_file, $REF, \%HREF, $hOQ);
      Overlap::doMultiOl($config, $HYP, $HYP_file, $REF, \%HREF, $hOQ);
      Align::doMultiAr($config, $HYP, $HYP_file, $REF, \%HREF, $hOQ);
      GTM::doMultiGTM($config, $HYP, $HYP_file, $REF, \%HREF, "", $hOQ);
      METEOR::doMultiMETEOR($config, $HYP, $HYP_file, $REF, \%HREF, $hOQ);
      ROUGE::doMultiROUGE($config, $HYP, $HYP_file, $REF, \%HREF, 1, "", $hOQ); # + stemming
      SP::doMultiSP($config, $HYP, $HYP_file, $REF, \%HREF, $hOQ);
      DP::doMultiDP($config, $HYP, $HYP_file, $REF, \%HREF, $hOQ);
      DPmalt::doMultiDP($config, $HYP, $HYP_file, $REF, \%HREF, $hOQ);
      NE::doMultiNE($config, $HYP, $HYP_file, $REF, \%HREF, $hOQ);
      CP::doMultiCP($config, $HYP, $HYP_file, $REF, \%HREF, $hOQ);
      SR::doMultiSR($config, $HYP, $HYP_file, $REF, \%HREF, $hOQ);
      DR::doMultiDR($config, $HYP, $HYP_file, $REF, \%HREF, 0, $hOQ);
      DR::doMultiDR($config, $HYP, $HYP_file, $REF, \%HREF, 1, $hOQ);
   }

	/*void Core::process_multi_metrics(string HYP, const set<string> &Lref, Scores &hOQ) {
		// read reports and build hOQ Scores structure
		// List of Metrics
	    string REF = Common::join_set(Lref, '_');

	    //compute_metrics_combination(REF, systems, metrics)
		SC_ASIYA sc_asiya;

		SingleMetric *pBLEU = new BLEU;
		SingleMetric *pNIST = new NIST;
		//SingleMetric *pBLEUNIST = new BLEUNIST;
		SingleMetric *pMETEOR = new METEOR;
		SingleMetric *pROUGE = new ROUGE;
		SingleMetric *pGTM = new GTM;
		SingleMetric *pTER = new TER;

		pBLEU->processMetric();

	    for (set<string>::const_iterator it_m= Config::metrics.begin(); it_m != Config::metrics.end(); ++it_m) {
	    	string metric = *it_m;
			for (set<string>::const_iterator it_s = Config::systems.begin(); it_s != Config::systems.end(); ++it_s) {
		    	string sys = *it_s;

		    	sc_asiya.read_report(sys, REF, metric, hOQ);
		    }
	    }
	}*/


void Core::doMultiMetrics(string HYP, const set<string> &Lref, Scores &hOQ) {
   // description _ launches automatic MT evaluation metrics (for multiple references)
   //                              * computes GTM (by calling Proteus java gtm) -> e = 1..3
   //                              * computes BLEU score (by calling NIST mteval script) -> n = 4
   //                              * computes NIST score (by calling NIST mteval script) -> n = 5
   //                              * computes METEOR
   //                              * computes ROUGE
   //                              * computes WER
   //                              * computes PER
   //                              * computes TER
   //                              * computes SP-based (Shallow Parsing)
   //                              * computes DP-based (Dependency Parsing)
   //                              * computes NE-based (Named Entity Recognition & Classification)
   //                              * computes CP-based (Full Parsing)
   //                              * computes SR-based (Semantic Role Labeling)
   //                              * computes DR-based (Discourse Representation - Semantics)
   // param2  _ candidate hypothesis (KEY)
   // param3  _ candidate filename (string)
   // param4  _ reference list (KEY LIST)		(Config::references)
   // param5  _ reference filenames (hash ref)		(Config::Hrefs)
   // param2  _ hash of scores

/*
	doMultiMetrics($config, $sys, $config->{Hsystems}->{$sys}, $config->{references}, $config->{Hrefs}, $hOQ);

   my $HYP = shift;
   my $HYP_file = shift;
   my $Lref = shift;	Config::references
   my $Href = shift;	Config::Hrefs
   my $hOQ = shift;
*/


   //Lref is already sorted (set's wonders)

	string HYP_file = TESTBED::Hsystems[HYP];

	/*set<string>::const_iterator it = Lref.begin();
	string REF = *it;	++it;
	while (it != Lref.end()) {
		REF += "_"; REF += *it;
		++it;
	}*/
    string REF = Common::join_set(Lref, '_');

	//if (Config::verbose > 1)
	if (Config::verbose) fprintf(stderr, "computing similarities [%s - %s]...\n", HYP.c_str(), REF.c_str());
	//else if (Config::verbose == 1) fprintf(stderr, "%s - %s [", HYP.c_str(), REF.c_str());

	SingleMetric *pBLEU = new BLEU;
	SingleMetric *pNIST = new NIST;
	//SingleMetric *pBLEUNIST = new BLEUNIST;
	SingleMetric *pMETEOR = new METEOR;
	SingleMetric *pROUGE = new ROUGE;
	SingleMetric *pGTM = new GTM;
	SingleMetric *pTER = new TER;

	pBLEU->doMetric(HYP, REF, "", hOQ);
	pNIST->doMetric(HYP, REF, "", hOQ);
	//pBLEUNIST->doMetric(HYP, REF, "", hOQ);
	pMETEOR->doMetric(HYP, REF, "", hOQ);
	pROUGE->doMetric(HYP, REF, "", 1, hOQ);
	pGTM->doMetric(HYP, REF, "", hOQ);
	pTER->doMetric(HYP, REF, "", hOQ);

	delete pBLEU, pNIST, pMETEOR, pROUGE, pGTM, pTER;
/*
	BLEU bleu;
	NIST nist;
	BLEUNIST bleunist;

	cout << "hola bleu" << endl;
	bleu.doMetric(HYP, REF, "", hOQ);
	cout << "hola nist" << endl;
	nist.doMetric(HYP, REF, "", hOQ);
	cout << "hola bleunist" << endl;
	bleunist.doMetric(HYP, REF, "", hOQ);*/

	if (Config::verbose == 1) fprintf(stderr, "]\n");

	cout << "[SCORES] : hOQ" << endl;
	hOQ.print_sys_scores();
	hOQ.print_doc_scores(2);

//	hOQ.save_struct_scores("serialized_hOQ");
	const char filename[] = "serialized_hOQ";
    ofstream ofs(filename);
    boost::archive::text_oarchive oa(ofs);
    oa << hOQ;

    Scores new_hOQ;

    ifstream ifs(filename);
    boost::archive::text_iarchive ia(ifs);
    ia >> new_hOQ;

	cout << "[SCORES] : new_hOQ" << endl;
	new_hOQ.print_sys_scores();
	new_hOQ.print_doc_scores(2);

	cout << "[SCORES] serialized done. FILE < " << filename << endl;
	exit(1);
}

void Core::find_max_scores(const Scores &hOQ) {
    // description _ finds maximum score for each metric (), considering system translations by default.
    //               If "do_refs" reference ranslations are considered as well.
    // param1  _ configuration
    // param2  _ hash of scores

}

double Core::do_scores(Scores &hOQ) {
   //description _ launches metric computation for all given systems
    //param2  _ hash of scores
    //@return _ overall benchmark time (in secs)

	//map<string, double> hOQ;
	//Scores hOQ;

    Config::parser = "";
    Config::SRCparser = "";

    // --- create the tsearch if requested
    if (Config::tsearch == 1) {
    	//$tsearch = new TSDatabase($config->{testbedid}, $config->{IQ_config}, $Common::DATA_PATH, $config->{tools} );
    }

    double TIME = 0;

    // --- end creation of tsearch
    //cout << "do_scores -> eval_schemes <- " << endl;
    //Config::printMapInt(Config::eval_schemes);

	if (Config::eval_schemes.find(Common::S_SINGLE) != Config::eval_schemes.end() or \
		Config::metaeval_schemes.find(Common::S_SINGLE) != Config::metaeval_schemes.end() or \
		Config::optimize_schemes.find(Common::S_SINGLE) != Config::optimize_schemes.end() or \
		Config::eval_schemes.find(Common::S_ULC) != Config::eval_schemes.end() or \
		Config::metaeval_schemes.find(Common::S_ULC) != Config::metaeval_schemes.end() or \
		Config::optimize_schemes.find(Common::S_ULC) != Config::optimize_schemes.end()) {

		if (Config::verbose) fprintf(stderr, "[METRICS] computing 'system vs. reference' scores (one vs. all)...\n");

		for (set<string>::const_iterator it = Config::systems.begin(); it != Config::systems.end(); ++it) {	//systems Vs. references
			double time1 = omp_get_wtime();
//doMultiMetrics($config, $sys, $config->{Hsystems}->{$sys}, $config->{references}, $config->{Hrefs}, $hOQ);
			doMultiMetrics(*it, Config::references, hOQ);
			//process_multi_metrics(*it, Config::references, hOQ);						//read report files

			if (Config::eval_schemes.find(Common::S_QUEEN) != Config::eval_schemes.end() or \
				Config::metaeval_schemes.find(Common::S_QUEEN) != Config::metaeval_schemes.end() or \
				Config::optimize_schemes.find(Common::S_QUEEN) != Config::optimize_schemes.end()) {

				for (set<string>::const_iterator itr = Config::references.begin(); itr != Config::references.end(); ++itr) {	//systems Vs. references
					doMultiMetrics(*it, set<string>(itr, itr), hOQ);
				}
			}

	  		// --- tsearch insertion
			if (Config::tsearch == 1) {

			}
			// --- end tsearch insertion

			double time2 = omp_get_wtime();
			double t = time2 - time1;	//= Common::get_raw_Benchmark;
			TIME += t;
			fprintf(stderr, "time1: %f\n", time1);
			fprintf(stderr, "time2: %f\n", time2);
			fprintf(stderr, "time: %f\n", t);
			if (Config::do_time) fprintf(stderr, "t(%s) = %f\n", it->c_str(), t);
		}
	}

	if (Config::eval_schemes.find(Common::S_QUEEN) != Config::eval_schemes.end() or \
		Config::metaeval_schemes.find(Common::S_QUEEN) != Config::metaeval_schemes.end() or \
		Config::optimize_schemes.find(Common::S_QUEEN) != Config::optimize_schemes.end()) {

		if (Config::verbose) fprintf(stderr, "[METRICS] computing 'reference vs. reference' scores (pairwise)...\n");

		for (set<string>::const_iterator it = Config::references.begin(); it != Config::references.end(); ++it) {	//references Vs. references
			double time1 = omp_get_wtime();
			for (set<string>::const_iterator itr = Config::references.begin(); itr != Config::references.end(); ++itr) {	//references Vs. references
				if (*it != *itr)
					doMultiMetrics(*it, set<string> (itr, itr), hOQ);
			}
			double time2 = omp_get_wtime();
			double t = time2 - time1;	//Common::get_raw_Benchmark;
			TIME += t;
			if (Config::do_time) fprintf(stderr, "t(%s) = %f\n", it->c_str(), t);
		}
	}

	if ( (Config::references.size() > 1 and Config::do_refs) or \
		Config::metaeval_criteria.find(Common::C_KING) != Config::metaeval_criteria.end() or \
		Config::optimize_criteria.find(Common::C_KING) != Config::optimize_criteria.end() or \
		Config::metaeval_criteria.find(Common::C_ORANGE) != Config::metaeval_criteria.end() or \
		Config::optimize_criteria.find(Common::C_ORANGE) != Config::optimize_criteria.end()) {

		if (Config::verbose) fprintf(stderr, "[METRICS] computing 'reference vs. reference' scores (one vs. all)...\n");

		for (set<string>::const_iterator it = Config::references.begin(); it != Config::references.end(); ++it) {	//references Vs. all other references
			double time1 = omp_get_wtime();
			set<string> all_other_refs;
			for (set<string>::const_iterator itr = Config::references.begin(); itr != Config::references.end(); ++itr) {
				if (*it != *itr) all_other_refs.insert(*itr);
			}
			if (all_other_refs.size() > 1) {
				doMultiMetrics(*it, all_other_refs, hOQ);

				if (Config::metaeval_criteria.find(Common::C_KING) != Config::metaeval_criteria.end() or \
					Config::optimize_criteria.find(Common::C_KING) != Config::optimize_criteria.end() or \
					Config::metaeval_criteria.find(Common::C_ORANGE) != Config::metaeval_criteria.end() or \
					Config::optimize_criteria.find(Common::C_ORANGE) != Config::optimize_criteria.end()) {

					for (set<string>::const_iterator it = Config::systems.begin(); it != Config::systems.end(); ++it) {	//systems Vs. all other references
						doMultiMetrics(*it, all_other_refs, hOQ);
					}
				}
			}
			else Config::do_refs = 0;

			double time2 = omp_get_wtime();
			double t = time2 - time1;	//Common::get_raw_Benchmark;
			TIME += t;
			if (Config::do_time) fprintf(stderr, "t(%s) = %f\n", it->c_str(), t);
		}
	}

	// --- finalize the tsearch
	if (Config::tsearch == 1) {}
	// --- end finalize tsearch

	if (Config::do_time) fprintf(stderr, "TOTAL TIME = %f\n", TIME);

	// required for normalized ULC computation (it can be very slow!)
	if (Config::eval_schemes.find(Common::S_ULC) != Config::eval_schemes.end() or \
		Config::metaeval_schemes.find(Common::S_ULC) != Config::metaeval_schemes.end() or \
		Config::optimize_schemes.find(Common::S_ULC) != Config::optimize_schemes.end()) {

		if (Config::verbose) fprintf(stderr, "[METRICS] finding max metric scores (for normalization)...\n");
		find_max_scores(hOQ);
	}

	return TIME;
}

void Core::do_print(Scores &hOQ) {
	// description _ Print metric scores in the given format
	if (Config::eval_schemes[Common::S_SINGLE] or Config::eval_schemes[Common::S_ULC] or Config::eval_schemes[Common::S_QUEEN]) {
		//if (Config::O_DEFAULT)

	}
	string format = Common::O_DEFAULT;
	//cout << "O_DEFAULT: " << format << endl;
	//cout << "config->{O}: " << Config::O << endl;

	if (Config::O != Common::O_DEFAULT) format == Config::O;
	vector<string> sorted_metrics = get_sorted_metrics();

	SC_RAW sc_raw;
	sc_raw.print_scores_MMATRIX(hOQ, sorted_metrics);

	/*if (Config::O != Common::O_NONE) {
		if (Config::verbose) fprintf(stderr, "Printing evaluation report...\n");
		if (format == Common::O_NIST) sc_raw.print_scores_NIST(hOQ);
		else if (format == Common::O_MMATRIX) sc_raw.print_scores_MMATRIX(hOQ);
		else if (format == Common::O_SMATRIX) sc_raw.print_scores_SMATRIX(hOQ);
		else { fprintf(stderr, "[ERROR] unknown output format <%s>\n", format.c_str()); exit(1); }
	}*/
}