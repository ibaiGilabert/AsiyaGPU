#ifndef CORE_HPP
#define CORE_HPP

#include "Scores.hpp"

#include <map>
#include <set>
#include <vector>
#include <string>

using namespace std;

class Core {
private:
	//const set<string> whole_metric_set;

	//Compute scores
	void doMultiMetrics(string HYP, const set<string> &Lref, Scores &hOQ);

	//Compute scores multi-threading
	void process_multi_metrics(string HYP, const set<string> &Lref, Scores &hOQ);

	vector<string> get_sorted_metrics();
	vector<string> get_sorted_systems();

	void find_max_metric_scores(const Scores &hOQ, const set<string> &systems, const set<string> &references);
	void find_max_scores(const Scores &hOQ);

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