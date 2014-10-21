#ifndef SINGLEMETRIC_HPP
#define SINGLEMETRIC_HPP

#include "Scores.hpp"
#include "../Common.hpp"
#include "../Config.hpp"
#include "TESTBED.hpp"
//#include "NISTXML.hpp"
//#include "IQXML.hpp"
#include "TB_NIST.hpp"
#include "SC_ASIYA.hpp"

#include <vector>
#include <string>

class SingleMetric {
protected:

public:
	//SingleMetric() {}
	//virtual ~SingleMetric() {}

	virtual void doMetric(string TGT, string REF, string prefix, Scores &hOQ) {}
	virtual void doMetric(string TGT, string REF, string prefix, int stemming, Scores &hOQ) {}	//DR i ROUGE

};

#endif