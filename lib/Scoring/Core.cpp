#include "../include/BLEU.hpp"
#include "../include/NIST.hpp"
//#include "../include/BLEUNIST.hpp"
#include "../include/METEOR.hpp"
#include "../include/ROUGE.hpp"
#include "../include/GTM.hpp"
#include "../include/TER.hpp"
#include "../include/SC_RAW.hpp"
#include "../include/TESTBED.hpp"
#include "../include/Core.hpp"
#include "../Config.hpp"

#include <omp.h>
#include <stdio.h>
#include <iostream>

/*#include <fstream>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
*/

/*vector<string> fBLEU() {
vector<string> v(8);
v[0] = "BLEU";    v[1] = "BLEU-1";  v[2] = "BLEU-2";  v[3] = "BLEU-3";
v[4] = "BLEU-4";  v[5] = "BLEUi-2"; v[6] = "BLEUi-3"; v[7] = "BLEUi-4";
return v;
}*/
//vector<string>(8) { "BLEU","BLEU-1","BLEU-2","BLEU-3","BLEU-4","BLEUi-2","BLEUi-3","BLEUi-4";

//string crew_BLEU[] = { "BLEU","BLEU-1","BLEU-2","BLEU-3","BLEU-4","BLEUi-2","BLEUi-3","BLEUi-4" };

Core::Core() {}

Core::~Core() {}

vector<string> Core::get_sorted_metrics() {
	vector<string> sorted_metrics;

	set<string> st = Config::metrics;
	if (Config::eval_schemes[Common::S_SINGLE]) {
		sorted_metrics = vector<string>(st.begin(), st.end());

		//sorted_metrics = vector<string>(Config::metrics.begin(), Config::metrics().end());
		//if (Config::SORT == Common::SORT_NAME) //already sorted (set)
	}
	if (Config::eval_schemes[Common::S_ULC]) sorted_metrics.push_back(ULC::ULC_NAME);
	if (Config::eval_schemes[Common::S_QUEEN]) sorted_metrics.push_back(QARLA::QUEEN);

	return sorted_metrics;
}

vector<string> Core::get_sorted_systems() {
	vector<string> sorted_systems;

	set<string> st = Config::systems;
	sorted_systems = vector<string>(Config::systems.begin(), Config::systems.end());

	return sorted_systems;
}


