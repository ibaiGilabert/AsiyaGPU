#ifndef SCORES_HPP
#define SCORES_HPP

#include <string>
#include <vector>
#include <map>
using namespace std;

/*typedef pair<string, double> Score;
typedef map<string, vector<Score> > iMap;*/


typedef map<string, double> sMap;
typedef map<string, sMap> iMap;
typedef map<string, iMap> oMap;

struct MetricScore {
	double sys_score;
	vector<double> doc_scores, seg_scores;
};

class Scores {
private:

public:
	oMap sys, all;
	vector<oMap> seg, doc;

	//Constructor/Destructor
	//Scores(int n_doc, int n_seg);
	Scores();
	~Scores();

	//Read
	static MetricScore read_scores(string basename, string TGT, int do_neg);
	static vector<double> read_scores_G(string basename, string G, string TGT, int do_neg);

	//Get
	oMap get_sys_scores() const;
	oMap get_doc_scores(int doc_id) const;
	oMap get_seg_scores(int seg_id) const;

	int get_doc_scores_size() const;
	int get_seg_scores_size() const;

	//Save
	void save_hash_scores(string metric_name, string system_name, string refere_name, const MetricScore &scores);
	void save_hash_scores(string metric_name, string system_name, string refere_name, double sys_score, const vector<double> &doc_scores, const vector<double> &seg_scores);

	//Print
	void print_scores();
	void print_sys_scores();
};

#endif