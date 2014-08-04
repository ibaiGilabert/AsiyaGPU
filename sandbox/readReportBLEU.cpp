#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#include <boost/regex.hpp>
#include <boost/algorithm/string.hpp>

using namespace std;

int main()
{
/*	float a;
    ifstream file("reportBLEU.txt");

    while (file >> a) {
    	printf("%f ", a);
    	getchar();
	}
    file.close();

    cout << "FILE READED" << endl;
*/

    boost::regex re1("^ +BLEU score using.*");
    boost::regex re2("^ +cumulative-BLEU score using.*");
    boost::regex re3("^ +individual-BLEU score using.*");

    vector<double> lbleu1, lbleu2, lbleu3, lbleu4;
    vector<double> lbleu1i, lbleu2i, lbleu3i, lbleu4i;

    vector<vector<double> > SEG(8);

    string str;
    ifstream file("reportBLEU.txt");
    if (file) {
	    while (getline(file, str)) {
	    	boost::match_results<string::const_iterator> results;

	        if (boost::regex_match(str, results, re1)) {
	            cout << "\t That was a kind of line" << endl;
	            string s = results[0];
	            cout << "line: |" << s << "|" << endl;

				vector<string> strs;
				boost::split(strs, s, boost::is_any_of("\t "));
				lbleu1.push_back(atof(strs[7].c_str()));
				lbleu2.push_back(atof(strs[8].c_str()));
				lbleu3.push_back(atof(strs[9].c_str()));
				lbleu4.push_back(atof(strs[10].c_str()));
	   			//for (int i = 0; i < strs.size(); ++i) cout << "strs[" << i << "]: " << strs[i] << endl;
			}
			else if (boost::regex_match(str, results, re2)) {
	            cout << "\t That was a kind of line" << endl;
	            string s = results[0];
	            cout << "line: |" << s << "|" << endl;

				vector<string> strs;
				boost::split(strs, s, boost::is_any_of("\t "));
				lbleu1.push_back(atof(strs[7].c_str()));
				lbleu2.push_back(atof(strs[8].c_str()));
				lbleu3.push_back(atof(strs[9].c_str()));
				lbleu4.push_back(atof(strs[10].c_str()));
	   			//for (int i = 0; i < strs.size(); ++i) cout << "strs[" << i << "]: " << strs[i] << endl;
			}
			else if (boost::regex_match(str, results, re3)) {
	            cout << "\t That was a kind of line" << endl;
	            string s = results[0];
	            cout << "line: |" << s << "|" << endl;

				vector<string> strs;
	            boost::split(strs, s, boost::is_any_of("\t "));
				lbleu1i.push_back(atof(strs[7].c_str()));
				lbleu2i.push_back(atof(strs[8].c_str()));
				lbleu3i.push_back(atof(strs[9].c_str()));
				lbleu4i.push_back(atof(strs[10].c_str()));
	   			//for (int i = 0; i < strs.size(); ++i) cout << "strs[" << i << "]: " << strs[i] << endl;
			}
	    }
        file.close();
        SEG[0] = lbleu1;	SEG[1] = lbleu2;	SEG[2] = lbleu3;	SEG[3] = lbleu4;
        SEG[4] = lbleu1i;	SEG[5] = lbleu2i;	SEG[6] = lbleu3i;	SEG[7] = lbleu4i;

	} else { fprintf(stderr, "couldn't open file: reportBLEU.txt\n"); exit(1); }

	cout << "--------------------SEG-----------------" << endl;
	for (int i = 0; i < SEG.size(); ++i) {
		for (int j = 0; j < SEG[i].size(); ++j) {
			cout << "SEG[" << i << "," << j << "]: " << SEG[i][j] << "\t";
		}
		cout << endl;
	}

}