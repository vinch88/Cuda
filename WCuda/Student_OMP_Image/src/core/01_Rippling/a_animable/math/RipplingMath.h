#pragma once

#include <math.h>
#include "MathTools.h"

#include "ColorTools_CPU.h"
using namespace cpu;

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

class RipplingMath
    {
	/*--------------------------------------*\
	|*		Constructeur		*|
	 \*-------------------------------------*/

    public:

	RipplingMath(uint w)
	    {
	    this->dim2 = w / 2;
	    }

	// constructeur copie: pas besoin car pas attribut ptr

	virtual ~RipplingMath(void)
	    {
	    // rien
	    }

	/*--------------------------------------*\
	|*		Methode			*|
	 \*-------------------------------------*/

    public:

	void colorIJ(uchar4* ptrColorIJ, int i, int j, float t)
	    {
	    uchar levelGris;

	    f(j, i, t, &levelGris);

	    ptrColorIJ->x = levelGris;
	    ptrColorIJ->y = levelGris;
	    ptrColorIJ->z = levelGris;

	    ptrColorIJ->w = 255; //opaque
	    }

    private:

	void f(int i, int j, float t, uchar* ptrlevelGris)
	    {
	    // TODO cf fonction math pdf
	    // use focntion dij ci-dessous
	    float result;
	    dij(i, j, &result);
	    *ptrlevelGris = 128 + 127 * ((cosf(result / 10.f - t / 7)) / (result / 10.f + 1));
	    }

	void dij(int i, int j, float* ptrResult)
	    {
	    //TODO cf fonction math pdf
	    *ptrResult = sqrtf((i - dim2) * (i - dim2) + (j - dim2) * (j - dim2));
	    }

	/*--------------------------------------*\
	|*		Attribut			*|
	 \*-------------------------------------*/

    private:

	// Tools
	double dim2;

    };

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
