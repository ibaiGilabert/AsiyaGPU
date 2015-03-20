#ifndef SRXLike_HPP
#define SRXLike_HPP

#include "SingleMetric.hpp"

#include <vector>
#include <set>

typedef vector<string> wParsed;
typedef vector<wParsed> sParsed;
typedef map<string, vector<int> > rParsed;


class SRXLike : public SingleMetric {
private:
	static set<string> create_rSRspacat();

	static const string SREXT, XLike;

	string getRoleName(string role_id, string L);
	pair<int, int> find_role_boundaries(map<int, vector<int> > &DPtree, int head);

	void extract_DP_subtress(map<int, vector<int> > &DPtree, vector<rParsed> &rolestruct);

	void FILE_create_input(string input, string auxconllfile);

public:
	void parse_SR(string input, string L, string C, vector<sParsed> &FILE_S, vector< vector<rParsed> > &FILE_R, vector< vector<vector<string> > > &FILE_V);

	static set<string> rSRspacat;	// SR

};



#endif