#ifndef NISTXML_HPP
#define NISTXML_HPP

#include <string>
#include <vector>
#include <libxml/parser.h>
#include <libxml/tree.h>

using namespace std;

class NISTXML {
private:
	//void SGML_f_create_create_doc(string input, string output, int type, string sysid, xmlDocPtr &doc, xmlNodePtr &root_node);

public:
	static vector<vector<string> > write_fake_idx_file(string file, string IDX, int verbose);


	static void SGML_f_create_mteval_doc(string input, string output, int type);
	static void SGML_f_create_mteval_multidoc(string output, int type);
};

#endif