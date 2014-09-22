#ifndef IQXML_HPP
#define IQXML_HPP

#include "Scores.hpp"

#include <string>
#include <vector>

using namespace std;

class IQXML {
private:

public:
	static void write_report(string TGT, string REF, string METRIC, const MetricScore &m);
	static void write_report(string TGT, string REF, string METRIC, double sys_score, const vector<double> &doc_scores, const vector<double> &seg_scores);

	static const int FLOAT_LENGTH;
	static const int FLOAT_PRECISION;
	static const string ROOT_ELEMENT;
};

#endif