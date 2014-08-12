// regex_replace example
#include <iostream>
#include <string>
#include <regex>
#include <iterator>

int main ()
{
	std::string s ("there is a subsequence in the string\n");
	std::regex e ("\\b(sub)([^ ]*)");   // matches words beginning by "sub"

	string ss = "sub-$2";
	const char* sc = ss.c_str();


	// using string/c-string (3) version:
	//std::cout << std::regex_replace (s,e,"sub-$2");


	std::cout << std::regex_replace (s,e,sc);



}