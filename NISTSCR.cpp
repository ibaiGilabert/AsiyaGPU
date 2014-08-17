#include "NISTSCR.hpp"
#include "Common.hpp"

#include <iostream>
#include <fstream>
#include <sstream>

#include <boost/algorithm/string.hpp>

map<string, int> NISTSCR::read_scr_file(string file, string G, int do_neg) {
	// description _ reads a given MetricsMaTr format scr file (of a given granularity)
    map<string, int> scores;

    ifstream F(file.c_str());
    if (F) {
        string line;
        while (getline(F, line)) {

            vector<string> l;
            boost::split(l, "string to split", boost::is_any_of("\t "));

        	pair<string, int> p = get_score(l, G, do_neg);
            scores[p.first] = p.second;

        }
        F.close();
    } else { fprintf(stderr, "[ERROR] unavailable file <%s>\n", file.c_str());  exit(1); }

    F.close();

    return scores;
}

pair<string, int> NISTSCR::get_score(const vector<string> &l, string G, int do_neg) {
    // description _ reads the score from the corresponding column according to the given granularity
    int n;
    string k;
    if (G == Common::G_SYS) {
        k = "sys::" + l[1];
        n = negate_or_not(atoi(l[2].c_str()), do_neg);
    }
    else if (G == Common::G_DOC) {
        k = "sys::" + l[1] + "::doc::" + l[2];
        n = negate_or_not(atoi(l[3].c_str()), do_neg);
    }
    else if (G == Common::G_SEG) {
        k = "sys::" + l[1] + "::doc::" + l[2] + "::seg::" + l[3];
        n = negate_or_not(atoi(l[4].c_str()), do_neg);
    }

    return make_pair(k, n);
}

int NISTSCR::negate_or_not(int n, int do_neg) {
    // description _ negates the given arithmetic value iff do_neg is true, otherwise returns the value as is
    return do_neg? -n : n;
}