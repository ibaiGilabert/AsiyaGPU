#ifndef ESA_HPP
#define ESA_HPP

#include "SingleMetric.hpp"

#include <vector>
#include <map>

class ESA : public SingleMetric {
private:
	static set<string> create_rESA();
	static map<string, set<string> > create_rLANG();
	static map<string, string> create_TESA();
	static map<string, string> create_TESA_java();
	static map<string, string> create_TESA_mem();
	static map<string, string> create_TESAindex();

	static const string ESAEXT, TESAdir, EMPTY_ITEM;
	static set<string> rESA;
	static map<string, set<string> > rLANG;
	static map<string, string> TESA, TESA_java, TESA_mem, TESAindex;

	void ESA_f_create_doc(string input, string output);

	vector<double> read_ESA_segments(string reportESA);

	void computeESA(string metric, string out, string ref, vector<double> &SEG);
	void computeMultiESA(string metric, string out, double &MAXSYS, vector<double> &MAXSEG);

public:
	void doMetric(string TGT, string REF, string prefix, Scores &hOQ);

};



#endif