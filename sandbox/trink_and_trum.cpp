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

    char buff[128];

    int c_file = 1;
    string basename =  "dir/source";
    for (int i = 1; i <= 5; ++i, ++c_file) {
    	sprintf(buff, "%s%s%.3d", basename.c_str(), ".txt.", c_file);
		printf("%s\n", buff);
	}
}