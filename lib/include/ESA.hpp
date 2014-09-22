#ifndef ESA_HPP
#define ESA_HPP

#include "SingleMetric.hpp"

#include <vector>
#include <map>

class ESA : public SingleMetric {
private:
	static map<string, int> create_rESA();
	static map<string, map<string, int> > create_rLANG();
	static map<string, string> create_TESA();
	static map<string, string> create_TESA_java();
	static map<string, string> create_TESA_mem();
	static map<string, string> create_TESAindex();

	void ESA_f_create_doc(string input, string output);

	vector<double> read_esa_segments(string reportESA);
	vector<double> computeESA(string metric, string out, string ref);

	pair<double, vector<double> > computeMultiESA(string metric, string out);

public:
	ESA() {}
	~ESA() {}

	void doMetric(string TGT, string REF, string prefix, Scores &hOQ);

	static const string ESAXT, TESAdir, EMPTY_ITEM;
	static const map<string, int> rESA, rLANG;
	static const map<string, string> TESA, TESA_java, TESA_mem, TESAindex;
};



#endif