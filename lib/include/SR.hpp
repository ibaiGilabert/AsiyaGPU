#ifndef SR_HPP
#define SR_HPP

#include "SingleMetric.hpp"

#include <vector>
#include <map>

typedef vector<string> wParsed;
typedef vector<wParsed> sParsed;
typedef map<string, map< string, map<string, int> > > SNTfeatures;
typedef map<string, vector<int> > rParsed;

class SR : public SingleMetric {
private:
	static set<string> create_rSReng();

	static set<string> rSReng;
	static const string SREXT, SWIRL;

	void parse_SR(string input, string L, string C, vector<sParsed> &FILE_S, vector< vector<rParsed> > &FILE_R, vector< vector<vector<string> > > &FILE_V);


public:
	void doMetric(string TGT, string REF, string prefix, Scores &hOQ);

};



#endif