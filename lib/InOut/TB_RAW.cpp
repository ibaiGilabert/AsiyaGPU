#include "../include/TB_RAW.hpp"
#include "../Common.hpp"
#include "../Config.hpp"

#include <fstream>
#include <sstream>

#include <boost/regex.hpp>
#include <boost/filesystem.hpp>
#include <boost/algorithm/string.hpp>


void TB_RAW::write_fake_idx_file(string file, vector<vector<string> > &lIDX) {
    // description _ writes a fake idx file, given a raw input file, and loads IDX structure into memory
    if (Config::verbose) fprintf(stderr, "reading raw file <%s>\n", file.c_str());
    //vector<vector <string> > lIDX(0, vector<string>());

    string system_name = TESTBED::give_file_name(file);
    string file_idx = TESTBED::replace_extension(file, Common::IDXEXT); //file + "." + Common::IDXEXT;
//cout << "system_name: " << system_name << endl;
//cout << "file(.txt): " << file << endl;
//cout << "file(.idx): " << file_idx << endl;

    ofstream f_idx(file_idx.c_str());
    if (f_idx) {
        string fake_header = Common::UNKNOWN_SET + " " + Common::UNKNOWN_LANG + " " + Common::UNKNOWN_LANG;
        f_idx << fake_header << endl;

        vector<string> l_header(3);
        l_header[0] = Common::UNKNOWN_SET; l_header[1] = Common::UNKNOWN_LANG; l_header[2] = Common::UNKNOWN_LANG;
       /* boost::regex reeq(" ");
        boost::sregex_token_iterator j;
        for(boost::sregex_token_iterator i(fake_header.begin(), fake_header.end(), reeq, -1); i != j; ++i) {
            l_header.push_back(*i);
        }
        cout << "l_header: ";
        for(int k = 0; k < l_header.size(); ++k) cout << l_header[k] << ",";
        cout << endl;*/

        lIDX.push_back(l_header);

        ifstream f_raw(file.c_str());
        if (f_raw) {
            string line;
            int i = 1;

                char buf[16];
            while (getline(f_raw, line)) {
                stringstream sf;
                sf << Common::UNKNOWN_DOC << " " << Common::UNKNOWN_GENRE << " " << system_name << " " << i;
                string fake_line = sf.str();

                vector<string> l(4);
                string token;
                for(int j = 0; j < l.size(); ++j) {
                        getline(sf, token, ' ');
                        l[j] = token;
                }
                //l[0] = Common::UNKNOWN_DOC;   l[1] = Common::UNKNOWN_GENRE;   l[2] = system_name;     l[3] = itao(i, buf, 10);

                /*boost::sregex_token_iterator jj;
                for(boost::sregex_token_iterator ii(fake_line.begin(), fake_line.end(), reeq, -1); ii != jj; ++ii) {
                    l.push_back(*ii);
                }
                cout << "l: ";
                for(int k = 0; k < l.size(); ++k) cout << l[k] << ",";
                cout << endl;*/
                lIDX.push_back(l);
                f_idx << fake_line << endl;
                i++;
            }
            f_raw.close();
        } else { fprintf(stderr, "couldn't open input file: %s\n", file.c_str());   exit(1); }

        f_idx.close();
    } else { fprintf(stderr, "couldn't open output IDX file: %s\n", system_name.c_str());       exit(1); }
}

void TB_RAW::read_fake_idx_file(string file, vector<vector<string> > &lIDX) {

    if (Config::verbose) fprintf(stderr, "reading idx file <%s>\n", file.c_str());

    string system_name = TESTBED::give_file_name(file);
    string file_idx = TESTBED::replace_extension(file, Common::IDXEXT); //file + "." + Common::IDXEXT;

    ifstream f_idx(file_idx.c_str());
    if (f_idx) {
        string line;
        getline(f_idx, line);       //get header

        vector<string> l_header(3);
        l_header[0] = Common::UNKNOWN_SET; l_header[1] = Common::UNKNOWN_LANG; l_header[2] = Common::UNKNOWN_LANG;
        lIDX.push_back(l_header);

        while (getline(f_idx, line)) {
            string token;
            istringstream buf(line);
            vector<string> l(4);
            for(int j = 0; j < l.size(); ++j) {
                    getline(buf, token, ' ');
                    l[j] = token;
            }
            lIDX.push_back(l);
        }
        f_idx.close();
    } else { fprintf(stderr, "couldn't open input IDX file: %s\n", file_idx.c_str()); exit(1); }
}

string TB_RAW::process_file(string file, string type) {
    // description _ read the contents of a RAW plain text file (one sentence per line) and generate fake idx files
    //               (idx structure is also stored onto memory)
    //fprintf(stderr, "%s\n", "----------NIST RAW FILES----------");

    string idxfile = TESTBED::replace_extension(file, Common::IDXEXT);
    string tokfile = TESTBED::replace_extension(file, Common::TOKEXT); //boost::filesystem::path(file).replace_extension(".tok").string();
    string lang;

    vector<vector<string> > rIDX; //(0, vector<string>());
    if (Config::serialize) read_fake_idx_file(idxfile, rIDX);
    else write_fake_idx_file(file, rIDX);

    if (type == "source" or type == "src") {
        TESTBED::src = file; //tokfile;
        TESTBED::IDX["source"] = rIDX;
        TESTBED::wc["source"] = rIDX.size() - 1;
        lang = Config::SRCLANG;
    }
    else if (type == "reference" or type == "ref") {
        string R = TESTBED::give_file_name(file);
        //fprintf(stderr, "\tR: '%s'\n", R.c_str());
        TESTBED::IDX[R] = rIDX;

        if (TESTBED::Hrefs.find(R) != TESTBED::Hrefs.end()) {
            fprintf(stderr, "[ERROR] reference name '%s' duplicated!\n", R.c_str()); exit(1);
        }
        TESTBED::wc[R] = rIDX.size()-1;
        TESTBED::Hrefs[R] = file; //tokfile;
        lang = Config::LANG;
    }
    else if (type == "system" or type =="sys") {
        string S = TESTBED::give_file_name(file);
        TESTBED::IDX[S] = rIDX;
        if (TESTBED::Hsystems.find(S) != TESTBED::Hsystems.end()) {
            fprintf(stderr, "[ERROR] system name '%s' duplicated!\n", S.c_str()); exit(1);
        }
        TESTBED::wc[S] = rIDX.size()-1;
        TESTBED::Hsystems[S] = file; //tokfile;
        lang = Config::LANG;
    }
    else { fprintf(stderr, "[ERROR] unkown file type <%s>!!\n", type.c_str()); exit(1); }

    if (!exists(boost::filesystem::path(tokfile))) {
        stringstream sc, ms;
        sc << "cp -f "<< file << " " << tokfile;
        ms << "[ERROR] could not copy " << file << " into " << tokfile;
        //if (exists(boost::filesystem::path(tokfile))) fprintf(stderr, "[TB_RAW] tokefile exists (%s)\n", tokfile.c_str());
        //else fprintf(stderr, "[TB_RAW]: tokefile NOT exists (%s)\n", tokfile.c_str());
        Common::execute_or_die(sc.str(), ms.str());
    }
    return file;
}
