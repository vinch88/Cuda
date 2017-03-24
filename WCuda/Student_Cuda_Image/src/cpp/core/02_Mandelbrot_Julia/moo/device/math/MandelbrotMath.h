#pragma once

#include <math.h>
#include "MathTools.h"
#include "Device.h"

#include "ColorTools_GPU.h"
#include "Calibreur_GPU.h"
using namespace gpu;

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

class MandelbrotMath
    {

	/*--------------------------------------*\
	|*		Constructor		*|
	 \*-------------------------------------*/

    public:
	__device__
	MandelbrotMath(int n) :
		calibreur(Interval<float>(0, n), Interval<float>(0, 1))
	    {
	    this->n = n;
	    }


	__device__
	virtual ~MandelbrotMath()
	    {
	    // rien
	    }

	/*--------------------------------------*\
	|*		Methodes		*|
	 \*-------------------------------------*/

    public:
	__device__
	void colorXY(uchar4* ptrColor, float x, float y)
	    {
	    float z = f(x, y);

	    if(z != this->n){
		calibreur.calibrer(z);
		float hue01 = z;
		ColorTools::HSB_TO_RVB(hue01, ptrColor);
	    }else{
		ptrColor->x = 0;
		ptrColor->y = 0;
		ptrColor->z = 0;
	    }

	    ptrColor->w = 255; // opaque
	    }

	__device__
	int f(float x, float y)
	    {
		float a = 0;
		float b = 0;
		float copyA = 0;
		int i = 0;

		do{
		    i++;
		    copyA = a;
		    a = (a*a-b*b)+x;
		    b = 2.0f*copyA*b+y;
		}
		while( a*a+b*b < 4.0f && i < this->n );

		return i;
	    }

	/*--------------------------------------*\
	|*		Attributs		*|
	 \*-------------------------------------*/

    private:

	// Input
	uint n;

	// Tools
	Calibreur<float> calibreur;

    };

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
