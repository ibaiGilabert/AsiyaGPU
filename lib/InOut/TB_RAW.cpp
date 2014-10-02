#include "../include/TB_RAW.hpp"
#include "../Common.hpp"
#include "../Config.hpp"

#include <fstream>
#include <sstream>

#include <boost/regex.hpp>
#include <boost/filesystem.hpp>
#include <boost/algorithm/string.hpp>


vector<vector<string> > TB_RAW::write_fake_idx_file(string file, string IDX) {
    // description _ writes a fake idx file, given a raw input file, and loads IDX structure into memory
    vector<vector <string> > lIDX(0, vector<string>());

	if (Config::verbose) fprintf(stderr, "reading raw file <%s>\n", file.c_str());

	string system_name = TB_FORMAT::give_system_name(file);
    ofstream f_idx(system_name.c_str());
    if (f_idx) {
        string fake_header = Common::UNKNOWN_SET + " " + Common::UNKNOWN_LANG + " " + Common::UNKNOWN_LANG;
        f_idx << fake_header << endl;

        vector<string> l_header;

        boost::regex reeq(" ");
        boost::sregex_token_iterator j;
        for(boost::sregex_token_iterator i(fake_header.begin(), fake_header.end(), reeq, -1); i != j; ++i) {
            l_header.push_back(*i);
        }
        lIDX.push_back(l_header);

        ifstream f_raw(file.c_str());
        if (f_raw) {
            string line;
            int i = 1;

            while (getline(f_raw, line)) {
                stringstream sf;
                sf << Common::UNKNOWN_DOC << " " << Common::UNKNOWN_GENRE << " " << system_name << " " << i;
                string fake_line = sf.str();

                vector<string> l;

                boost::sregex_token_iterator jj;
                for(boost::sregex_token_iterator ii(fake_line.begin(), fake_line.end(), reeq, -1); ii != jj; ++ii) {
                    l.push_back(*ii);
                }
                lIDX.push_back(l);
                f_idx << fake_line << endl;
                i++;
            }
            f_raw.close();
        } else { fprintf(stderr, "couldn't open input file: %s\n", file.c_str());   exit(1); }

        f_idx.close();
    } else { fprintf(stderr, "couldn't open output IDX file: %s\n", system_name.c_str());	exit(1); }

    return lIDX;
}


void TB_RAW::process_raw_file(string file, string type) {
    // description _ read the contents of a RAW plain text file (one sentence per line) and generate fake idx files
    //               (idx structure is also stored onto memory)
    cout << "----------NIST RAW FILES----------" << endl;

    string IDX = file + "." + Common::IDXEXT;
    string tokfile = file + "." + Common::TOKEXT;
    string lang;

    vector<vector<string> > rIDX = write_fake_idx_file(file, IDX);
    if (type == "source" or type == "src") {
        TESTBED::src = tokfile;
        TESTBED::IDX["source"] = rIDX;
        TESTBED::wc["source"] = rIDX.size() - 1;
        lang = Config::SRCLANG;
    }
    else if (type == "reference" or type == "ref") {
        string R = TB_FORMAT::give_system_name(file);
        cout << "\tR: '" << R << "'" << endl;
        TESTBED::IDX[R] = rIDX;

        if (TESTBED::Hrefs.find(R) != TESTBED::Hrefs.end()) {
            fprintf(stderr, "[ERROR] reference name '%s' duplicated!\n", R.c_str()); exit(1);
        }
        TESTBED::wc[R] = rIDX.size()-1;
        TESTBED::Hrefs[R] = tokfile;
        lang = Config::LANG;
    }
    else if (type == "system" or type =="sys") {
        string S = TB_FORMAT::give_system_name(file);
        TESTBED::IDX[S] = rIDX;
        if (TESTBED::Hsystems.find(S) != TESTBED::Hsystems.end()) {
            fprintf(stderr, "[ERROR] system name '%s' duplicated!\n", S.c_str()); exit(1);
        }
        TESTBED::wc[S] = rIDX.size()-1;
        TESTBED::Hsystems[S] = tokfile;
        lang = Config::LANG;
    }
    else { fprintf(stderr, "[ERROR] unkown file type <%s>!!\n", type.c_str()); exit(1); }

    stringstream sc, ms;
    sc << "cp -f "<< file << " " << tokfile;
    ms << "[ERROR] could not copy " << file << " into " << tokfile;

    Common::execute_or_die(sc.str(), ms.str());
}