#ifndef SC_FORMAT_HPP
#define SC_FORMAT_HPP

#include "Scores.hpp"

using namespace std;

class SC_FORMAT {
private:

public:
	//read scores
	virtual map<string, double> read_scores_file(string file, string G, int do_neg) {}

	//write scores
	virtual void write_report(string TGT, string REF, string METRIC, const MetricScore &m) {}
	virtual void write_report(string TGT, string REF, string METRIC, double sys_score, const vector<double> &doc_scores, const vector<double> &seg_scores) {}
};

#endif