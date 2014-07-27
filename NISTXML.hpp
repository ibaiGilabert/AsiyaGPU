#ifndef NISTXML_HPP
#define NISTXML_HPP

#include <string>
#include <vector>
using namespace std;

class NISTXML {
private:

public:
	static vector<vector<string> > write_fake_idx_file(string file, string IDX, int verbose);

};

#endif