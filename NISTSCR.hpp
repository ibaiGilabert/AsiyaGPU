#ifndef NISTSCR_HPP
#define NISTSCR_HPP

#include <string>
#include <vector>
#include <map>

using namespace std;

class NISTSCR {
private:

	static double negate_or_not(double n, int do_neg);
	static pair<string, double> get_score(const vector<string> &l, string G, int do_neg);

public:

	static map<string, double> read_scr_file(string file, string G, int do_neg);
};

#endif