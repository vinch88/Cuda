#include "Indice2D.h"
#include "cudaTools.h"
#include "Device.h"

#include "Sphere.h"
#include "math/RayTracingMath.h"
#include "IndiceTools_GPU.h"
#include "../../provider/nbSphere.h"
#include "RayTracingMath.h"

using namespace gpu;

__constant__ Sphere TAB_CM[NB_SPHERE];

static __device__ void rayTracing(uchar4* ptrDevPixels, uint w, uint h, float t, Sphere* ptrDevTabSphere);
static __device__ void copyGMtoSM(Sphere* ptrDevTabSphere, Sphere* tab_SM);


__host__ void uploadGPU(Sphere* tabValue)
    {
    size_t size = NB_SPHERE * sizeof(Sphere);
    int offset = 0;
    HANDLE_ERROR(cudaMemcpyToSymbol(TAB_CM, tabValue, size, offset, cudaMemcpyHostToDevice));
    }

__device__ void copyGMtoSM(Sphere* ptrDevTabSphere, Sphere* tab_SM)
    {
    const int TID_LOCAL = Indice2D::tidLocal();
    const int NB_THREAD_LOCAL = Indice2D::nbThreadLocal();

    int s = TID_LOCAL;
    while (s < NB_SPHERE)
	{
	tab_SM[s] = ptrDevTabSphere[s];
	s += NB_THREAD_LOCAL;
	}
    }

__global__ void CM(uchar4* ptrDevPixels, uint w, uint h, float t)
    {
    rayTracing(ptrDevPixels, w, h, t, TAB_CM);
    }

__global__ void GM(uchar4* ptrDevPixels, uint w, uint h, float t, Sphere* ptrDevTabSphere)
    {
    rayTracing(ptrDevPixels, w, h, t, ptrDevTabSphere);
    }

__global__ void SM(uchar4* ptrDevPixels, uint w, uint h, float t, Sphere* ptrDevTabSphere)
    {
    extern __shared__ Sphere tab_SM[];
    copyGMtoSM(ptrDevTabSphere, tab_SM);
    __syncthreads();
    rayTracing(ptrDevPixels, w, h, t, tab_SM);
    }

__device__ void rayTracing(uchar4* ptrDevPixels, uint w, uint h, float t, Sphere* ptrDevTabSphere)
    {
    RaytracingMath raytracingMath = RaytracingMath(t, NB_SPHERE, ptrDevTabSphere);

    const int TID = Indice2D::tid();
    const int NB_THREAD = Indice2D::nbThread();
    const int WH = w * h;

    int i;
    int j;

    int s = TID;
    while (s < WH)
	{
	IndiceTools::toIJ(s, w, &i, &j);

	raytracingMath.colorIJ(&ptrDevPixels[s], (float) i, (float) j);

	s += NB_THREAD;
	}
    }

