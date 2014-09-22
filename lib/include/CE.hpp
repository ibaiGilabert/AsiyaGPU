#ifndef CE_HPP
#define CE_HPP

#include "SingleMetric.hpp"

#include <vector>
#include <map>

class CE : public SingleMetric {
private:
	static map<string, int> create_rCE();
	static map<string, int> create_srcENG();
	static map<string, int> create_trgENG();
	static map<string, int> create_notENGSPA();
	static map<string, string> create_rBIDICT();

	vector<double> read_CE(string reportCE);
	vector<vector<double> > read_CE_segments(string reportCE);

	pair<vector<double>, vector<vector<double> > > computeCE(string TGT, int stemming);

public:
	CE() {}
	~CE() {}

	void doMetric(string TGT, string REF, string prefix, int stemming, Scores &hOQ);

	static const string CEEXT;
	static const map<string, int> rCE, srcENG, trgENG, notENGSPA;
	static const map<string, string> rBIDICT;
	static const int BIDICT_MAX_NGRAM_LENGTH;
};



#endif