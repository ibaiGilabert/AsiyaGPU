#ifndef CORE_HPP
#define CORE_HPP

#include "Scores.hpp"
#include "Process.hpp"

#include <map>
#include <set>
//#include <stack>
#include <vector>
#include <string>

using namespace std;

class Core {
private:
    Process proc;
	set<string> job_qw;      								// set de job_ids

	//Compute scores
	void doMultiMetrics(string HYP, const set<string> &Lref, Scores &hOQ);

	//Compute scores multi-threading
	void process_multi_metrics(string HYP, const set<string> &Lref);
	void rebuild_hash_scores(string TGT, const set<string> &Lref, Scores &hOQ);

	vector<string> get_sorted_metrics();
	vector<string> get_sorted_systems();

	void find_max_metric_scores(Scores &hOQ, const set<string> &systems, const set<string> &references);
	void find_max_scores(Scores &hOQ);
	void compute_metrics_combination(Scores &hOQ);

	//Printing
	void print_metric_names();

public:
	Core();
	~Core();

	//Compute scores
	double do_scores(Scores &hOQ);

	//Print Final Report
	void do_print(Scores &hOQ);

	//Printing
	void do_metric_names();
	void do_system_names();
	void do_reference_names();
};

#endif
