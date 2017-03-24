#pragma once

#include <math.h>
#include "MathTools.h"

#include "Calibreur_CPU.h"
#include "ColorTools_CPU.h"
using namespace cpu;

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

	MandelbrotMath(uint n) :
		calibreur(Interval<float>(0, n), Interval<float>(0, 1))
	    {
	    }
	// constructeur copie automatique car pas pointeur dans
	//	DamierMath
	// 	calibreur
	// 	IntervalF

	virtual ~MandelbrotMath()
	    {
	    // rien
	    }

	/*--------------------------------------*\
	|*		Methodes		*|
	 \*-------------------------------------*/

    public:

	void colorXY(uchar4* ptrColor, float x, float y, float t)
	    {
	    float z = f(x, y, t);

	    if (z < t)
		{

		float hue01 = z;
		calibreur.calibrer(z);
		ColorTools::HSB_TO_RVB(hue01, ptrColor); // update color

		ptrColor->w = 255; // opaque

		}
	    else
		{
		ptrColor->x = 0;
		ptrColor->y = 0;
		ptrColor->z = 0;
		}

	    }

    private:

	int f(float x, float y, float t)
	    {
	    float a = 0;
	    float b = 0;
	    float aCopy = 0;
	    int k = 0;
	    do
		{
		aCopy = a;
		a = (a * a - b * b) + x;
		b = 2 * aCopy * b + y;
		k++;
		}
	    while (a * a + b * b > 4 || k > t);
	    return k;
	    }

	/*--------------------------------------*\
	|*		Attributs		*|
	 \*-------------------------------------*/

    private:

	// Tools
	Calibreur<float> calibreur;

    };

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
