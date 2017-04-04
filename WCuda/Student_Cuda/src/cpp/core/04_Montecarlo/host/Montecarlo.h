#pragma once

#include "cudaTools.h"
#include "Grid.h"
#include <curand_kernel.h>



class Montecarlo
    {


    public:

	Montecarlo(const Grid& grid);

	virtual ~Montecarlo(void);

	void run();

	int getResult();

    private:

	dim3 dg;
	dim3 db;
	curandState* ptrTabGen;
	int* ptrDevNxTotal;
	int nbFlecheByThread;
	size_t sizeTabSM;
	size_t sizeResultGM;
	int result;
	double piAt;

    };

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
