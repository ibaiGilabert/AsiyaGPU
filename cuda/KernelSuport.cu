#ifndef _KERNEL_SUPPORT_
#define _KERNEL_SUPPORT_

#include <iostream>
#include "MyKernel.h"

int main( int argc, char** argv)
{
    const int N = 16;

    int hostArray[N];
    int *deviceArray;

    std::cout << "Before device\n";
    for(int i = 0; i < N; i++) {
        hostArray[i] = i + 1;
        std::cout << hostArray[i] << "\n";
    }
    std::cout << "\n";

    cudaMalloc((void**) &deviceArray, N*sizeof(int));

    cudaMemcpy(deviceArray, hostArray, N*sizeof(int), cudaMemcpyHostToDevice);
    TestDevice <<< 4, 4 >>> (deviceArray);
    cudaMemcpy(hostArray, deviceArray, N*sizeof(int), cudaMemcpyDeviceToHost);

    cudaFree(deviceArray);

    std::cout << "After device\n";
    for(int i = 0; i < N; i++) std::cout << hostArray[i] << "\n";

    std::cout << "Done\n";
}

#endif