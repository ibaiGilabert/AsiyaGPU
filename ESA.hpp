#ifndef ESA_HPP
#define ESA_HPP

#include "SingleMetric.hpp"

#include <vector>
#include <map>

class ESA : public SingleMetric {
private:
	static map<string, int> create_rESA();
	static map<string, map<string, int> > ESA::create_rLANG();
	static map<string, string> create_TESA();
	static map<string, string> create_TESA_java();
	static map<string, string> create_TESA_mem();
	static map<string, string> create_TESAindex();

	vector<double> read_ESA(string reportESA);
	vector<vector<double> > read_ESA_segments(string reportESA);

	pair<vector<double>, vector<vector<double> > > computeESA(string TGT, int stemming);

public:
	ESA() {}
	~ESA() {}

	void doMetric(string TGT, string REF, string prefix, int stemming, Scores &hOQ);

	static const string ESAXT, TESAdir, EMPTY_ITEM;
	static const map<string, int> rESA, rLANG;
	static const map<string, string> TESA, TESA_java, TESA_mem, TESAindex;
};



#endif