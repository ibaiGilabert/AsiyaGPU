#ifndef ROUGE_HPP
#define ROUGE_HPP

#include "SingleMetric.hpp"

#include <vector>
#include <set>

class ROUGE : public SingleMetric {
private:
	static set<string> create_rROUGE();

	static const set<string> rROUGE;
	static const string ROUGEXT, TROUGE, CFGEXT;

	void read_rouge(string reportROUGE, vector<double> &SYS);
	void read_rouge_segments(string reportROUGE, vector<vector<double> > &SEG);

	void computeROUGE(string TGT, int stemming, vector<double> &SYS, vector<vector<double> > &SEG);

public:
	ROUGE() {}
	~ROUGE() {}

	void doMetric(string TGT, string REF, string prefix, int stemming, Scores &hOQ);
};



#endif