#ifndef ULC_HPP
#define ULC_HPP

#include "ComplexMetric.hpp"

#include <vector>

class ULC : public ComplexMetric {
private:
	static const string ULC_NAME;

public:
	void doMetric(Scores &hOQ, const set<string> &systems, const set<string> &references, const set<string> &metrics);	// compute_normalize_ULC

};



#endif