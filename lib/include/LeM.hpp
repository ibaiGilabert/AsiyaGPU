#ifndef LeM_HPP
#define LeM_HPP

#include "SingleMetric.hpp"

#include <vector>
#include <set>

class LeM : public SingleMetric {
private:
	static set<string> create_rLeM();

	static const string LeMEXT, TLeM;
	static const set<string> rLeM;

	void LeM_f_create_doc(string input, string output, string G, const vector<vector<string> > &idx);
	void read_LeM(string report, double &SYS, vector<double> &DOC, vector<double> &SEG);

	void computeLeM(string TGT, string langpair, double &SYS, vector<double> &DOC, vector<double> &SEG);

public:
	void doMetric(string TGT, string REF, string prefix, Scores &hOQ);

};


#endif