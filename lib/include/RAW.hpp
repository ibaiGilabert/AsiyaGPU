#ifndef RAW_HPP
#define RAW_HPP

#include "TESTBED.hpp"

#include <string>
#include <vector>

using namespace std;

class RAW : public TESTBED {
private:

public:
	//write
	static vector<vector<string> > write_fake_idx_file(string file, string IDX);

	static void process_raw_file(string file, string type);

};

#endif