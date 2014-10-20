#include "stdio.h"
#include <vector>

#define N 100000

using namespace std;

void add(const vector<int> &a, const vector<int> &b, vector<int> &c) {
	for(int i = 0; i < N; ++i)
		c[i] = a[i] + b[i];
}

int main() {
	vector<int> a(N), b(N), c(N);

	for (int i = 0; i < N; ++i) {
		a[i] = i;
		b[i] = i;
	}
	add(a, b, c);

	/*for(int i = 0; i < N; ++i) {
		printf("%d + %d = %d\n", a[i], b[i], c[i]);
	}*/
}