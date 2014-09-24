#ifndef NISTXML_HPP
#define NISTXML_HPP

#include <string>
#include <vector>
#include <map>

using namespace std;

class NISTXML {
private:
	//void SGML_f_create_create_doc(string input, string output, int type, string sysid, xmlDocPtr &doc, xmlNodePtr &root_node);

	static double negate_or_not(double n, int do_neg);
	static pair<string, double> get_score(const vector<string> &l, string G, int do_neg);
public:
	//static read_file(string file);

	//read scores
	static map<string, double> read_scr_file(string file, string G, int do_neg);

	//read input
	static map<string,> read_file(string file);

	//write
	static vector<vector<string> > write_fake_idx_file(string file, string IDX, int verbose);

	static void SGML_f_create_mteval_doc(string input, string output, int type);
	static void SGML_f_create_mteval_multidoc(string output, int type);

	static void SGML_GTM_f_create_mteval_doc(string input, string output);

	static void f_create_mteval_doc(string input, string output, string TGT, string cas, int type);
	static void f_create_mteval_multidoc(string output, string cas, int type);
};

#endif