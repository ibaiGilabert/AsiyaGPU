// Multiply two matrices A * B = C

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "matrixMul_kernel.cu"

// Allocates a matrix with random float entries.
void randomInit(float* data, int size)
{
   for (int i = 0; i < size; ++i)
   data[i] = rand() / (float)RAND_MAX;
}

/////////////////////////////////////////////////////////
// Program main
/////////////////////////////////////////////////////////

int main(int argc, char** argv) {
   // set seed for rand()
   srand(2006);

   // 1. allocate host memory for matrices A and B
   unsigned int size_A = WA * HA;
   unsigned int mem_size_A = sizeof(float) * size_A;
   float* h_A = (float*) malloc(mem_size_A);

   unsigned int size_B = WB * HB;
   unsigned int mem_size_B = sizeof(float) * size_B;
   float* h_B = (float*) malloc(mem_size_B);

   // 2. initialize host memory
   randomInit(h_A, size_A);
   randomInit(h_B, size_B);

   // 8. allocate device memory
   float* d_A;
   float* d_B;
   cudaMalloc((void**) &d_A, mem_size_A);
   cudaMalloc((void**) &d_B, mem_size_B);

   // 9. copy host memory to device
   cudaMemcpy(d_A, h_A, mem_size_A,
   cudaMemcpyHostToDevice);
   cudaMemcpy(d_B, h_B, mem_size_B,
   cudaMemcpyHostToDevice);

   // 4. allocate host memory for the result C
   unsigned int size_C = WC * HC;
   unsigned int mem_size_C = sizeof(float) * size_C;
   float* h_C = (float*) malloc(mem_size_C);

   // 10. allocate device memory for the result
   float* d_C;
   cudaMalloc((void**) &d_C, mem_size_C);

   // 5. perform the calculation
   // setup execution parameters
   dim3 threads(BLOCK_SIZE, BLOCK_SIZE);
   dim3 grid(WC / threads.x, HC / threads.y);

   // execute the kernel
   matrixMul<<< grid, threads >>>(d_C, d_A,
                                  d_B, WA, WB);

   // 11. copy result from device to host
   cudaMemcpy(h_C, d_C, mem_size_C,
   cudaMemcpyDeviceToHost);

   // 7. clean up memory
   free(h_A);
   free(h_B);
   free(h_C);
   cudaFree(d_A);
   cudaFree(d_B);
   cudaFree(d_C);
}


   int devID;
   cudaDeviceProp props;
   checkCudaErrors(cudaGetDevice(&devID));
   checkCudaErrors(cudaGetDeviceProperties(&props, devID));

   int block_size = (props.major < 2) ? 16 : 32;
   unsigned int uiWA, uiHA, uiWB, uiHB, uiWC, uiHC;
   uiWA = uiHA= uiWB = uiHB = uiWC = uiHC;

   // allocate host memory for matrices A and B
   unsigned int size_A = uiWA * uiHA;
   unsigned int mem_size_A = sizeof(float) * size_A;
   float* h_A = (float*)malloc(mem_size_A);
   unsigned int size_B = uiWB * uiHB;
   unsigned int mem_size_B = sizeof(float) * size_B;
   float* h_B = (float*)malloc(mem_size_B);

   // initialize host memory
   srand(2012);
   randomInit(h_A, size_A);
   randomInit(h_B, size_B);

   // allocate device memory
   float* d_A, *d_B, *d_C;
   unsigned int size_C = uiWC * uiHC;
   unsigned int mem_size_C = sizeof(float) * size_C;

   // allocate host memory for the result
   float* h_C      = (float*) malloc(mem_size_C);
   float* h_CUBLAS = (float*) malloc(mem_size_C);
   checkCudaErrors(cudaMalloc((void**) &d_A, mem_size_A));
   checkCudaErrors(cudaMalloc((void**) &d_B, mem_size_B));
   // copy host memory to device
   checkCudaErrors(cudaMemcpy(d_A, h_A, mem_size_A, cudaMemcpyHostToDevice) );
   checkCudaErrors(cudaMemcpy(d_B, h_B, mem_size_B, cudaMemcpyHostToDevice) );
   checkCudaErrors(cudaMalloc((void**) &d_C, mem_size_C));
   // setup execution parameters
   dim3 threads(block_size, block_size);
   dim3 grid(uiWC / threads.x, uiHC / threads.y);

   //Performs warmup operation using matrixMul CUDA kernel
   if (block_size 16) {
   matrixMul<16><<< grid, threads >>>(d_C, d_A, d_B, uiWA, uiWB);
   } else {
   matrixMul<32><<< grid, threads >>>(d_C, d_A, d_B, uiWA, uiWB);
   }

   cudaDeviceSynchronize();

   // clean up memory
   free(h_A);
   free(h_B);
   free(h_C);