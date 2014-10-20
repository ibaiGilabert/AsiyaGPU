 #include "stdio.h"


__global__ void add(int a, int b, int *c) {
	*c = a + b;
}

int main() {
	int a = 3;
	int b = 4;
	int c, *dev_c;

	cudaMalloc((void**)&dev_c, sizeof(int));
	add<<<1,1>>>(a, b, dev_c);
	cudaMemcpy(&c, dev_c, sizeof(int), cudaMemcpyDeviceToHost);
	cudaFree(dev_c);

	printf("%d + %d = %d\n", a, b, c);
}