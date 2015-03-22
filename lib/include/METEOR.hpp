#ifndef METEOR_HPP
#define METEOR_HPP

#include "SingleMetric.hpp"

#include <vector>
#include <set>

class METEOR : public SingleMetric {
private:
	static set<string> create_rMETEOR();
	static set<string> create_rLANG_STM();
	static set<string> create_rLANG_PARA();
	static set<string> create_rLANG_SYN();
	static map<string, string> create_rLANG();

	static map<string, string> rLANG;
	static const string MTREXT, TMETEOR, METEORSCRIPT;
	static const set<string> rMETEOR, rLANG_STM, rLANG_PARA, rLANG_SYN;

	void computeMETEOR(string TGT, string variant, MetricScore &res);

public:
	void doMetric(string TGT, string REF, string prefix, Scores &hOQ);

};



#endif