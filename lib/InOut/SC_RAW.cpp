#include "../include/SC_RAW.hpp"
#include "../Config.hpp"
#include "../Common.hpp"

#include <iostream>
#include <sstream>

#include <stdio.h>
using namespace std;

/*#include <fstream>

#include <stdlib.h>*/

void SC_RAW::print_MMATRIX_header() {
    // description _ print matrix score header (on a metric basis)
    stringstream head;
    if (Config::G == Common::G_SYS) {
        head << "%-" << Config::setid_length << "s %-" << Config::sysid_length << "s";
        string aux = head.str();
        cout << "aux: |" << aux << "|" << endl;
        //sprintf(aux.c_str(), "SET", "SYS");

    }
}

void SC_RAW::print_system_scores_MMATRIX(string s) {

}

void SC_RAW::print_scores_NIST(const Scores &hOQ) {

}

void SC_RAW::print_scores_MMATRIX(const Scores &hOQ) {
    // description _ print metric scores in MMATRIX format (on a metric basis)
    string REF;
    set<string>::const_iterator it = Config::references.begin();
    REF = *it;  ++it;
    while (it != Config::references.end()) {
        REF += "_" + *it;   ++it;
    }
    print_MMATRIX_header();

    for(set<string>::const_iterator it = Config::systems.begin(); it != Config::systems.end(); ++it) {
        print_system_scores_MMATRIX(*it);
    }
    if (Config::do_refs) {

    }
}