#ifndef TB_FORMAT_HPP
#define TB_FORMAT_HPP

#include "TESTBED.hpp"

#include <vector>
#include <string>

using namespace std;

struct FileInfo {
	vector<vector<string> > idx;    //vector de linies. Linia -> vector de paraules
    string txt;
    int wc;
};

class TB_FORMAT {
protected:

public:
	static string give_system_name(string file);	//PROTECTED btw...

};

#endif