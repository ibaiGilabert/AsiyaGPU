#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#include <boost/regex.hpp>
#include <boost/algorithm/string.hpp>

using namespace std;

int main()
{

    boost::regex re1("^ +NIST score using.*");
    boost::regex re2("^ +cumulative-NIST score using.*");
    boost::regex re3("^ +individual-NIST score using.*");

    vector<double> lnist1, lnist2, lnist3, lnist4, lnist5;
    vector<double> lnist1i, lnist2i, lnist3i, lnist4i, lnist5i;

    vector<vector<double> > SEG(10);

    string str;
    ifstream file("reportNIST.txt");
    if (file) {
	    while (getline(file, str)) {
	    	boost::match_results<string::const_iterator> results;

	        if (boost::regex_match(str, results, re1)) {
	            cout << "\t That was a kind of line" << endl;
	            string s = results[0];
	            cout << "line: |" << s << "|" << endl;

				vector<string> strs;
				boost::split(strs, s, boost::is_any_of("\t "));
				lnist1.push_back(atof(strs[7].c_str()));
				lnist2.push_back(atof(strs[8].c_str()));
				lnist3.push_back(atof(strs[9].c_str()));
				lnist4.push_back(atof(strs[10].c_str()));
				lnist5.push_back(atof(strs[11].c_str()));

	   			for (int i = 0; i < strs.size(); ++i) cout << "strs[" << i << "]: " << strs[i] << endl;
			}
			else if (boost::regex_match(str, results, re2)) {
	            cout << "\t That was a kind of line" << endl;
	            string s = results[0];
	            cout << "line: |" << s << "|" << endl;

				vector<string> strs;
				boost::split(strs, s, boost::is_any_of("\t "));
				lnist1.push_back(atof(strs[7].c_str()));
				lnist2.push_back(atof(strs[8].c_str()));
				lnist3.push_back(atof(strs[9].c_str()));
				lnist4.push_back(atof(strs[10].c_str()));
				lnist5.push_back(atof(strs[11].c_str()));

	   			for (int i = 0; i < strs.size(); ++i) cout << "strs[" << i << "]: " << strs[i] << endl;
			}
			else if (boost::regex_match(str, results, re3)) {
	            cout << "\t That was a kind of line" << endl;
	            string s = results[0];
	            cout << "line: |" << s << "|" << endl;

				vector<string> strs;
	            boost::split(strs, s, boost::is_any_of("\t "));
				lnist1i.push_back(atof(strs[7].c_str()));
				lnist2i.push_back(atof(strs[8].c_str()));
				lnist3i.push_back(atof(strs[9].c_str()));
				lnist4i.push_back(atof(strs[10].c_str()));
				lnist5i.push_back(atof(strs[11].c_str()));

	   			for (int i = 0; i < strs.size(); ++i) cout << "strs[" << i << "]: " << strs[i] << endl;
			}
	    }
        file.close();
        SEG[0] = lnist1;	SEG[1] = lnist2;	SEG[2] = lnist3;	SEG[3] = lnist4;	SEG[4] = lnist5;
        SEG[5] = lnist1i;	SEG[6] = lnist2i;	SEG[7] = lnist3i;	SEG[8] = lnist4i;	SEG[9] = lnist5i;

	} else { fprintf(stderr, "couldn't open file: reportNIST.txt\n"); exit(1); }

		cout << "--------------------SEG-----------------" << endl;
		for (int i = 0; i < SEG.size(); ++i) {
			for (int j = 0; j < SEG[i].size(); ++j) {
				cout << "SEG[" << i << "," << j << "]: " << SEG[i][j] << "\t";
			}
			cout << endl;
		}
}