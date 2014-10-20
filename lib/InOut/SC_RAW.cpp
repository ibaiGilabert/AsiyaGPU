#include "../include/SC_RAW.hpp"
#include "../Config.hpp"
#include "../Common.hpp"

#include <iostream>
#include <sstream>
#include <iomanip>

#include <stdio.h>
using namespace std;

/*#include <fstream>

#include <stdlib.h>*/

void SC_RAW::print_MMATRIX_header(const vector<string> &sorted_metrics) {
    // description _ print matrix score header (on a metric basis)
    stringstream head;
    if (Config::G == Common::G_SYS) {
        //head << "%-" << Config::setid_length << "s %-" << Config::sysid_length << "s";
        head << setw(Config::setid_length) << "SET" << setw(Config::sysid_length) << "SYS";

        string aux = head.str();
        cout << "aux: |" << aux << "|" << endl;
        //sprintf(aux.c_str(), "SET", "SYS");

    } else if (Config::G == Common::G_DOC) {

    }
    else { fprintf(stderr, "[ERROR] unknown granularity <%s>!\n", Config::G.c_str()); exit(1); }

    vector<string> header;
    for (int i = 0; i < sorted_metrics.size(); ++i) {
        header.push_back(trunk_string(sorted_metrics[i], Common::METRIC_NAME_LENGTH));
    }

    cout << head.str() << " " << header[0];
    for(int i = 1; i < header.size(); ++i) cout << " " << header[i];
    cout << endl;

    int length = head.str().size();
    length += (Common::METRIC_NAME_LENGTH + 1)*sorted_metrics.size();
    print_hline('=', length);

}

void SC_RAW::print_system_scores_MMATRIX(string s) {

}

void SC_RAW::print_scores_NIST(const Scores &hOQ) {

}

void SC_RAW::print_scores_MMATRIX(const Scores &hOQ, const vector<string> &sorted_metrics) {
    // description _ print metric scores in MMATRIX format (on a metric basis)
    string REF;
    set<string>::const_iterator it = Config::references.begin();
    REF = *it;  ++it;
    while (it != Config::references.end()) {
        REF += "_" + *it;   ++it;
    }
    print_MMATRIX_header(sorted_metrics);

    for(set<string>::const_iterator it = Config::systems.begin(); it != Config::systems.end(); ++it) {
        print_system_scores_MMATRIX(*it);
    }
    if (Config::do_refs) {

    }
}