void Core::find_max_metric_scores(const Scores &hOQ, const set<string> &systems, const set<string> &references) {
	// description _ finds maximum score for each metric, so normalized scores for a given metric "i"
	//               can be later computed as are Xnorm(i) = X(i) / MAX(i)
	//               (max metric scores are stored onto the configuration object)
	string REF = Common::join_set(references, '_');
	for(set<string>::const_iterator it_m = Config::metrics.begin(); it_m != Config::metrics.end(); ++it_m) {
		string ref_tmp = REF;
		if (Config::min_score[Common::G_SYS][*it_m] == Config::min_score[Common::G_SYS][*it_m]) Config::min_score[Common::G_SYS][*it_m] = 0;
		if (Config::min_score[Common::G_DOC][*it_m] == Config::min_score[Common::G_DOC][*it_m]) Config::min_score[Common::G_DOC][*it_m] = 0;
		if (Config::min_score[Common::G_SEG][*it_m] == Config::min_score[Common::G_SEG][*it_m]) Config::min_score[Common::G_SEG][*it_m] = 0;

		if (Config::max_score[Common::G_SYS][*it_m] == Config::max_score[Common::G_SYS][*it_m]) Config::max_score[Common::G_SYS][*it_m] = 0;
		if (Config::max_score[Common::G_DOC][*it_m] == Config::max_score[Common::G_DOC][*it_m]) Config::max_score[Common::G_DOC][*it_m] = 0;
		if (Config::max_score[Common::G_SEG][*it_m] == Config::max_score[Common::G_SEG][*it_m]) Config::max_score[Common::G_SEG][*it_m] = 0;

		//SC_ASIYA sc_asiya;
		for(set<string>::const_iterator it_s = systems.begin(); it_s != systems.end(); ++it_s) {
			//sc_asiya.read_report(*it_s, REF, *it_m, hOQ);
			if (Config::G == Common::G_SYS or Config::G == Common::G_ALL) {
				if (hOQ.get_sys_scores()[*it_m][*it_s][ref_tmp] < Config::min_score[Common::G_SYS][*it_m])
					Config::min_score[Common::G_SYS][*it_m] = hOQ.get_sys_scores()[*it_m][*it_s][ref_tmp];
				if (hOQ.get_sys_scores()[*it_m][*it_s][ref_tmp] > Config::max_score[Common::G_SYS][*it_m])
					Config::max_score[Common::G_SYS][*it_m] = hOQ.get_sys_scores()[*it_m][*it_s][ref_tmp];
			}
			if (Config::G == Common::G_DOC or Config::G == Common::G_ALL) {
				for (int i = 0; i < hOQ.get_num_doc_scores(); ++i) {
					if (hOQ.get_doc_scores(i)[*it_m][*it_s][ref_tmp] < Config::min_score[Common::G_DOC][*it_m])
						Config::min_score[Common::G_DOC][*it_m] = hOQ.get_doc_scores(i)[*it_m][*it_s][ref_tmp];
					if (hOQ.get_doc_scores(i)[*it_m][*it_s][ref_tmp] > Config::max_score[Common::G_DOC][*it_m])
						Config::max_score[Common::G_DOC][*it_m] = hOQ.get_doc_scores(i)[*it_m][*it_s][ref_tmp];
				}
			}
			if (Config::G == Common::G_SEG or Config::G == Common::G_ALL) {
				for (int i = 0; i < hOQ.get_num_seg_scores(); ++i) {
					if (hOQ.get_seg_scores(i)[*it_m][*it_s][ref_tmp] < Config::min_score[Common::G_SEG][*it_m])
						Config::min_score[Common::G_SEG][*it_m] = hOQ.get_seg_scores(i)[*it_m][*it_s][ref_tmp];
				if (hOQ.get_seg_scores(i)[*it_m][*it_s][ref_tmp] > Config::max_score[Common::G_SEG][*it_m])
						Config::max_score[Common::G_SEG][*it_m] = hOQ.get_seg_scores(i)[*it_m][*it_s][ref_tmp];
				}
			}
		}
	}
}

void Core::find_max_scores(const Scores &hOQ) {
	// description _ finds maximum score for each metric (), considering system translations by default.
	//               If "do_refs" reference ranslations are considered as well.
	find_max_metric_scores(hOQ, Config::systems, Config::references);

	if (Config::do_refs) {
		for(set<string>::const_iterator it_r = Config::references.begin(); it_r != Config::references.end(); ++it_r) {
			set<string> all_other_refs;
			for(set<string>::const_iterator it_r2 = Config::references.begin(); it_r2 != Config::references.end(); ++it_r2)
				if (*it_r != *it_r2) all_other_refs.insert(*it_r);
			find_max_metric_scores(hOQ, set<string>(it_r, it_r), all_other_refs);
		}
	}
}


