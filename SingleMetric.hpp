#ifndef SINGLEMETRIC_HPP
#define SINGLEMETRIC_HPP

#include "Scores.hpp"

#include <vector>
#include <string>

class SingleMetric {
protected:

public:
	//SingleMetric() {}
	//virtual ~SingleMetric() {}

	static Score read_scores(string basename, string TGT);
	static vector<double> read_scores_G(string basename, string G, string TGT);

	virtual void doMetric(string TGT, string REF, string prefix, Scores &hOQ) {}
	virtual void doMetric(string TGT, string REF, string prefix, int stemming, Scores &hOQ) {}	//DR i ROUGE

};

#endif