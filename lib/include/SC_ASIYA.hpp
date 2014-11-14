#ifndef SC_ASIYA_HPP
#define SC_ASIYA_HPP

#include "SC_FORMAT.hpp"

#include <string>
#include <vector>

#include <boost/serialization/string.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/serialization/map.hpp>

using namespace std;

class SC_ASIYA : SC_FORMAT {
private:
	void save_xml(string report_xml, string TGT, string REF, string METRIC, const MetricScore &m);

public:
	void read_report(string TGT, string REF, string METRIC, Scores &hOQ);

	void write_report(string TGT, string REF, string METRIC, const MetricScore &m);
	void write_report(string TGT, string REF, string METRIC, double sys_score, const vector<double> &doc_scores, const vector<double> &seg_scores);

	//Serialize hash scores
	void save_struct_scores(const Scores &hOQ, string filename);
	void load_struct_scores(Scores &hOQ, string filename);

};

#endif