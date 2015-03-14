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
	map<string, string> job_qw;      								// <job_id, <sys_name, init_time> >
	map<string, map<string, string> > fm_qw;      					// <sys_name, <metric_family, error_file> >

	//Compute scores
	void doMultiMetrics(string HYP, string REF, Scores &hOQ);

	//Compute scores multi-threading
	void process_multi_metrics(string HYP, string REF);
	void rebuild_hash_scores(string TGT, string REF, Scores &hOQ);

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
