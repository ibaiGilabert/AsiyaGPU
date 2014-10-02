#ifndef TESTBED_HPP
#define TESTBED_HPP

#include <string>
#include <vector>
#include <map>

using namespace std;


class TESTBED {
protected:

public:
	static pair<vector<double>, vector<double> > get_seg_doc_scores(const vector<double> &scores, int DO_doc, string TGT);

	static string give_system_name(string file);
	static string replace_special_characters(string &input);

	static map<string, string> Hrefs, Hsystems;
	static map<string, vector<vector<string> > > IDX;
	static map<string, int> wc;
	static string src;
};

#endif