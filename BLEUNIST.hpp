#ifndef BLEUNIST_HPP
#define BLEUNIST_HPP

#include "Scores.hpp"
#include "SingleMetric.hpp"

#include <vector>

class BLEUNIST : public SingleMetric {
private:
	struct ReadScores {
		double sys_score;
		vector<double> doc_scores, seg_scores;
	};

	static map<string, int> create_rBLEUNIST();
	static map<string, int> create_rBLEU();
	static map<string, int> create_rNIST();

	ReadScores read_scores(string basename, string TGT);
	vector<double> read_scores_G(string basename, string G, string TGT);

	pair<ReadScores, ReadScores> computeBLEUNIST(string TGT);

public:
	void doMetric(string TGT, string REF, string prefix, Scores &hOQ);

	static const string BLEUEXT, NISTEXT, TBLEUNIST;
	static const map<string, int> rBLEUNIST, rBLEU, rNIST;
};


#endif