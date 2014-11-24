#ifndef TB_RAW_HPP
#define TB_RAW_HPP

#include "TB_FORMAT.hpp"
#include "Scores.hpp"

#include <string>
#include <vector>

using namespace std;

class TB_RAW : public TB_FORMAT {
private:
	//write
	void write_fake_idx_file(string file, vector<vector<string> > &lIDX);
	
	//read
	void read_fake_idx_file(string file, vector<vector<string> > &lIDX);

public:
	
	string process_file(string file, string type);

};

#endif
