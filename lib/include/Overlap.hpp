#ifndef Overlap_HPP
#define Overlap_HPP

#include "SingleMetric.hpp"

#include <vector>
#include <map>

class Overlap : public SingleMetric {
private:
	static set<string> create_rOl();

	static const string OlEXT, PlEXT, RlEXT , FlEXT;
	static const set<string> rOl;

	void extract_temrs(const map<string, int> &h_cand, const map<string, int> &h_ref, int LC, map<string, double> &t_cand, map<string, double> &t_ref, map<string, double> &t_tot);

	pair<double, double> compute_precision(const map<string, int> &hO, const map<string, int> &hR, int LC);
	pair<double, double> compute_recall(const map<string, int> &hO, const map<string, int> &hR, int LC);

	void computeOl(string out, string ref, double &SYS, vector<double> &SEG);
	void computePl(string out, string ref, double &SYS, vector<double> &SEG);
	void computeRl(string out, string ref, double &SYS, vector<double> &SEG);
	void computeFl(string out, string ref, double &SYS, vector<double> &SEG);

	void computeMultiOl(string out, double &MAXSYS, vector<double> &MAXSEG);
	void computeMultiPl(string out, double &MAXSYS, vector<double> &MAXSEG);
	void computeMultiRl(string out, double &MAXSYS, vector<double> &MAXSEG);
	void computeMultiFl(string out, double &MAXSYS, vector<double> &MAXSEG);

public:
	pair<double, double> compute_overlap(const map<string, int> &hO, const map<string, int> &hR, int LC);

	void doMetric(string TGT, string REF, string prefix, Scores &hOQ);

};


#endif