#ifndef TESTBED_HPP
#define TESTBED_HPP

#include <string>
#include <vector>
#include <map>

using namespace std;


class TESTBED {
private:


public:
	static string give_system_name(string file);
	static string replace_special_characters(string &input);

	static void get_docid_list(string sys, vector<string> &ldoc_ids);

	static int get_setid_length(string sys);
	static int get_max_docid_length(string sys);
	static int get_max_segid_length(string sys);

	static pair<vector<double>, vector<double> > get_seg_doc_scores(const vector<double> &scores, int DO_doc, string TGT);

	static map<string, string> Hrefs, Hsystems;
	static map<string, vector<vector<string> > > IDX;
	static map<string, int> wc;
	static string src;
};

#endif