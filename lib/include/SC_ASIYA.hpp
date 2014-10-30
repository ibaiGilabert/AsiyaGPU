#ifndef SC_ASIYA_HPP
#define SC_ASIYA_HPP

#include "SC_FORMAT.hpp"

#include <string>
#include <vector>

using namespace std;

class SC_ASIYA : SC_FORMAT {
private:
	void save_xml(string report_xml, string TGT, string REF, string METRIC, const MetricScore &m);

public:
	void write_report(string TGT, string REF, string METRIC, const MetricScore &m);
	void write_report(string TGT, string REF, string METRIC, double sys_score, const vector<double> &doc_scores, const vector<double> &seg_scores);

};

#endif