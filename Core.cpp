#include "Core.hpp"
#include "Config.hpp"
#include "Scores.hpp"

#include <omp.h>
#include <stdio.h>
#include <iostream>

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

   if ($verbose == 1) { print STDERR "]\n"; }
void Core::doMultiMetrics(string HYP, map<string, double> &hOQ) {
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
   string HYP_file = Config::Hsystems[HYP];
   for (map<string, string>::const_iterator it = Config::Href.begin(); it != Config::Href.end(); ++it) {

   }
   if (Config::verbose > 1) fprintf(stderr, "computing similarities [$HYP]...\n");
   else if (Config::verbose == 1) fprintf(stderr, "$HYP - $REF [");

   BLEU.doMetric(HYP, REF, "", hOQ);
}

void Core::find_max_scores(map<string, double> &hOQ) {
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
	if (Config::eval_schemes.find(Common::S_SINGLE) != Config::eval_schemes.end() or \
		Config::metaeval_schemes.find(Common::S_SINGLE) != Config::metaeval_schemes.end() or \
		Config::optimize_schemes.find(Common::S_SINGLE) != Config::optimize_schemes.end() or \
		Config::eval_schemes.find(Common::S_ULC) != Config::eval_schemes.end() or \
		Config::metaeval_schemes.find(Common::S_ULC) != Config::metaeval_schemes.end() or \
		Config::optimize_schemes.find(Common::S_ULC) != Config::optimize_schemes.end()) {

		if (Config::verbose) fprintf(stderr, "[METRICS] computing 'system vs. reference' scores (one vs. all)...\n");

		for (set<string>::const_iterator it = Config::systems.begin(); it != Config::systems.end(); ++it) {	//systems Vs. references
			double time1 = omp_get_wtime();
			doMultiMetrics(*it, hOQ);
         	//doMultiMetrics($config, $sys, $config->{Hsystems}->{$sys}, $config->{references}, $config->{Hrefs}, $hOQ);

			if (Config::eval_schemes.find(Common::S_QUEEN) != Config::eval_schemes.end() or \
				Config::metaeval_schemes.find(Common::S_QUEEN) != Config::metaeval_schemes.end() or \
				Config::optimize_schemes.find(Common::S_QUEEN) != Config::optimize_schemes.end()) {

				for (set<string>::const_iterator itr = Config::references.begin(); itr != Config::references.end(); ++itr) {	//systems Vs. references
					doMultiMetrics(/**itr*/);
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
				if (*it != *itr) doMultiMetrics();
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
				doMultiMetrics();
				if (Config::metaeval_criteria.find(Common::C_KING) != Config::metaeval_criteria.end() or \
					Config::optimize_criteria.find(Common::C_KING) != Config::optimize_criteria.end() or \
					Config::metaeval_criteria.find(Common::C_ORANGE) != Config::metaeval_criteria.end() or \
					Config::optimize_criteria.find(Common::C_ORANGE) != Config::optimize_criteria.end()) {

					for (set<string>::const_iterator it = Config::systems.begin(); it != Config::systems.end(); ++it) {	//systems Vs. all other references
						doMultiMetrics();
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

pair<vector<double>, vector<double> > get_seg_doc_scores() {

}