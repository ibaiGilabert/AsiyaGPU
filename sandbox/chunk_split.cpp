#include <iostream>
#include <math.h>
using namespace std;


int main() {
	int num_proc;
	double n_segs;
	cout << "Please, introduce n_segs and num_proc" << endl;
	cin >> n_segs >> num_proc;
	int chunk = n_segs/num_proc + (ceil(n_segs/num_proc) - floor(n_segs/num_proc));
	cout << "chunk: " << chunk << "\t[ " << n_segs/num_proc << " + (" << ceil(n_segs/num_proc) << " - " << floor(n_segs/num_proc) << ") ]" << endl;
}
