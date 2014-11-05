#ifndef TB_FORMAT_HPP
#define TB_FORMAT_HPP

#include "TESTBED.hpp"

#include <vector>
#include <string>

using namespace std;

struct FileInfo {
	vector<vector<string> > idx;    //vector de linies. Linia -> vector de paraules
    string txt;
    int wc;
};

class TB_FORMAT {
protected:

public:
	// split data files
	//xmlNodePtr split_xml(xmlNodePtr a_node, ofstream &out_txt, ofstream &out_idx, string id, string docid, string genre, int chunk, int seg);
    void split_file(const char* file, int s);
    void split_txt_idx(string file, int s);
};

#endif