#include "Core.hpp"
#include "Config.hpp"
#include "Scores.hpp"
#include "BLEU.hpp"
#include "NIST.hpp"
#include "BLEUNIST.hpp"

#include <omp.h>
#include <stdio.h>
#include <iostream>
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

   if ($verbose == 1) { print STDERR "]\n"; }*/

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

	string HYP_file = Config::Hsystems[HYP];

	set<string>::const_iterator it = Lref.begin();
	string REF = *it;	++it;
	while (it != Lref.end()) {
		REF += "_"; REF += *it;
		++it;
	}

	if (Config::verbose > 1) fprintf(stderr, "computing similarities [$HYP]...\n");
	else if (Config::verbose == 1) fprintf(stderr, "$HYP - $REF [");

	SingleMetric *pBLEU = new BLEU;
	SingleMetric *pNIST = new NIST;
	SingleMetric *pBLEUNIST = new BLEUNIST;

	pBLEU->doMetric(HYP, REF, "", hOQ);
	pNIST->doMetric(HYP, REF, "", hOQ);
	pBLEUNIST->doMetric(HYP, REF, "", hOQ);

	/*BLEU bleu;
	NIST nist;
	BLEUNIST bleunist;

	cout << "hola bleu" << endl;
	bleu.doMetric(HYP, REF, "", hOQ);
	cout << "hola nist" << endl;
	nist.doMetric(HYP, REF, "", hOQ);
	cout << "hola bleunist" << endl;
	bleunist.doMetric(HYP, REF, "", hOQ);*/
	delete pBLEU, pNIST, pBLEUNIST;

	if (Config::verbose == 1) fprintf(stderr, "]\n");
}

void Core::find_max_scores(const Scores &hOQ) {
    // description _ finds maximum score for each metric (), considering system translations by default.
    //               If "do_refs" reference ranslations are considered as well.
    // param1  _ configuration
    // param2  _ hash of scores

}

double Core::do_scores() {
   //description _ launches metric computation for all given systems
    //param2  _ hash of scores
    //@return _ overall benchmark time (in secs)

	//map<string, double> hOQ;
	Scores hOQ;

    Config::parser = "";
    Config::SRCparser = "";

    // --- create the tsearch if requested
    if (Config::tsearch == 1) {
    	//$tsearch = new TSDatabase($config->{testbedid}, $config->{IQ_config}, $Common::DATA_PATH, $config->{tools} );
    }

    double TIME = 0;

    // --- end creation of tsearch
    cout << "do_scores -> eval_schemes <- " << endl;
    Config::printMapInt(Config::eval_schemes);

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
			cout << "MultiMetric o ke ase?" << endl;
			doMultiMetrics(*it, Config::references, hOQ);

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
			cout << "time1: " << time1 << endl;
			cout << "time2: " << time2 << endl;
			cout << "time: " << t << endl;
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
				if (*it != *itr) doMultiMetrics(*it, set<string> (itr, itr), hOQ);
//doMultiMetrics($config, $ref1, $config->{Hrefs}->{$ref1}, [$ref2], $config->{Hrefs}, $hOQ); }
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
//doMultiMetrics($config, $ref1, $config->{Hrefs}->{$ref1}, \@all_other_refs, $config->{Hrefs}, $hOQ);

				if (Config::metaeval_criteria.find(Common::C_KING) != Config::metaeval_criteria.end() or \
					Config::optimize_criteria.find(Common::C_KING) != Config::optimize_criteria.end() or \
					Config::metaeval_criteria.find(Common::C_ORANGE) != Config::metaeval_criteria.end() or \
					Config::optimize_criteria.find(Common::C_ORANGE) != Config::optimize_criteria.end()) {

					for (set<string>::const_iterator it = Config::systems.begin(); it != Config::systems.end(); ++it) {	//systems Vs. all other references
						doMultiMetrics(*it, all_other_refs, hOQ);
//doMultiMetrics($config, $sys, $config->{Hsystems}->{$sys}, \@all_other_refs, $config->{Hrefs}, $hOQ);

					}
				}
			}
			else Config::do_refs = 0;

			// --- tsearch insertion
			if (Config::tsearch == 1) {}
			// -- end tsearch insertion

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

pair<vector<double>, vector<double> > Core::get_seg_doc_scores(const vector<double> &scores, int DO_doc, string TGT) {
    // description _ returns segment and document scores, given an index structure which
    //               contains information on the number of segments per document

	vector<vector<string> > idx = Config::IDX[TGT];
	vector<double> D_scores, S_scores;
	string docid = "";
	double sum = -1;
	int n, n_doc;
	n = n_doc = 0;

	int i = 1;
	while(i < idx.size()) {
		if (DO_doc) {	//doc-level scores
			if (idx[i][0] != docid)	{	//NEW DOCUMENT
				D_scores.push_back(scores[n_doc]);
				docid = idx[i][0];
				++n_doc;
			}
			S_scores.push_back(scores[n_doc-1]);
		}
		else {	//segment-level scores
			if (idx[i][0] != docid)	{	//NEW DOCUMENT
				if (sum != -1) D_scores.push_back(sum/n);
				docid = idx[i][0];
				sum = n = 0;
			}
			double x = 0;
			if (scores[i-1] != -1) x = scores[i-1];
			S_scores.push_back(x);
			sum += x;
			++n;
		}
		++i;
	}

	// last document (only if segment-level scores)
	if (!DO_doc) {
		if (sum != -1) D_scores.push_back(sum/n);
	}

	return make_pair(D_scores, S_scores);
}