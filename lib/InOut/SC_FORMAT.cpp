#include "../include/SC_FORMAT.hpp"

#include <stdio.h>

#include <sstream>
#include <iomanip>
#include <iostream>

using namespace std;

void SC_FORMAT::print_hline(char c, int l) {
    //description _ print horizontal line
    //param1 _ character
    //param1 _ length
    string s = "";
    for (int i = 0; i < l; ++i) s += c;
    cout << s << endl;
}

void SC_FORMAT::print_hline_stderr(char c, int l) {
    //description _ print horizontal line
    //param1 _ character
    //param1 _ length

    string s = "";
    for (int i = 0; i < l; ++i) s += c;
    fprintf(stderr, "%s\n", s.c_str());
}

string SC_FORMAT::trunk_string(string s, int l) {
    // description _ trunks the given string to the given length
    stringstream x;
    x << setw(l) << s;
    return x.str();
}
/*double SC_FORMAT::trunk_number(int n, int l, int p) {
    // description _ trunks the given number into a float (given length and precision)
}*/