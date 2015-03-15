#ifndef SRXLike_HPP
#define SRXLike_HPP

#include "SingleMetric.hpp"

#include <vector>
#include <set>

class SRXLike : public SingleMetric {
private:
	static set<string> create_rSRspacat();

public:
	static set<string> rSRspacat;
	static const string SREXT, XLike;

};



#endif