#include "Indice2D.h"
#include "cudaTools.h"
#include "Device.h"

#include "math/MandelbrotMath.h"
#include "DomaineMath_GPU.h"
#include "IndiceTools_GPU.h"
using namespace gpu;

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/
__global__ void mandelbrot(uchar4* ptrDevPixels, uint w, uint h, uint t, DomaineMath domaineMath)
    {
    MandelbrotMath mandelbrotMath = MandelbrotMath(t);

    const int WH=w*h;
    const int TID = Indice2D::tid();
    const int NB_THREAD = Indice2D::nbThread();

    int i = 0;
    int j = 0;

    double x = 0;
    double y = 0;

    int s = TID;
    while (s < WH)
	{
	IndiceTools::toIJ(s, w, &i, &j);

	domaineMath.toXY(i, j, &x, &y);

	mandelbrotMath.colorXY(&ptrDevPixels[s],x, y);
	s += NB_THREAD;
	}
    }


/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

