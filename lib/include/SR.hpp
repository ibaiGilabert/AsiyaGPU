#ifndef SR_HPP
#define SR_HPP

#include "SingleMetric.hpp"

#include <vector>
#include <map>

typedef vector<string> wParsed;
typedef vector<wParsed> sParsed;
typedef map<string, vector<int> > rParsed;
typedef map<string, map<string, map<string, int> > > SNTfeaturesA;
typedef map<string, map<string, int> >	SNTfeaturesB;

struct SNTextract_feat {
	SNTfeaturesA A;
	SNTfeaturesB B;
	int nVerbs;
};

class SR : public SingleMetric {
private:
	static set<string> create_rSReng();

	static set<string> rSReng;
	static const string SREXT, SWIRL;

	void SNT_extract_features(const sParsed &snt_s, const vector<rParsed> &snt_r, const vector<vector<string> > &snt_v, SNTextract_feat &SNT);
	void SNT_compute_overlap_scores(SNTextract_feat &Tout, SNTextract_feat &Tref, int LC, map<string, double> &SCORES);

	void FILE_compute_overlap_metrics(const vector<sParsed> &POUT_S, const vector< vector<rParsed> > &POUT_R, const vector< vector<vector<string> > > &POUT_V, 
									  const vector<sParsed> &PREF_S, const vector< vector<rParsed> > &PREF_R, const vector< vector<vector<string> > > &PREF_V, 
									  vector< map<string, double> > &SCORES);

	void parse_SR(string input, string L, string C, vector<sParsed> &FILE_S, vector< vector<rParsed> > &FILE_R, vector< vector<vector<string> > > &FILE_V);


public:
	void doMetric(string TGT, string REF, string prefix, Scores &hOQ);

};



#endif