void Core::process_multi_metrics(string HYP, const set<string> &Lref) {
	// read reports and build hOQ Scores structure
	// List of Metrics
	string REF = Common::join_set(Lref, '_');

	//Process proc;
	string erase = "rm ";
	// LAUNCH
	for (int i = 1; i <= Config::num_process; ++i) {
		fprintf(stderr, "get_split (%s): sys: %s/ ext: %s/ thread: %d\n", HYP.c_str(), TESTBED::Hsystems[HYP].c_str(), Common::TXTEXT.c_str(), i );
		string TGT_split = TB_FORMAT::get_split(TESTBED::Hsystems[HYP], Common::TXTEXT, i);

		/*string config_bleu_file = proc.make_config_file(HYP, REF, "BLEU", i);
		string run_bleu_file = proc.make_run_file(config_bleu_file, HYP, REF, i, "BLEU");
		job_qw.insert(proc.run_job(run_bleu_file, "BLEU"));*/

		string config_rouge_file = proc.make_config_file(HYP, REF, "ROUGE", i);
		string run_rouge_file = proc.make_run_file(config_rouge_file, HYP, REF, i, "ROUGE");
		job_qw.insert(proc.run_job(run_rouge_file, "ROUGE"));

		/*string run_meteor_file = proc.make_run_file(config_file, HYP, REF, i, "METEOR");
		job_qw.insert(proc.run_job(run_meteor_file, "METEOR")); */

		// Crear cada config i script, despres llançar-lo iterativament per cada metrica.

<<<<<<< HEAD
		// ELIMINAR scripts
		//string erase_sh;
		//erase_sh = erase + run_bleu_file;			    system(erase_sh.c_str());
		//erase_sh = erase + run_rouge_file;        system(erase_sh.c_str());
		//erase_sh = erase + run_meteor_file;			  system(erase_sh.c_str());

		//erase_sh = erase + config_bleu_file;				  system(erase_sh.c_str());
		//erase_sh = erase + config_rouge_file;         system(erase_sh.c_str());
		}
=======
		// ELIMINAR scripts	(s'ha de fer no al encuar, sino despres de l'execucio)
		/*string erase_sh;
		//erase_sh = erase + run_bleu_file;			    system(erase_sh.c_str());
		erase_sh = erase + run_rouge_file;        system(erase_sh.c_str());
		//erase_sh = erase + run_meteor_file;			  system(erase_sh.c_str());

		//erase_sh = erase + config_bleu_file;				  system(erase_sh.c_str());
		erase_sh = erase + config_rouge_file;         system(erase_sh.c_str());*/
	}
>>>>>>> b5344f6962929c6ce147c46fa47d92c248c59497

	// WAIT IN DO_SCORES
}



void Core::rebuild_hash_scores(string TGT, const set<string> &Lref, Scores &hOQ) {
	string REF = Common::join_set(Lref, '_');

<<<<<<< HEAD
	for (int i = 1; i <= Config::num_process; ++i) {
		fprintf(stderr, "[LOAD]: ROUGE/ tgt: %s/ ref: %s/ split: %d\n", TGT.c_str(), REF.c_str(), i);
		hOQ.load_struct_scores(TB_FORMAT::get_serial("ROUGE", TGT, REF, i));
		fprintf(stderr, "[LOAD]: COMPLETE\n");
	}
=======
    for (int i = 1; i <= Config::num_process; ++i) {
        //fprintf(stderr, "[LOAD]: ROUGE/ tgt: %s/ ref: %s/ split: %d\n", TGT.c_str(), REF.c_str(), i);
    	hOQ.load_struct_scores(TB_FORMAT::get_serial("ROUGE", TGT, REF, i));
	    //fprintf(stderr, "[LOAD]: COMPLETE\n");
    }

>>>>>>> b5344f6962929c6ce147c46fa47d92c248c59497
}

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


	string HYP_file = TESTBED::Hsystems[HYP];
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

	if (Config::verbose == 1) fprintf(stderr, "]\n");

	/*	cout << "[SCORES] : hOQ" << endl;
	hOQ.print_sys_scores();
	hOQ.print_doc_scores(2);

	string filename = "serialized_hOQ";

	hOQ.save_struct_scores(filename.c_str());

	Scores new_hOQ;
	new_hOQ.load_struct_scores(filename.c_str());

	cout << "[SCORES] : new_hOQ" << endl;
	new_hOQ.print_sys_scores();
	new_hOQ.print_doc_scores(2);

	cout << "[SCORES] serialized done. FILE < " << filename << endl;

	string rm_filename = "rm " + filename;
	system(rm_filename.c_str());

	exit(1);*/
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
			if (Config::num_process)
				process_multi_metrics(*it, Config::references);						//read report files
			else
				doMultiMetrics(*it, Config::references, hOQ);

			/*if (Config::eval_schemes.find(Common::S_QUEEN) != Config::eval_schemes.end() or \
			Config::metaeval_schemes.find(Common::S_QUEEN) != Config::metaeval_schemes.end() or \
			Config::optimize_schemes.find(Common::S_QUEEN) != Config::optimize_schemes.end()) {

			for (set<string>::const_iterator itr = Config::references.begin(); itr != Config::references.end(); ++itr) {	//systems Vs. references
			doMultiMetrics(*it, set<string>(itr, itr), hOQ);
			}
			}*/

			double time2 = omp_get_wtime();
			double t = time2 - time1;	//= Common::get_raw_Benchmark;
			TIME += t;
			fprintf(stderr, "time1: %f\n", time1);
			fprintf(stderr, "time2: %f\n", time2);
			fprintf(stderr, "time: %f\n", t);
			if (Config::do_time) fprintf(stderr, "t(%s) = %f\n", it->c_str(), t);
		}
	}

