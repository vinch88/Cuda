#pragma once

#include <math.h>
#include "MathTools.h"

#include "ColorTools_GPU.h"
using namespace gpu;

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

class RipplingMath
    {
	/*--------------------------------------*\
	|*		Constructor		*|
	 \*-------------------------------------*/

    public:

	__device__ RipplingMath(int w, int h)
	    {
	    this->dim2 = w / 2.0f;
	    }

	// constructeur copie automatique car pas pointeur dans VagueMath

	__device__
	   virtual ~RipplingMath()
	    {
	    // rien
	    }

	/*--------------------------------------*\
	|*		Methodes		*|
	 \*-------------------------------------*/

    public:

	__device__
	void colorIJ(uchar4* ptrColor, int i, int j, float t)
	    {
	    uchar levelGris;

	    f(&levelGris, i, j, t); // update levelGris

	    ptrColor->x = levelGris;
	    ptrColor->y = levelGris;
	    ptrColor->z = levelGris;

	    ptrColor->w = 255; // opaque
	    }

    private:

	__device__
	void f(uchar* ptrLevelGris, int i, int j, float t)
	    {
		float result;
		result = dij(i, j);
		*ptrLevelGris = 128.0f+127.0f*(cosf(result/10.0f - t/7)/(result/10.0f+1.0f));
	    }

	__device__
	float  dij(int i, int j)
	    {
		float fi = i - (float)dim2;
		float fj = j - (float)dim2;
		return sqrtf(fi*fi+fj*fj);
	    }

	/*--------------------------------------*\
	|*		Attributs		*|
	 \*-------------------------------------*/

    private:

	// Tools
	float dim2;

    };

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
