#ifndef SPHERE_H
#define SPHERE_H

#include <stdio.h>
#include "cudaTools.h"
#include "MathTools.h"


class Sphere
    {

    public:

	__host__
	Sphere(float3 centre, float rayon, float hue)
	    {
	    this->centre = centre;
	    this->r = rayon;
	    this->hueStart = hue;

	    this->rCarre = rayon * rayon;
	    }

	__host__
	Sphere()
	    {

	    }

	__device__
	float hCarre(float x, float y)
	    {
	    float a = (centre.x - x);
	    float b = (centre.y - y);
	    return a * a + b * b;
	    }

	__device__
	bool isEnDessous(float hCarre)
	    {
	    return hCarre < rCarre;
	    }

	__device__
	float dz(float hCarre)
	    {
	    return sqrtf(rCarre - hCarre);
	    }

	__device__
	float brightness(float dz)
	    {
	    return dz / r;
	    }

	__device__
	float distance(float dz)
	    {
	    return centre.z - dz;
	    }

	__device__
	float getHueStart()
	    {
	    return hueStart;
	    }

	__device__
	float hue(float t)
	    {
	    return 0.5f + 0.5f * sinf(t + hueStart + 3.0f * PI_FLOAT / 2.0f);
	    }

    public :
	// Inputs
	float r;
	float3 centre;
	float hueStart;
	// Tools
	float rCarre;

	};
#endif
