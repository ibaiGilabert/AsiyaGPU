#ifndef SC_NIST_HPP
#define SC_NIST_HPP

#include "SC_FORMAT.hpp"

#include <string>
#include <vector>
#include <map>

using namespace std;

class SC_NIST : SC_FORMAT {
private:
	static double negate_or_not(double n, int do_neg);
	static pair<string, double> get_score(const vector<string> &l, string G, int do_neg);

public:
	//read scores
	map<string, double> read_scores_file(string file, string G, int do_neg);

	//print scores
	//void print_scores();

};

#endif