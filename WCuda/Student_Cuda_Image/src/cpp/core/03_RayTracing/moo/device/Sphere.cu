#include "Indice2D.h"
#include "cudaTools.h"
#include "Device.h"
#include "IndiceTools_GPU.h"

#include "Sphere.h"
using namespace gpu;


/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Imported	 	*|
 \*-------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

__global__ void vague(uchar4* ptrDevPixels, uint w, uint h, float t);

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

__global__ void vague(uchar4* ptrDevPixels, uint w, uint h, float t)
    {
    VagueMath vagueMath = VagueMath(w, h);

    const int WH = w * h;
    const int TID = Indice2D::tid();
    const int NB_THREAD = Indice2D::nbThread();

    int i;	// in [0,h[
    int j; 	// in [0,w[

    int s = TID;  // in [0,...
    while (s < WH)
	{
	IndiceTools::toIJ(s, w, &i, &j); 	// update (i, j)

	vagueMath.colorIJ(&ptrDevPixels[s], i, j, t); 	// update ptrDevPixels[s]

	s += NB_THREAD;
	}
    }

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

