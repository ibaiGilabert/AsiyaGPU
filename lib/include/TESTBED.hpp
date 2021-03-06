#ifndef TESTBED_HPP
#define TESTBED_HPP

#include <string>
#include <vector>
#include <map>

using namespace std;


class TESTBED {
private:


public:
	static string give_file_name(string file);
	static string give_relative_name(string file);
	static string replace_extension(string file, string ext);
	static string replace_special_characters(string &input);

	static void get_docid_list(string sys, vector<string> &ldoc_ids);

	static int get_num_docs();
	static int get_num_segs();

	static int get_setid_length(string sys);
	static int get_max_docid_length(string sys);
	static int get_max_segid_length(string sys);

	static void print_idx();

	static void do_metric_names();
	static void do_system_names();
	static void do_reference_names();

	static void get_seg_doc_scores(const vector<double> &scores, int DO_doc, string TGT, vector<double> &D_scores, vector<double> &S_scores);

	static map<string, string> Hrefs, Hsystems;
	static map<string, vector<vector<string> > > IDX;
	static map<string, int> wc;
	static string src;
};

#endif