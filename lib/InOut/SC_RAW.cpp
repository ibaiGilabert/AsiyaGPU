#include "../include/SC_RAW.hpp"
#include "../include/TESTBED.hpp"
#include "../Config.hpp"
#include "../Common.hpp"

#include <iostream>
#include <sstream>
#include <iomanip>

#include <stdio.h>

using namespace std;



void SC_RAW::print_MMATRIX_header(const vector<string> &sorted_metrics) {
    // description _ print matrix score header (on a metric basis)
    stringstream head;
    if (Config::G == Common::G_SYS) {
        //head << "%-" << Config::setid_length << "s %-" << Config::sysid_length << "s";
        cout << "\tsetid_length: " << Config::setid_length << endl;
        cout << "\tsysid_length: " << Config::sysid_length << endl;

        head << "SET" << setw(Config::setid_length) << "SYS" << setw(Config::sysid_length);

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

void SC_RAW::print_system_scores_MMATRIX(string sys, const Scores &hOQ, const vector<string> &sorted_metrics, string ref) {
    // description _ print scores for a given system according to a given metric
    //int doALL =
    string SO = *Config::systems.begin();
    string setid = TESTBED::IDX[SO][0][0];
    string sysid = TESTBED::IDX[SO][1][2];

    if (Config::G == Common::G_SYS or Config::G == Common::G_ALL) { // SYSTEM SCORE
        vector<double> scores;
        for(int i = 0; i < sorted_metrics.size(); ++i) {
            scores.push_back(hOQ.get_sys_scores()[ sorted_metrics[i] ][sys][ref]);
            //scores.push_back(trunk_number(hOQ.get_sys_scores()[metric][sys][ref]), Common::METRIC_NAME_LENGTH, Config::float_precision);
        }
        cout << setid << setw(Config::setid_length) << sysid << setw(Config::sysid_length);
        cout.precision(Common::METRIC_NAME_LENGTH);
        cout << scores[0];
        for (int j = 1; j < scores.size(); ++j) cout << " " << scores[j];
    }
    if (Config::G == Common::G_DOC or Config::G == Common::G_ALL) { // DOCUMENT SCORES
        vector<string> ldoc_ids;
        TESTBED::get_docid_list(sys, ldoc_ids);
        for (int i = 0; i < hOQ.get_doc_scores_size(); ++i) {
            vector<double> scores;
            string docid = ldoc_ids[i];
            for(int j = 0; j < sorted_metrics.size(); ++j) {
                scores.push_back(hOQ.get_doc_scores(j)[sorted_metrics[j]][sys][ref]);
            }
            cout << setid << setw(Config::setid_length) << sysid << setw(Config::sysid_length) << docid << setw(Config::docid_length);
            cout.precision(Common::METRIC_NAME_LENGTH);
            cout << scores[0];
            for (int k = 1; k < scores.size(); ++k) cout << " " << scores[k];
        }
    }


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
        print_system_scores_MMATRIX(*it, hOQ, sorted_metrics, REF);
    }
    if (Config::do_refs) {

    }
}