#ifndef SCORES_HPP
#define SCORES_HPP

#include <string>
#include <vector>
#include <map>
using namespace std;

typedef pair<string, double> Score;
typedef map<string, vector<Score> > iMap;
typedef map<string, iMap> oMap;

class Scores {
private:

public:

	oMap sys, seg, doc, all;

	//Save
	void save_hash_scores(string metric_name, string system_name, string refere_name, double sys_score, const vector<double> &doc_scores, const vector<double> &seg_scores);

	//Print
	void print_scores();
};

#endif