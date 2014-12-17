#ifndef ULC_HPP
#define ULC_HPP

#include "ComplexMetric.hpp"

#include <vector>

class ULC : public ComplexMetric {
private:

public:
	void doMetric(const set<string> &systems, const set<string> &references, const set<string> &metrics, Scores &hOQ);	// compute_normalize_ULC

	static const string ULC_NAME;

};



#endif