#include <iostream>
#include <stdlib.h>

#include "MandelbrotProvider.h"
#include "RipplingProvider.h"
#include "Animateur_GPU.h"
#include "Settings_GPU.h"

#include "03_Raytracing/provider/RaytracingProvider.h"
using namespace gpu;

using std::cout;
using std::endl;

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Imported	 	*|
 \*-------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

int mainAnimable(Settings& settings);

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

static void rippling();
static void mandelbrot();
static void raytracing();

// Tools
template<typename T>
static void animer(Provider_I<T>* ptrProvider, int nbIteration);

/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

int mainAnimable(Settings& settings)
    {
    cout << "\n[Animable] mode" << endl;

    // Attention : pas tous a la fois

    //rippling();
    mandelbrot();
    //raytracing();

    cout << "\n[Animable] end" << endl;

    return EXIT_SUCCESS;
    }

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

void rippling()
    {
    const int NB_ITERATION = 1000;

    RipplingProvider provider;
    animer<uchar4>(&provider,NB_ITERATION);
    }

void mandelbrot()
    {
    const int NB_ITERATION = 1000;

    MandelbrotProvider provider;
    animer<uchar4>(&provider,NB_ITERATION);
    }

void raytracing()
    {
    const int NB_ITERATION = 1000;

    RayTracingProvider provider;
    animer<uchar4>(&provider,NB_ITERATION);
    }

/*-----------------------------------*\
 |*		Tools	        	*|
 \*-----------------------------------*/

template<typename T>
void animer(Provider_I<T>* ptrProvider, int nbIteration)
    {
    Animateur<T> animateur(ptrProvider, nbIteration);
    animateur.run();
    }

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

