#ifndef WER_HPP
#define WER_HPP

#include "SingleMetric.hpp"

#include <vector>
#include <map>

class WER : public SingleMetric {
private:
	static map<string, int> create_rWER();

	static const string WEREXT, TWER;
	static const map<string, int> rWER;

	void WER_f_create_doc(string input, string output);

	pair<double, vector<double> > read_WER(string report, int do_neg);

	pair<double, vector<double> > computeWER(string TGT, int do_neg);

public:
	WER() {}
	~WER() {}

	void doMetric(string TGT, string REF, string prefix, Scores &hOQ);

};



#endif