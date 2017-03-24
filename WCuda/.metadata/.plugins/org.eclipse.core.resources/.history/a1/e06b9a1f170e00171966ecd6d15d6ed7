#include <iostream>
#include <assert.h>

#include "Device.h"
#include <assert.h>
#include "RayTracing.h"

using std::cout;
using std::endl;


extern __global__ void rayTracing(uchar4* ptrDevPixels,uint w, uint h,float t,uint nbSphere, Sphere* ptrDevTabSphere);



RayTracing::RayTracing(uint nbSphere, const Grid& grid, uint w, uint h, float dt) :
	Animable_I<uchar4>(grid, w, h, "RayTracing_Cuda_RGBA_uchar4")
    {

    // Inputs
    this->dt = dt;
    this->nbSphere = nbSphere;

    this->sizeOctet = nbSphere * sizeof(Sphere);

    printf("coucou");
    SphereCreator sphereCreator(nbSphere,w,h,100);
    Sphere* ptrTabSphere = sphereCreator.getTabSphere();

    // Tools
    this->t = 0;

    this->dg = grid.dg;
    this->db = grid.db;

    Device::malloc(&ptrDevTabSphere, sizeOctet);
    Device::memclear(ptrDevTabSphere, sizeOctet);
    Device::memcpyHToD(ptrDevTabSphere, ptrTabSphere, sizeOctet);
    //Device::lastCudaError("TabSphere MM (end allocation)"); // temp debug, facultatif


    }

RayTracing::~RayTracing()
    {
    //delete this->ptrTabSphere;
    Device::free(ptrDevTabSphere);
    //Device::lastCudaError("TabSphere MM (end deallocation)"); // temp debug, facultatif
    }



void RayTracing::process(uchar4* ptrDevPixels, uint w, uint h, const DomaineMath& domaineMath)
    {

    //Device::lastCudaError("rayTracing (before kernel)"); // facultatif, for debug only, remove for release
    rayTracing<<<dg,db>>>(ptrDevPixels,w,h,t,nbSphere,ptrDevTabSphere);
    //Device::lastCudaError("rayTracing (after kernel)"); // facultatif, for debug only, remove for release

    //Device::synchronize();



    }


void RayTracing::animationStep()
    {
    t += dt;
    }


