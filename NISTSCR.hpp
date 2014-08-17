#ifndef NISTSCR_HPP
#define NISTSCR_HPP

#include <string>
#include <vector>
#include <map>

using namespace std;

class NISTSCR {
private:

	static int negate_or_not(int n, int do_neg);
	static pair<string, int> get_score(const vector<string> &l, string G, int do_neg);

public:

	static map<string, int> read_scr_file(string file, string G, int do_neg);
};

#endif