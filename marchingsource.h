//
// Created by John Brewer on 10/14/19.
//

#ifndef JERAMARCHINGCUBES_MARCHINGSOURCE_H
#define JERAMARCHINGCUBES_MARCHINGSOURCE_H

#include <OpenGL/OpenGL.h>

struct GLvector
{
    GLfloat fX;
    GLfloat fY;
    GLfloat fZ;
};

extern GLint     iDataSetSize;
extern GLfloat   fStepSize;
extern GLfloat   fTargetValue;
extern GLfloat   fTime;
extern GLvector  sSourcePoint[3];

extern GLfloat fSample1(GLfloat fX, GLfloat fY, GLfloat fZ);
extern GLfloat fSample2(GLfloat fX, GLfloat fY, GLfloat fZ);
extern GLfloat fSample3(GLfloat fX, GLfloat fY, GLfloat fZ);
extern GLfloat (*fSample)(GLfloat fX, GLfloat fY, GLfloat fZ);

extern GLvoid vMarchingCubes();
extern GLvoid vMarchCube1(GLfloat fX, GLfloat fY, GLfloat fZ, GLfloat fScale);
extern GLvoid vMarchCube2(GLfloat fX, GLfloat fY, GLfloat fZ, GLfloat fScale);
extern GLvoid (*vMarchCube)(GLfloat fX, GLfloat fY, GLfloat fZ, GLfloat fScale);

#endif //JERAMARCHINGCUBES_MARCHINGSOURCE_H
