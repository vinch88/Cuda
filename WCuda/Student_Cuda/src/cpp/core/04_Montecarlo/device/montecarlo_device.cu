
#include "Indice1D.h"
#include "cudaTools.h"
#include <stdio.h>
#include "reductionADD.h"
#include <curand_kernel.h>

static __device__ void reductionInterThread(curandState* ptrTabGen, int nbFlecheByThread);
static __device__ float f(float x);

__global__ void montecarlo(curandState* ptrTabGen, int nbFlecheByThread, int* ptrDevNxTotal)
    {
    extern __shared__ int tab_SM[];
    reductionInterThread(ptrTabGen, nbFlecheByThread);
    __syncthreads();
    reductionADD<int>(tab_SM, ptrDevNxTotal);
    }

__device__
void reductionInterThread(curandState* ptrTabGen, int nbFlecheByThread)
    {
    const int TID_LOCAL = Indice1D::tidLocal();
    const int TID_GLOBAL = Indice1D::tid();
    const int NB_THREAD = Indice1D::nbThread();

    curandState localGenerator = ptrTabGen[TID_GLOBAL];

    float xAlea;
    float yAlea;

    float sum = 0;

    for(long i = 0; i < nbFlecheByThread; i++)
	{
	xAlea = curand_uniform(&localGenerator);
	yAlea = curand_uniform(&localGenerator);

	sum += f(i);

	}

    ptrTabGen[TID_LOCAL] = localGenerator;
    }

__device__
float f(float x)
    {
    return 4.0 / (1 + x * x);
}
