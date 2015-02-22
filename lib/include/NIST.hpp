#ifndef NIST_HPP
#define NIST_HPP

#include "SingleMetric.hpp"

#include <vector>

class NIST : public SingleMetric {
private:
	static map<string, int> create_rNIST();

	static const string NISTEXT,	NISTEXTi,	TNIST;
	static const map<string, int> rNIST;

	vector<double> read_nist(string reportNIST);
	vector<vector<double> > read_nist_segments(string reportNIST);

	MetricScore computeNISTN(string TGT, string out, const map<string, string> &HREF);
	void computeNIST(string TGT, string out, const map<string, string> &HREF, vector<double> &SYS, vector<vector<double> > &SEG);

public:
	void doMetric(string TGT, string out, string REF, const map<string, string> &HREF, string prefix, Scores &hOQ);

};


#endif