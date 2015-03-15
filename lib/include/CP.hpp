#ifndef CP_HPP
#define CP_HPP

#include "SingleMetric.hpp"

#include <vector>
#include <map>

struct TreeNode {
	string n;
	TreeNode *child;
};

typedef vector<string> wParsed;
typedef vector<wParsed> sParsed;
typedef map<string, map< string, map<string, int> > > SNTfeatures;

class CP : public SingleMetric {
private:
	static set<string> create_rCPeng();
	static set<string> create_rCPspacat();
	static set<string> create_rCPfrench();
	static set<string> create_rCPgerman();

	static map<string, string> create_rLANG();

	static const set<string> rCPeng, rCPspacat, rCPfrench, rCPgerman;
	static map<string, string> rLANG;

	static const string SPATOOL, ENGTOOL, FRETOOL, GERTOOL, CPEXT, CSEP, EMPTY_ITEM;
	static const int SNTLEN_COLLINS, SNTLENG_CHARNIAK, MAXSTM_LENGTH;

public:
	CP();
	~CP();
};



#endif