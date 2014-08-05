#ifndef NISTXML_HPP
#define NISTXML_HPP

#include <string>
#include <vector>
using namespace std;

class NISTXML {
private:

public:
	static vector<vector<string> > write_fake_idx_file(string file, string IDX, int verbose);

	static void SGML_f_create_mteval_multidoc(string output, int type);
};

#endif