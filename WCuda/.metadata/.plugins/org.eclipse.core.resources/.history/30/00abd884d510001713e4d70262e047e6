#include <iostream>
#include <assert.h>

#include "Device.h"
#include <assert.h>
#include "RayTracing.h"

#include "../../provider/nbSphere.h"

using std::cout;
using std::endl;


extern __global__ void CM(uchar4* ptrDevPixels, uint w, uint h, float t);
extern __global__ void GM(uchar4* ptrDevPixels, uint w, uint h, float t, Sphere* ptrDevTabSphere);
extern __global__ void SM(uchar4* ptrDevPixels, uint w, uint h, float t, Sphere* ptrDevTabSphere);
extern __host__ void uploadGPU(Sphere* tabValue);


RayTracing::RayTracing( const Grid& grid, uint w, uint h, float dt) :
	Animable_I<uchar4>(grid, w, h, "RayTracing_Cuda_RGBA_uchar4")
    {

    // Inputs
    this->dt = dt;

    this->sizeOctet = NB_SPHERE * sizeof(Sphere);

    SphereCreator sphereCreator(NB_SPHERE,w,h,100);
    Sphere* ptrTabSphere = sphereCreator.getTabSphere();

    // Tools
    this->t = 0;
    this->i = 0;

    this->dg = grid.dg;
    this->db = grid.db;

    Device::malloc(&ptrDevTabSphere, sizeOctet);
    Device::memclear(ptrDevTabSphere, sizeOctet);
    Device::memcpyHToD(ptrDevTabSphere, ptrTabSphere, sizeOctet);
    //Device::lastCudaError("TabSphere MM (end allocation)"); // temp debug, facultatif
    uploadGPU(ptrTabSphere);

    }

RayTracing::~RayTracing()
    {
    Device::free(ptrDevTabSphere);
    }



void RayTracing::process(uchar4* ptrDevPixels, uint w, uint h, const DomaineMath& domaineMath)
    {
//    i++;
//    if(i%3 == 0){
//	 CM<<<dg,db>>>(ptrDevPixels,w,h,t);
//    }else if(i%3 == 1){
//	 GM<<<dg,db>>>(ptrDevPixels,w,h,t,ptrDevTabSphere);
//    }else if(i%3 == 2){
	 SM<<<dg,db,sizeOctet>>>(ptrDevPixels,w,h,t,ptrDevTabSphere);
    //}
    }


void RayTracing::animationStep()
    {
    t += dt;
    }


