#include "stdio.h"

#include <iostream>
#include <vector>

#include <thrust/host_vector.h>
#include <thrust/device_vector.h>
#include <thrust/transform.h>
#include <thrust/functional.h>

using namespace std;

#define N 10


/*__global__ void add(int &a, int &b, int &c) {
	int tId = blockIdx.x*blockDim.x + threadIdx.x;
	if (tId < N)
		c[tId] = a[tId] + b[tId];
}*/

int main() {
	thrust::host_vector<float> A(N);
	thrust::host_vector<float> B(N);
	for(int i = 0; i < N; ++i) {
		A[i] = i;
		B[i] = i;
	}
	thrust::device_vector<float> dA = A;
	thrust::device_vector<float> dB = B;
	thrust::device_vector<float> C(N);

	thrust::transform(dA.begin(), dA.end()),
					  dB.begin(),
					  C.begin(),
					  thrust::plus<float>());
}