#ifndef CORE_HPP
#define CORE_HPP

#include <map>
#include <string>
using namespace std;

class Core {
private:
	//Compute scores
	void doMultiMetrics();

	//Printing
	void print_metric_names();

	void find_max_scores(map<string, double> &hOQ);
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