<<<<<<< HEAD
if (Config::num_process) {
	// WAIT
	fprintf(stderr, "[WAIT]\n");
	while (!job_qw.empty()) {
		for (set<string>::const_iterator it_job = job_qw.begin(); it_job != job_qw.end(); ++it_job) {
			if (proc.end(*it_job)) job_qw.erase(it_job);
		}
	}

	// REBUILD
	fprintf(stderr, "[REBUILD]\n");
	for (set<string>::const_iterator it = Config::systems.begin(); it != Config::systems.end(); ++it) {
		rebuild_hash_scores(*it, Config::references, hOQ);
	}

	//cout << "[REBUILD] hOQ: " << endl;
	//for(int i = 0; i < hOQ.get_num_seg_scores(); ++i) {
	//	hOQ.print_seg_scores(i);
	//}
}
        /*for(int i = 0; i < hOQ.get_num_seg_scores(); ++i) {
                hOQ.print_seg_scores(i);
        }
	TESTBED::print_idx();*/
=======
	if (Config::num_process) {
		// WAIT
		if (Config::verbose) fprintf(stderr, "[WAIT]\n");
		while (!job_qw.empty()) {
	        for (set<string>::const_iterator it_job = job_qw.begin(); it_job != job_qw.end(); ++it_job) {
	                if (proc.end(*it_job)) job_qw.erase(it_job);
	        }
		}
		// REBUILD
		if (Config::verbose) fprintf(stderr, "[REBUILD]\n");
		for (set<string>::const_iterator it = Config::systems.begin(); it != Config::systems.end(); ++it) {
	        rebuild_hash_scores(*it, Config::references, hOQ);
		}
	}

>>>>>>> b5344f6962929c6ce147c46fa47d92c248c59497

	if (Config::eval_schemes.find(Common::S_QUEEN) != Config::eval_schemes.end() or \
	Config::metaeval_schemes.find(Common::S_QUEEN) != Config::metaeval_schemes.end() or \
	Config::optimize_schemes.find(Common::S_QUEEN) != Config::optimize_schemes.end()) {

		if (Config::verbose) fprintf(stderr, "[METRICS] computing 'reference vs. reference' scores (pairwise)...\n");

		for (set<string>::const_iterator it = Config::references.begin(); it != Config::references.end(); ++it) {	//references Vs. references
			double time1 = omp_get_wtime();
			for (set<string>::const_iterator itr = Config::references.begin(); itr != Config::references.end(); ++itr) {	//references Vs. references
				if (*it != *itr) doMultiMetrics(*it, set<string> (itr, itr), hOQ);
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
