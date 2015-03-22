#ifndef GTM_HPP
#define GTM_HPP

#include "SingleMetric.hpp"

#include <vector>
#include <set>

class GTM : public SingleMetric {
private:
	static set<string> create_rGTM();
	
	static const string GTMEXT, TGTM;
	static const set<string> rGTM;

	double read_GTM(string reportGTM);
	vector<double> read_GTM_segments(string reportGTM);

	void computeGTM(string TGT, int e, double &SYS, vector<double> &SEG);

public:
	void doMetric(string TGT, string REF, string prefix, Scores &hOQ);

};



#endif