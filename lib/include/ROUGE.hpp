#ifndef ROUGE_HPP
#define ROUGE_HPP

#include "SingleMetric.hpp"

#include <vector>
#include <map>

class ROUGE : public SingleMetric {
private:
	static map<string, int> create_rROUGE();

	vector<double> read_rouge(string reportROUGE);
	vector<vector<double> > read_rouge_segments(string reportROUGE);

	void computeROUGE(string TGT, vector<double> &SYS, vector<vector<double> > &SEG, int stemming);

public:
	ROUGE() {}
	~ROUGE() {}

	void doMetric(string TGT, string REF, string prefix, int stemming, Scores &hOQ);

	static const string ROUGEXT, TROUGE, CFGEXT;
	static const map<string, int> rROUGE;
};



#endif