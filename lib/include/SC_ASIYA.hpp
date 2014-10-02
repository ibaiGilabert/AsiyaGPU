#ifndef SC_ASIYA_HPP
#define SC_ASIYA_HPP

#include "SC_FORMAT.hpp"

#include <string>
#include <vector>

using namespace std;

class SC_ASIYA : SC_FORMAT {
private:

public:
	void write_report(string TGT, string REF, string METRIC, const MetricScore &m);
	void write_report(string TGT, string REF, string METRIC, double sys_score, const vector<double> &doc_scores, const vector<double> &seg_scores);

	static const int FLOAT_LENGTH;
	static const int FLOAT_PRECISION;
	static const string ROOT_ELEMENT;
};

#endif