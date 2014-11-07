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

	pair<vector<double>, vector<vector<double> > > computeNIST(string TGT);
	MetricScore computeNISTN(string TGT);

public:
	void doMetric(string TGT, string REF, string prefix, Scores &hOQ);

};


#endif