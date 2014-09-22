#ifndef SCORES_HPP
#define SCORES_HPP

#include <string>
#include <vector>
#include <map>
using namespace std;

typedef pair<string, double> Score;
typedef map<string, vector<Score> > iMap;
typedef map<string, iMap> oMap;

struct MetricScore {
	double sys_score;
	vector<double> doc_scores, seg_scores;
};

class Scores {
private:

public:
	oMap sys, seg, doc, all;

	//Read
	static MetricScore read_scores(string basename, string TGT, int do_neg);
	static vector<double> read_scores_G(string basename, string G, string TGT, int do_neg);

	//Save
	void save_hash_scores(string metric_name, string system_name, string refere_name, const MetricScore &scores);
	void save_hash_scores(string metric_name, string system_name, string refere_name, double sys_score, const vector<double> &doc_scores, const vector<double> &seg_scores);

	//Print
	void print_scores();
};

#endif