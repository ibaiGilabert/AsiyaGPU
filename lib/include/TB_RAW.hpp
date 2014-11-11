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
	static void write_fake_idx_file(string file, string IDX, vector<vector<string> > &lIDX);

	string process_file(string file, string type);

	//Serialize hash scores
	void save_struct_scores(const Scores &hOQ, const char* filename);
	void load_struct_scores(Scores &hOQ, const char* filename);

};

#endif