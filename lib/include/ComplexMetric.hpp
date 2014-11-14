#ifndef COMPLEXMETRIC_HPP
#define COMPLEXMETRIC_HPP

#include "Scores.hpp"
#include "TESTBED.hpp"
#include "../Common.hpp"
#include "../Config.hpp"
//#include "TB_NIST.hpp"
//#include "SC_ASIYA.hpp"

#include <vector>
#include <string>
#include <set>

using namespace std;

class ComplexMetric {
protected:

public:
	virtual void doMetric(Scores &hOQ, const set<string> &systems, const set<string> &references, const set<string> &metrics) {}

};

#endif