#ifndef SINGLEMETRIC_HPP
#define SINGLEMETRIC_HPP

#include "Scores.hpp"

#include <string>

class SingleMetric {
private:

public:
	SingleMetric() {}
	//SingleMetric() { std::cout << "Constructor de SingleMetric" << endl; }
	virtual void doMetric(string TGT, string REF, string prefix, Scores &hOQ) {}

};

#endif