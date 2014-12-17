#ifndef PER_HPP
#define PER_HPP

#include "SingleMetric.hpp"

#include <vector>
#include <set>

class PER : public SingleMetric {
private:
	static set<string> create_rPER();

	static const string PEREXT, TPER;
	static const set<string> rPER;

	void PER_f_create_doc(string input, string output);
	void read_PER(string report, int do_neg, double &PER, vector<double> &lPER);

	void computePER(string TGT, int do_neg, double &MAXSYS, vector<double> &MAXSEG);

public:
	void doMetric(string TGT, string REF, string prefix, Scores &hOQ);

};


#endif