#ifndef SCORES_HPP
#define SCORES_HPP

#include <string>
#include <vector>
#include <map>

#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>

/*#include <boost/serialization/string.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/serialization/map.hpp>*/

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
	oMap sys, all;
	vector<oMap> seg, doc;
    map<string, double> max_sys_score,	max_doc_score, max_seg_score;	//<granularity, [metric, value]>
	map<string, double> min_sys_score,	min_doc_score, min_seg_score;

    /*friend class boost::serialization::access;
	template<typename Archive>
	void serialize(Archive& ar, const unsigned version) {
		ar & sys & all & seg & doc;  // Simply serialize the data members of Obj
	}*/

public:

	//Constructor/Destructor
	//Scores(int n_doc, int n_seg);
	Scores();
	~Scores();

	//Read
	static MetricScore read_scores(string basename, string TGT, string sep, int do_neg);
	static vector<double> read_scores_G(string basename, string G, string TGT, string sep, int do_neg);

	bool exists_sys_score(string METRIC, string TGT, string REF);
	bool exists_doc_score(string METRIC, string TGT, string REF);
	bool exists_seg_score(string METRIC, string TGT, string REF);
    bool exists_all_score(string METRIC, string TGT, string REF);

	//Get
	oMap get_sys_scores() const;
	oMap get_doc_scores(int doc_id) const;
	oMap get_seg_scores(int seg_id) const;

	double get_sys_score(string METRIC, string TGT, string REF);
	double get_doc_score(string METRIC, string TGT, string REF, int doc_id);
	double get_seg_score(string METRIC, string TGT, string REF, int seg_id);

	int get_num_doc_scores() const;
	int get_num_seg_scores() const;

	double get_min_sys_score(string metric);
	double get_min_doc_score(string metric);
	double get_min_seg_score(string metric);
	double get_max_sys_score(string metric);
	double get_max_doc_score(string metric);
	double get_max_seg_score(string metric);

    //Set
	void set_sys_score(string METRIC, string TGT, string REF, double score);
	void set_doc_score(int n, string METRIC, string TGT, string REF, double x);
	void set_seg_score(int n, string METRIC, string TGT, string REF, double x);

	void set_min_sys_score(string metric, double value);
	void set_min_doc_score(string metric, double value);
	void set_min_seg_score(string metric, double value);
	void set_max_sys_score(string metric, double value);
	void set_max_doc_score(string metric, double value);
	void set_max_seg_score(string metric, double value);

	void add_metrics(string TGT, string REF, set<string> &M, string G, vector< map<string, double> > &scores);		// SR

	//Save
	void save_hash_scores(string metric_name, string system_name, string refere_name, const MetricScore &scores);
	void save_hash_scores(string metric_name, string system_name, string refere_name, double sys_score, const vector<double> &doc_scores, const vector<double> &seg_scores);

	//Serialize hash scores
	void save_struct_scores(char* filename);
	void load_struct_scores(char* filename);
	void make_doc_scores();
	void make_sys_scores();

	//Print
	void print_sys_scores() const;
	void print_doc_scores(int n) const;
	void print_seg_scores(int n) const;

	void print_min_scores() const;
	void print_max_scores() const;

	void print_MetricScore(const MetricScore &res) const;
};

#endif
