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
	//Compute scores
	void doMultiMetrics(string HYP, const set<string> &Lref, Scores &hOQ);

	vector<string> get_sorted_metrics();

	//Printing
	void print_metric_names();

	void find_max_scores(const Scores &hOQ);
	void find_max_metric_scores();

public:
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