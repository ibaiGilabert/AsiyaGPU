#ifndef NE_HPP
#define NE_HPP

#include "SingleMetric.hpp"

#include <vector>
#include <map>
#include <set>

typedef vector<string> wParsed;
typedef vector<wParsed> sParsed;
typedef map<string, map< string, map<string, int> > > SNTfeatures;


class NE : public SingleMetric {
private:
	static map<string, string> create_rLANG();
	static set<string> create_rNEeng();
	static set<string> create_rNEengSmall();

	static const string NEEXT, BIOS;
	static const set<string> rNEeng, rNEengSmall, rNEespcat;
	static const map<string, string> rLANG;

	void SNT_extract_features(const sParsed &snt, SNTfeatures &sntEXT);
	void SNT_compute_overlap_scores(SNTfeatures &Tout, SNTfeatures &Tref, map<string, double> &SCORES);
	void FILE_compute_overlap_metrics(const vector<sParsed> &FDout, const vector<sParsed> &FDref, vector< map<string, double> > &SCORES);

public:
	void doMetric(string TGT, string REF, string prefix, Scores &hOQ);

};



#endif