#ifndef TB_NIST_HPP
#define TB_NIST_HPP

#include "TB_FORMAT.hpp"

#include <string>
#include <vector>
#include <map>

#include <libxml/parser.h>
#include <libxml/tree.h>

using namespace std;


class TB_NIST : public TB_FORMAT {
private:
	static void SGML_f_create_create_doc(string input, string output, string sysid, xmlDocPtr &doc, xmlNodePtr &root_node);
	static void f_create_create_doc(string input, string output, string TGT, string cas, int type);

public:
	// read nist input format
	static void process_xml(xmlNodePtr a_node, ofstream &out_txt, ofstream &out_idx, pair<string, FileInfo> &m, string id, string docid, string genre);
	static pair<string, FileInfo> read_file(const char* file);
	string process_file(string file, string type);

	// write middle score files
	static void SGML_f_create_mteval_doc(string input, string output, int type);
	static void SGML_f_create_mteval_multidoc(string output, int type);

	static void SGML_GTM_f_create_mteval_doc(string input, string output);

	static void f_create_mteval_doc(string input, string output, string TGT, string cas, int type);
	static void f_create_mteval_multidoc(string output, string cas, int type);
};

#endif