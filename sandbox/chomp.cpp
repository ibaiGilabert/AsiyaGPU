#include <boost/algorithm/string.hpp>
#include <iostream>
#include <fstream>
#include <string>
#include <boost/regex.hpp>

using namespace std;
//using namespace boost;

// ...
int main() {
  /*string str1(" hello world! \n");
  string str1t, str1r;
  str1t = str1r = str1;
  trim(str1t);      // str1 == "HELLO WORLD!"
  cout << "Trimming:" << endl << str1t;
  replace_last(str1r, "\n", "");
  cout << "replace_last:" << endl << str1r;*/

  ifstream file("Asiya.config");
  boost::regex re("^[^#].*=.*");
  string str;
  int i = 0;

  while (getline(file, str)) {
    cout << "Linia " << ++i << endl;
    cout << '\t' << str << endl;
    boost::match_results<string::const_iterator> results;
    if (boost::regex_match(str, results, re)) {
      cout << "\t That was a kind of line" << endl;

      string s = results[0];

      boost::regex reeq("=");
      boost::sregex_token_iterator i(s.begin(), s.end(), reeq, -1);
      //boost::sregex_token_iterator j;
      //int count = 0;
      pair<string, string> entry(*i++, *i++);
      /*while (i != j) {
        cout << *i++ << '|';
        count++;
      }*/
      cout << "\tTokens: " << entry.first << " | " << entry.second << endl;
      //std::transform(str.begin(), str.end(), str.begin(), ::tolower);
      if (boost::to_lower(entry.second) == "input") {
        if (boost::to_lower(entry.first) == I_NIST) {
          CONFIG.I = I_NIST;
        }
        else {
          CONFIG.I = I_RAW;
        }
      }



      //cout << endl << "\tThere were " << count << " tokens found." << endl;

    }
    //cout << "Match: " << results[2] << endl;
  }

}
