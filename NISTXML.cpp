#include "NISTXML.hpp"
#include "Common.hpp"
#include <fstream>
#include <sstream>
#include <stdlib.h>
#include <boost/regex.hpp>


vector<vector<string> > write_fake_idx_file(string file, string IDX, int verbose) {
    vector<vector <string> > lIDX(0, vector<string>());

	if (verbose) fprintf(stderr, "reading raw file <%s>\n", file.c_str());
	string system_name = give_system_name(file);
    ofstream f_idx(system_name.c_str());
    if (f_idx) {
        stringstream ss;
        ss << UNKNOWN_SET << " " << UNKNOWN_LANG << " " << UNKNOWN_LANG;
        string fake_header = ss.str();

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
                sf << UNKNOWN_DOC << " " << UNKNOWN_GENRE << " " << system_name << " " << i;
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
