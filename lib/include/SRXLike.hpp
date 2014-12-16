#ifndef SRXLike_HPP
#define SRXLike_HPP

#include "SingleMetric.hpp"

#include <vector>
#include <map>

class SRXLike : public SingleMetric {
private:
	static set<string> create_rSRspacat();

	static set<string> rSRspacat;
	static const string SREXTT, XLike;

public:

};



#endif