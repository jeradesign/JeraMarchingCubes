//
// Created by John Brewer on 10/14/19.
//

#ifndef JERAMARCHINGCUBES_MARCHINGSOURCE_H
#define JERAMARCHINGCUBES_MARCHINGSOURCE_H

struct Vector
{
    float fX;
    float fY;
    float fZ;
};

extern int     iDataSetSize;
extern float   fStepSize;
extern float   fTargetValue;
extern float   fTime;
extern Vector  sSourcePoint[3];

extern float fSample1(float fX, float fY, float fZ);
extern float fSample2(float fX, float fY, float fZ);
extern float fSample3(float fX, float fY, float fZ);
extern float (*fSample)(float fX, float fY, float fZ);

extern void vMarchingCubes();
extern void vMarchCube1(float fX, float fY, float fZ, float fScale);
extern void vMarchCube2(float fX, float fY, float fZ, float fScale);
extern void (*vMarchCube)(float fX, float fY, float fZ, float fScale);

#endif //JERAMARCHINGCUBES_MARCHINGSOURCE_H
