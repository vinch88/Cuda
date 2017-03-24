#pragma once

#include <math.h>
#include "MathTools.h"
#include "Sphere.h"
#include <stdio.h>

#include "ColorTools_GPU.h"
using namespace gpu;

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

class RaytracingMath
    {
	/*--------------------------------------*\
	|*		Constructor		*|
	 \*-------------------------------------*/

    public:

	__device__ RaytracingMath(float t, int nbSphere, Sphere* ptrDevTabSphere)
	    {
	    this->t = t;
	    this->nbSphere = nbSphere;
	    this->ptrDevTabSphere = ptrDevTabSphere;
	    }

	__device__
	     virtual ~RaytracingMath()
	    {
	    // rien
	    }

	/*--------------------------------------*\
	|*		Methodes		*|
	 \*-------------------------------------*/

    public:

	__device__
	void colorIJ(uchar4* ptrColor, float i, float j)
	    {

	    float min = 10000.0f;
	    float hueMin = -1000.0f;
	    float brightnessMin = -1000.0f;

	    for (uint index = 0; index < nbSphere; index++)
		{
		Sphere sphere = ptrDevTabSphere[index];
		float hCarre = sphere.hCarre(i,j);

		if (sphere.isEnDessous(hCarre))
		    {
		    float dz = sphere.dz(hCarre);
		    float distance = sphere.distance(dz);

		    if (distance < min)
			{
			min = distance;
			hueMin = sphere.hue(t);
			brightnessMin = sphere.brightness(dz);
			}
		    }
		}

	    if (hueMin >= 0)
		{
		ColorTools::HSB_TO_RVB(hueMin, 1.f, brightnessMin, ptrColor);
		}
	    else
		{
		ptrColor->x = 0;
		ptrColor->y = 0;
		ptrColor->z = 0;
		}
	    }

    private:

	/*--------------------------------------*\
	|*		Attributs		*|
	 \*-------------------------------------*/

    private:

	// Tools
	float t;
	int nbSphere;
	Sphere* ptrDevTabSphere;

    };

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
