#ifndef METEOR_HPP
#define METEOR_HPP

#include "SingleMetric.hpp"

#include <vector>

class METEOR : public SingleMetric {
private:
	static map<string, int> create_rMETEOR();
	static map<string, int> create_rLANG_STM();
	static map<string, int> create_rLANG_PARA();
	static map<string, int> create_rLANG_SYN();
	static map<string, string> create_rLANG();

	static map<string, string> rLANG;
	static const string MTREXT, TMETEOR, METEORSCRIPT;
	static const map<string, int> rMETEOR, rLANG_STM, rLANG_PARA, rLANG_SYN;

	void computeMETEOR(string TGT, string variant, MetricScore &res);

public:
	void doMetric(string TGT, string REF, string prefix, Scores &hOQ);

};



#endif