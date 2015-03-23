#include "../include/SC_RAW.hpp"
#include "../include/TESTBED.hpp"
#include "../Config.hpp"
#include "../Common.hpp"

#include <iostream>
#include <sstream>
#include <iomanip>
#include <numeric>

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

using namespace std;

int sum_string_chars(int sum, const string& str) {
    return sum + str.size();
}

void SC_RAW::print_MMATRIX_header(const vector<string> &sorted_metrics) {
    // description _ print matrix score header (on a metric basis)
    int chars = Config::setid_length + Config::sysid_length + Config::docid_length + Config::segid_length;

    char buffer[2*chars];
    if (Config::G == Common::G_SYS) {
        sprintf(buffer, "%-*s %-*s", Config::setid_length, "SET", Config::sysid_length, "SYS");
    } else if (Config::G == Common::G_DOC) {
        sprintf(buffer, "%-*s %-*s %-*s", Config::setid_length, "SET", Config::sysid_length, "SYS", Config::docid_length, "DOC");
    } else if (Config::G == Common::G_SEG) {
        sprintf(buffer, "%-*s %-*s %-*s %-*s", Config::setid_length, "SET", Config::sysid_length, "SYS", Config::docid_length, "DOC", Config::segid_length, "SEG");
    } else if (Config::G == Common::G_ALL) {
        sprintf(buffer, "%-*s %-*s %-*s %-*s", Config::setid_length, "SET", Config::sysid_length, "SYS", Config::docid_length, "DOC", Config::segid_length, "SEG");
    } else { fprintf(stderr, "[ERROR] unknown granularity <%s>!\n", Config::G.c_str()); exit(1); }
    //fprintf(stderr, "\n\nsetid_length: %d, setid: %s\n", Config::setid_length, setid.c_str());
    //fprintf(stderr, "\tsysid_length: %d, sysid: %s\n", Config::setid_length, sysid.c_str());

    printf("%s", buffer);
    for(int i = 0; i < sorted_metrics.size(); ++i)
        printf(" %s", trunk_string(sorted_metrics[i], Common::METRIC_NAME_LENGTH).c_str());
    printf("\n");

    int length = strlen(buffer);
    length += (Common::METRIC_NAME_LENGTH + 1)*sorted_metrics.size();
    print_hline('=', length);
}

void SC_RAW::print_system_scores_MMATRIX(string sys, const Scores &hOQ, const vector<string> &sorted_metrics, string ref) {
    // description _ print scores for a given system according to a given metric
    //int doALL =
    //int chars = accumulate(sorted_metrics.begin(), sorted_metrics.end(), 0, sum_string_chars);
    int chars = Config::setid_length + Config::sysid_length + Config::docid_length + Config::segid_length;

    char buffer[2*chars];
    string SO = *Config::systems.begin();
    string setid = TESTBED::IDX[SO][0][0];
    string sysid = TESTBED::IDX[sys][1][2];
    //int doALL =
    if (Config::G == Common::G_SYS or Config::G == Common::G_ALL) { // SYSTEM SCORE
        string scores;
        for(int i = 0; i < sorted_metrics.size(); ++i)
            scores += " " + trunk_number(hOQ.get_sys_scores()[sorted_metrics[i]][sys][ref], Common::METRIC_NAME_LENGTH);

        sprintf(buffer, "%-*s %-*s%s", Config::setid_length, setid.c_str(), Config::sysid_length, sysid.c_str(), scores.c_str());
        printf("%s\n", buffer);
    }
    if (Config::G == Common::G_DOC or Config::G == Common::G_ALL) { // DOCUMENT SCORES
        vector<string> ldoc_ids;
        TESTBED::get_docid_list(sys, ldoc_ids);
        for (int i = 0; i < hOQ.get_num_doc_scores(); ++i) {
            string scores, docid;
            docid = ldoc_ids[i];
            for(int j = 0; j < sorted_metrics.size(); ++j)
                scores += " " + trunk_number(hOQ.get_doc_scores(i)[sorted_metrics[j]][sys][ref], Common::METRIC_NAME_LENGTH);

            sprintf(buffer, "%-*s %-*s %-*s%s", Config::setid_length, setid.c_str(), Config::sysid_length, sysid.c_str(), Config::docid_length, docid.c_str(), scores.c_str());
            printf("%s\n", buffer);
        }
    }
    if (Config::G == Common::G_SEG or Config::G == Common::G_ALL) { // SEGMENT SCORES
        for (int i = 0; i < hOQ.get_num_seg_scores(); ++i) {
            //if (semgents...doALL...)
            string scores, docid, segid;
            docid = TESTBED::IDX[sys][i + 1][0];
            segid = TESTBED::IDX[sys][i + 1][3];
            for(int j = 0; j < sorted_metrics.size(); ++j)
                scores += " " + trunk_number(hOQ.get_seg_scores(i)[sorted_metrics[j]][sys][ref], Common::METRIC_NAME_LENGTH);

            sprintf(buffer, "%-*s %-*s %-*s %-*s%s", Config::setid_length, setid.c_str(), Config::sysid_length, sysid.c_str(), Config::docid_length, docid.c_str(), Config::segid_length, segid.c_str(), scores.c_str());
            printf("%s\n", buffer);
        }
    }
}

void SC_RAW::print_scores_MMATRIX(const Scores &hOQ, const vector<string> &sorted_metrics) {
    // description _ print metric scores in MMATRIX format (on a metric basis)
    if (Config::verbose) fprintf(stderr, "[SC_RAW]: Print Scores MMATRIX format\n");
    string REF = Common::join_set(Config::references, '_');

    print_MMATRIX_header(sorted_metrics);

    for(set<string>::const_iterator it = Config::systems.begin(); it != Config::systems.end(); ++it)    // systems
        print_system_scores_MMATRIX(*it, hOQ, sorted_metrics, REF);

    if (Config::do_refs) {
        for(set<string>::const_iterator it = Config::references.begin(); it != Config::references.end(); ++it) {    // references
            set<string> all_other_refs(Config::references);
            all_other_refs.erase(Config::references.find(*it));
            if (!all_other_refs.empty()) {
                REF = Common::join_set(all_other_refs, '_');
                print_system_scores_MMATRIX(*it, hOQ, sorted_metrics, REF);
            }
        }
    }
}
