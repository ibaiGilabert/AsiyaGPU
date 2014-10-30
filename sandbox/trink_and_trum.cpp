#include <iostream>
#include <math.h>
#include <stdio.h>
using namespace std;

const int FLOAT_LENGTH = 10;
const int FLOAT_PRECISION = 8;

int main() {
	double pi = 4*atan(1);
	cout << "pi: " << pi << endl;

	char buffer[100];
	sprintf(buffer, "%*.*f", FLOAT_LENGTH, FLOAT_PRECISION, pi);
	//cout <<
	cout << "pi: " << string(buffer) << " (sprinted)" << endl;
	printf("pi: %s (sprinted)\n", buffer);

	char buf[512];
    sprintf(buf, "%-*s %-*s", 19, "SYS", 11, "SYS");
    printf("buf: [%s]\n", buf);
}