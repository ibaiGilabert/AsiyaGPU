#include "../include/SC_NIST.hpp"
#include "../Common.hpp"

#include <fstream>

#include <stdlib.h>

#include <boost/algorithm/string.hpp>

double SC_NIST::negate_or_not(double n, int do_neg) {
    // description _ negates the given arithmetic value iff do_neg is true, otherwise returns the value as is
    return do_neg? -n : n;
}

pair<string, double> SC_NIST::get_score(const vector<string> &l, string G, int do_neg) {
    // description _ reads the score from the corresponding column according to the given granularity
    double n;
    string k;
    if (G == Common::G_SYS) {
        k = "sys::" + l[1];
        n = negate_or_not(atof(l[2].c_str()), do_neg);
    }
    else if (G == Common::G_DOC) {
        k = "sys::" + l[1] + "::doc::" + l[2];
        n = negate_or_not(atof(l[3].c_str()), do_neg);
    }
    else if (G == Common::G_SEG) {
        k = "sys::" + l[1] + "::doc::" + l[2] + "::seg::" + l[3];
        n = negate_or_not(atof(l[4].c_str()), do_neg);
    }

    return make_pair(k, n);
}

map<string, double> SC_NIST::read_scores_file(string file, string G, int do_neg) {
    // description _ reads a given MetricsMaTr format scr file (of a given granularity)
    map<string, double> scores;

    ifstream F(file.c_str());
    if (F) {
        string line;
        while (getline(F, line)) {

            vector<string> l;
            boost::split(l, line, boost::is_any_of("\t "));

            pair<string, double> p = get_score(l, G, do_neg);
            scores[p.first] = p.second;

        }
        F.close();
    } else { fprintf(stderr, "[ERROR] unavailable file <%s>\n", file.c_str());  exit(1); }

    F.close();

    return scores;
}

/*void SC_NIST::print_scores() {
    // description _ print metric scores in NIST 'MetricsMATR' format (i.e., onto .scr files)
    //              -> all systems (system, document, segment levels) into the corresponding output files

    //list of metrics
    //sorted_metrics = get_sorted_metrics();
    //list of systems and references
    //systems = get_sorted_systems();
    string REF;
    set<string>::const_iterator it = Config::references.begin();
    REF = *it;
    ++it;
    while (it != Config::references.end()) {
        REF += "_" + *it;
        ++it;
    }
    compute_metric_combination();


}*/