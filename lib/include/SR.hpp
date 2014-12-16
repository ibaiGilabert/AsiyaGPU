#ifndef SR_HPP
#define SR_HPP

#include "SingleMetric.hpp"

#include <vector>
#include <map>

class SR : public SingleMetric {
private:
	static set<string> create_rSReng();
	static set<string> create_rSRspacat();

	static set<string> rSReng, rSRspacat;
	static const string SREXT, SWIRL, XLike;

public:
	void doMetric(string TGT, string REF, string prefix, Scores &hOQ);

};



#endif