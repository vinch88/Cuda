#include "SphereCreator.h"
#include "AleaTools.h"
#include <stdio.h>

SphereCreator::SphereCreator(int nbSpheres, int w, int h, int bord)
    {

    this->nbSpheres = nbSpheres;
    this->w = w;
    this->h = h;
    this->bord = bord;

    this->tabSphere = new Sphere[nbSpheres];

    createSphere();
    }

SphereCreator::~SphereCreator()
    {
    delete[] tabSphere;
    }

Sphere* SphereCreator::getTabSphere()
    {
    return tabSphere;
    }

void SphereCreator::createSphere(void)
    {
    AleaTools aleaTools = AleaTools();
    for (int i = 0; i < nbSpheres; i++)
	{
	float3 centre;
	centre.x = aleaTools.uniformeAB(0 + bord, h - bord);
	centre.y = aleaTools.uniformeAB(0 + bord, w - bord);
	centre.z = aleaTools.uniformeAB(10, 2 * w);
	float rayon = aleaTools.uniformeAB(20, w / 10);
	float hue01 = aleaTools.uniforme01();
	//printf("centre : %f %f %f",centre.x,centre.y,centre.z);
	//printf("rayon : %f ",rayon);
	tabSphere[i] = Sphere(centre, rayon, hue01);
// Warning : sphere stack copier dans sphere heap, // ok car pas ptr dans Sphere }
	}
    }
