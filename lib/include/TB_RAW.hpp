#ifndef TB_RAW_HPP
#define TB_RAW_HPP

#include "TB_FORMAT.hpp"

#include <string>
#include <vector>

using namespace std;

class TB_RAW : public TB_FORMAT {
private:

public:
	static string give_system_name(string file);

	//write
	static vector<vector<string> > write_fake_idx_file(string file, string IDX);

	void process_raw_file(string file, string type);
};

#endif