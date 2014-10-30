#include "../include/SC_FORMAT.hpp"

#include <stdio.h>

#include <sstream>
#include <iomanip>
#include <iostream>

using namespace std;

const int SC_FORMAT::FLOAT_LENGTH = 10;
const int SC_FORMAT::FLOAT_PRECISION = 8;
const string SC_FORMAT::ROOT_ELEMENT = "REPORT";

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
    // description _ trunks the given string to the given length (left aligned)
    char buffer[l];
    sprintf(buffer, "%*s", l, s.c_str());
    return string(buffer);
}

string SC_FORMAT::trunk_number(double f, int l) {
    // description _ trunks the given number into a float (given length and precision)
    char buffer[l];
    sprintf(buffer, "%*.*f", l, FLOAT_PRECISION, f);
    return (buffer);
}

string SC_FORMAT::trunk_and_trim_number(double f) {
    // description _ trunks the given number into a float (given length and precision)
    char buffer[FLOAT_LENGTH];
    sprintf(buffer, "%*.*f", FLOAT_LENGTH, FLOAT_PRECISION, f);
    return string(buffer);
}