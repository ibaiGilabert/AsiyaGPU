#ifndef TER_HPP
#define TER_HPP

#include "SingleMetric.hpp"
#include "Scores.hpp"

#include <vector>

class TER : public SingleMetric {
private:
	static map<string, int> create_rTER();

	MetricScore computeTER(string TGT, string variant, int do_neg);

public:
	TER() {}
	~TER() {}

	void doMetric(string TGT, string REF, string prefix, Scores &hOQ);

	static const string TEREXT,	TTERp;
	static const map<string, int> rTER;
};



#endif