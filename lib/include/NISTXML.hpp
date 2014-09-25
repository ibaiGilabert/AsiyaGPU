#ifndef NISTXML_HPP
#define NISTXML_HPP

#include "TESTBED.hpp"

#include <string>
#include <vector>
#include <map>

#include <libxml/parser.h>
#include <libxml/tree.h>

using namespace std;


class NISTXML : public TESTBED {
private:
	//void SGML_f_create_create_doc(string input, string output, int type, string sysid, xmlDocPtr &doc, xmlNodePtr &root_node);
	static double negate_or_not(double n, int do_neg);
	static pair<string, double> get_score(const vector<string> &l, string G, int do_neg);

public:
	//read scores
	static map<string, double> read_scr_file(string file, string G, int do_neg);

	//read nist input format
	static void process_xml(xmlNodePtr a_node, ofstream &out_txt, ofstream &out_idx, map<string, FileInfo> &m, string id, string docid, string genre);
	static map<string, FileInfo> read_file(const char* file);
	static void process_nist_file(string file, string type);

	//write middle score files
	static void SGML_f_create_mteval_doc(string input, string output, int type);
	static void SGML_f_create_mteval_multidoc(string output, int type);

	static void SGML_GTM_f_create_mteval_doc(string input, string output);

	static void f_create_mteval_doc(string input, string output, string TGT, string cas, int type);
	static void f_create_mteval_multidoc(string output, string cas, int type);
};

#endif