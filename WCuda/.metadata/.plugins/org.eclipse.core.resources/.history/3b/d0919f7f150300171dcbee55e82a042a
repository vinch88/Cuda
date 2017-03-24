#pragma once

#include <math.h>
#include "MathTools.h"

#include "Calibreur_CPU.h"
#include "ColorTools_CPU.h"
using namespace cpu;


class FractaleMath
    {

    public:

	FractaleMath(uint n);

	virtual ~FractaleMath();

	virtual int f(float x, float y ) = 0;

   	void colorXY(uchar4* ptrColor, float x, float y);

   	bool isStop(float a, float n);

   	void setN(int n);

   	uint n;

   	Calibreur<float>* calibreur;
    };


