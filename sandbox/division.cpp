#include <iostream>
#include <math.h>
using namespace std;

int main() {
	double a, b;
	while (cin >> a >> b) {
		cout << "divisio entera:\t" << a/b << endl;
		cout << "enter superior:\t" << floor(a/b) << endl;
		cout << "enter inferior:\t" << ceil(a/b) << endl;
	}
}