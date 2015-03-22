#ifndef NIST_HPP
#define NIST_HPP

#include "SingleMetric.hpp"

#include <vector>
#include <set>

class NIST : public SingleMetric {
private:
	static set<string> create_rNIST();

	static const string NISTEXT,	NISTEXTi,	TNIST;
	static const set<string> rNIST;

	void read_nist(string reportNIST, vector<double> &SYS);
	void read_nist_segments(string reportNIST, vector<vector<double> > &SEG);

	MetricScore computeNISTN(string TGT, string out, const map<string, string> &HREF);
	void computeNIST(string TGT, string out, const map<string, string> &HREF, vector<double> &SYS, vector<vector<double> > &SEG);

public:
	void doMetric(string TGT, string out, string REF, const map<string, string> &HREF, string prefix, Scores &hOQ);

};


#endif