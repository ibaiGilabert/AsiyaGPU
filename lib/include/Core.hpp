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

	//Printing
	void print_metric_names();

	void find_max_scores(const Scores &hOQ);
	void find_max_metric_scores();

public:
	//Compute scores
	double do_scores();

	//Printing
	void do_metric_names();
	void do_system_names();
	void do_reference_names();
};

#endif