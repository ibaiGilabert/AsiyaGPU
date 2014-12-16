#ifndef WER_HPP
#define WER_HPP

#include "SingleMetric.hpp"

#include <vector>
#include <set>

class WER : public SingleMetric {
private:
	static set<string> create_rWER();

	static const string WEREXT, TWER;
	static const set<string> rWER;

	void WER_f_create_doc(string input, string output);
	void read_WER(string report, int do_neg, double &WER, vector<double> &lWER);

	void computeWER(string TGT, int do_neg, double &MAXSYS, vector<double> &MAXSEG);

public:
	void doMetric(string TGT, string REF, string prefix, Scores &hOQ);

};


#endif