#ifndef NIST_HPP
#define NIST_HPP

#include "Scores.hpp"
#include "SingleMetric.hpp"

#include <vector>

class NIST : public SingleMetric {
private:
	static map<string, int> create_rNIST();

	vector<double> read_nist(string reportNIST);
	vector<vector<double> > read_nist_segments(string reportNIST);

	pair<vector<double>, vector<vector<double> > > computeNIST(string TGT);

public:
	void doMetric(string TGT, string REF, string prefix, Scores &hOQ);

	static const string NISTEXT,	NISTEXTi,	TNIST;
	static const map<string, int> rNIST;
};


#endif