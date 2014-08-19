#ifndef SINGLEMETRIC_HPP
#define SINGLEMETRIC_HPP

#include "Scores.hpp"

#include <iostream>
#include <string>

class SingleMetric {
private:

public:
	SingleMetric() {  cout << "######################## CONSTRUCTOR SingleMetric #########################" << endl; }
	virtual ~SingleMetric() { cout << "######################## DESTRUCTOR SingleMetric #########################" << endl; }

	//virtual ~SingleMetric() {}
	//SingleMetric() { std::cout << "Constructor de SingleMetric" << endl; }
	virtual void doMetric(string TGT, string REF, string prefix, Scores &hOQ) = 0;

};

#endif