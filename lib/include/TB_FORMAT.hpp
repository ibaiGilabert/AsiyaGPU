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
private:
	static map<string, string> create_rLANGTOK();
	
protected:
    //void split_file(const char* in_file, const char* out_file, const char* ext);
    void split_file(const char* file, const char* ext);

	static void tokenize_file(string file, string lang);

	static map<string, string> rLANGTOK;
	static const string TOK;

public:
	//TB_FORMAT();
	//~TB_FORMAT();
	static int chunk;

	// split data files
	//xmlNodePtr split_xml(xmlNodePtr a_node, ofstream &out_txt, ofstream &out_idx, string id, string docid, string genre, int chunk, int seg);
    //void split_txt_idx(string input, string output);
	void split_txt_idx(string file);
	
	static string get_split(string file, string ext, int thread);
	static char* get_serial(string METRIC, string TGT, string REF, int thread);
	static int get_thread(string file);
	//static string get_formated_thread(string file);

	static char* make_serial(string METRIC, string TGT, string REF);

	virtual string process_file(string file, string type) {}

};

#endif
