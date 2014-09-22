#ifndef BLEUNIST_HPP
#define BLEUNIST_HPP

#include "SingleMetric.hpp"
//#include "Scores.hpp"

#include <vector>

class BLEUNIST : public SingleMetric {
private:
	static map<string, int> create_rBLEUNIST();
	static map<string, int> create_rBLEU();
	static map<string, int> create_rNIST();

	//Score read_scores(string basename, string TGT);
	//vector<double> read_scores_G(string basename, string G, string TGT);

	pair<MetricScore, MetricScore> computeBLEUNIST(string TGT);

public:
	BLEUNIST() {}
	~BLEUNIST() {}

	void doMetric(string TGT, string REF, string prefix, Scores &hOQ);

	static const string BLEUEXT, NISTEXT, TBLEUNIST;
	static const map<string, int> rBLEUNIST, rBLEU, rNIST;
};


#endif