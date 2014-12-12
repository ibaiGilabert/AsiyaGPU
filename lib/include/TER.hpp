#ifndef TER_HPP
#define TER_HPP

#include "SingleMetric.hpp"
#include "Scores.hpp"

#include <vector>

class TER : public SingleMetric {
private:
	static set<string> create_rTER();

	MetricScore computeTER(string TGT, string variant, int do_neg, MetricScore &res);

public:
	void doMetric(string TGT, string REF, string prefix, Scores &hOQ);

	static const string TEREXT,	TTERp;
	static const set<string> rTER;
};


#endif