#include <iostream>
#include <math.h>
using namespace std;

int main() {
	/*double a, b;
	while (cin >> a >> b) {
		cout << "divisio entera:\t" << a/b << endl;
		cout << "enter superior:\t" << floor(a/b) << endl;
		cout << "enter inferior:\t" << ceil(a/b) << endl;
	}*/
	double a = 33;
	int b = 4;
	cout << "a = " << a << endl;
	cout << "b = " << b << endl;
	cout << "a/b = " << a/b << endl;
	cout << "ceil(a/b): " << ceil(a/b) << endl;
	cout << "floor(a/b): " << floor(a/b) << endl;
	cout << "ceil - floor: " << ceil(a/b) - floor(a/b) << endl;
	cout << "a/b + (ceil-floor): " << a/b + (ceil(a/b) - floor(a/b)) << endl;
	int chunk = a/b + (ceil(a/b) - floor(a/b));
	cout << "chunk (same above (int)): " << chunk << endl;

	double c = 2;
	int d = 2;
	cout << "ceil(c/d): " << ceil(c/d) << endl;
	cout << "floor(c/d): " << floor(c/d) << endl;
	cout << "ceil - floor: " << ceil(c/d) - floor(c/d) << endl;
	cout << "c/d + (ceil-floor): " << c/d + (ceil(c/d) - floor(c/d)) << endl;
	int chunk_cd = c/d + (ceil(c/d) - floor(c/d));
	cout << "chunk (same above (int)): " << chunk_cd << endl;

}