#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <boost/regex.hpp>
using namespace std;

int main(int argc, char* argv[]) {
	if (argc < 1) { fprintf(stderr, "INPUT DATA!!!\n"); exit(1); }
	
	char out[80];
	strcpy(out, argv[1]);
	srtcat(out, ".results");
	ofstream output(out);
	if (!output.is_open()) { fprintf(stderr, "Could not open output file <%s>\n", out); exit(1); }

	boost::regex re("^TOTAL TIME.*");

	ifstream file(argv[1]);
	if (file) {
		string str;
		boost::match_results<string::const_iterator> results;
		while( getline(file, str) ) {
            if (boost::regex_match(str, results, re)) {
	    		vector<string> v;
	    		istringstream buf(str);
			    for(string token; getline(buf, token, ' '); ) v.push_back(token);
			    output << 
            }
		}
	}
	else { fprintf(stderr, "Could not open input file <%s>\n", argv[0]); exit(1); }
}


	    std::vector<std::string> v;
	    std::istringstream buf(s);
	    for(std::string token; getline(buf, token, ' '); )
	        v.push_back(token);