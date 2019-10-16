//
// Created by John Brewer on 10/14/19.
//

#ifndef JERAMARCHINGCUBES_MARCHINGSOURCE_H
#define JERAMARCHINGCUBES_MARCHINGSOURCE_H

#include <vector>

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

extern uint16_t* voxelData;

extern float fSample1(float fX, float fY, float fZ);
extern float fSample2(float fX, float fY, float fZ);
extern float fSample3(float fX, float fY, float fZ);
extern float fSample4(float fX, float fY, float fZ);
extern float (*fSample)(float fX, float fY, float fZ);

extern void vMarchingCubes(std::vector<Vector>& vertices, std::vector<Vector>& normals);
extern void vMarchCube1(float fX, float fY, float fZ, float fScale,
    std::vector<Vector>& vertices, std::vector<Vector>& normals);
extern void vMarchCube2(float fX, float fY, float fZ, float fScale,
    std::vector<Vector>& vertices, std::vector<Vector>& normals);
extern void (*vMarchCube)(float fX, float fY, float fZ, float fScale,
    std::vector<Vector>& vertices, std::vector<Vector>& normals);

#endif //JERAMARCHINGCUBES_MARCHINGSOURCE_H
