#ifndef TB_RAW_HPP
#define TB_RAW_HPP

#include "TB_FORMAT.hpp"
#include "Scores.hpp"

#include <string>
#include <vector>

using namespace std;

class TB_RAW : public TB_FORMAT {
private:

public:
	//write
	static void write_fake_idx_file(string file, string IDX, vector<vector<string> > &lIDX);

	string process_file(string file, string type);

};

#endif