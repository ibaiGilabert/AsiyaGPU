#include "../include/TESTBED.hpp"

#include <boost/regex.hpp>
#include <boost/filesystem.hpp>

map<string, vector<vector<string> > > TESTBED::IDX;
map<string, string> TESTBED::Hrefs, TESTBED::Hsystems;

map<string, int> TESTBED::wc;
string TESTBED::src;

void TESTBED::get_docid_list(string sys, vector<string> &ldoc_ids) {
    // description _ returns the list of document ids in the idx, in order of appearance
	string docid;
	for (int i = 1; i < TESTBED::IDX[sys].size(); ++i) {
		if (TESTBED::IDX[sys][i][0] != docid) {
			docid = TESTBED::IDX[sys][i][0];
			ldoc_ids.push_back(docid);
		}
	}
}

pair<vector<double>, vector<double> > TESTBED::get_seg_doc_scores(const vector<double> &scores, int DO_doc, string TGT) {
    // description _ returns segment and document scores, given an index structure which
    //               contains information on the number of segments per document
	vector<vector<string> > idx = TESTBED::IDX[TGT];
	vector<double> D_scores, S_scores;
	string docid = "";
	double sum = -1;
	int n_doc = 0;
	int n = 0;
    /*cout << "IDX[" << TGT << "]: " << endl;
    for (int i = 0; i < idx.size(); ++i) {
            cout << "\ti: " << i << ": [";
            for(int j = 0; j < idx[i].size(); ++j) cout << idx[i][j] << ", ";
            cout << "]" << endl;
    }*/
	for (int i = 1; i < idx.size(); ++i) {
		if (DO_doc) {	//doc-level scores
			if (idx[i][0] != docid)	{	//NEW DOCUMENT
				D_scores.push_back(scores[n_doc]);
				docid = idx[i][0];
				++n_doc;
			}
			S_scores.push_back(scores[n_doc-1]);
		}
		else {	//segment-level scores
			if (idx[i][0] != docid)	{	//NEW DOCUMENT
				if (sum != -1) D_scores.push_back(sum/n);
				docid = idx[i][0];
				sum = n = 0;
			}
			double x = 0;
			if (scores[i-1] != -1) x = scores[i-1];
			S_scores.push_back(x);
			sum += x;
			++n;
		}
	}
	// last document (only if segment-level scores)
	if (!DO_doc) {
		if (sum != -1) D_scores.push_back(sum/n);
	}

	return make_pair(D_scores, S_scores);
}

int TESTBED::get_setid_length(string sys) {
	// description _ returns the length of the set id of the given idx
	return TESTBED::IDX[sys].size();
}

int TESTBED::get_max_docid_length(string sys) {
	// description _ returns the length of the longest document id in the given idx
	int max = 0;
	for(int i = 1; i < TESTBED::IDX[sys].size(); ++i) {
		if (TESTBED::IDX[sys][i][0].size() > max) max = TESTBED::IDX[sys][i][0].size();
	}
	return max;
}

int TESTBED::get_max_segid_length(string sys) {
	// description _ returns the length of the longest segment id in the given idx
	int max = 0;
	for(int i = 1; i < TESTBED::IDX[sys].size(); ++i) {
		if (TESTBED::IDX[sys][i][3].size() > max) max = TESTBED::IDX[sys][i][3].size();
	}
	return max;
}

string TESTBED::give_system_name(string file) {
    // description _ get system name from filename
    boost::filesystem::path pathname (file);
    return pathname.filename().string();
}

string TESTBED::replace_special_characters(string &input) {
   // description _ replaces conflictive characters inside a given string (~filename)
	boost::regex re;
    re = ("\\*");   input = boost::regex_replace(input, re, "\\\\*");
    re = (";");     input = boost::regex_replace(input, re, "\\\\;");
    re = ("`");     input = boost::regex_replace(input, re, "\\\\`");
    re = ("'");     input = boost::regex_replace(input, re, "\\\\'");
    re = ("\\(");   input = boost::regex_replace(input, re, "\\\\(");
    re = ("\\)");   input = boost::regex_replace(input, re, "\\\\)");
    re = ("\\?");   input = boost::regex_replace(input, re, "\\\\?");
    return input;
}