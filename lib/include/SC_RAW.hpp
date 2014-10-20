#ifndef SC_RAW_HPP
#define SC_RAW_HPP

#include "SC_FORMAT.hpp"

#include <string>
#include <vector>

using namespace std;

class SC_RAW : SC_FORMAT {
private:
	void print_MMATRIX_header(const vector<string> &sorted_metrics);
	void print_system_scores_MMATRIX(string s);

public:
	void print_scores_NIST(const Scores &hOQ);
	void print_scores_MMATRIX(const Scores &hOQ, const vector<string> &sorted_metrics);
	void print_scores_SMATRIX(const Scores &hOQ);
};

#endif