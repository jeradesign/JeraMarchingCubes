//
// Marching Cubes Example Program
// by Cory Bloyd (corysama@yahoo.com)
//
// A simple, portable and complete implementation of the Marching Cubes
// and Marching Tetrahedrons algorithms in a single source file.
// There are many ways that this code could be made faster, but the
// intent is for the code to be easy to understand.
//
// For a description of the algorithm go to
// http://astronomy.swin.edu.au/pbourke/modelling/polygonise/
//
// This code is public domain.
//

#include "stdio.h"
#include "math.h"
//This program requires the OpenGL and GLUT libraries
// You can obtain them for free from http://www.opengl.org
#include "GLUT/glut.h"

#include "marchingsource.h"

static const GLfloat afAmbientWhite [] = {0.25, 0.25, 0.25, 1.00};
static const GLfloat afAmbientRed   [] = {0.25, 0.00, 0.00, 1.00};
static const GLfloat afAmbientGreen [] = {0.00, 0.25, 0.00, 1.00};
static const GLfloat afAmbientBlue  [] = {0.00, 0.00, 0.25, 1.00};
static const GLfloat afDiffuseWhite [] = {0.75, 0.75, 0.75, 1.00};
static const GLfloat afDiffuseRed   [] = {0.75, 0.00, 0.00, 1.00};
static const GLfloat afDiffuseGreen [] = {0.00, 0.75, 0.00, 1.00};
static const GLfloat afDiffuseBlue  [] = {0.00, 0.00, 0.75, 1.00};
static const GLfloat afSpecularWhite[] = {1.00, 1.00, 1.00, 1.00};
static const GLfloat afSpecularRed  [] = {1.00, 0.25, 0.25, 1.00};
static const GLfloat afSpecularGreen[] = {0.25, 1.00, 0.25, 1.00};
static const GLfloat afSpecularBlue [] = {0.25, 0.25, 1.00, 1.00};


GLenum    ePolygonMode = GL_FILL;
GLboolean bSpin = true;
GLboolean bMove = true;
GLboolean bLight = true;

void vIdle();
void vDrawScene();
void vResize(GLsizei, GLsizei);
void vKeyboard(unsigned char cKey, int iX, int iY);
void vSpecial(int iKey, int iX, int iY);

GLvoid vPrintHelp();
GLvoid vSetTime(GLfloat fTime);

int main(int argc, char **argv)
{
    GLfloat afPropertiesAmbient [] = {0.50, 0.50, 0.50, 1.00};
    GLfloat afPropertiesDiffuse [] = {0.75, 0.75, 0.75, 1.00};
    GLfloat afPropertiesSpecular[] = {1.00, 1.00, 1.00, 1.00};

    GLsizei iWidth = 640.0;
    GLsizei iHeight = 480.0;

    glutInit(&argc, argv);
    glutInitWindowPosition( 0, 0);
    glutInitWindowSize(iWidth, iHeight);
    glutInitDisplayMode( GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE );
    glutCreateWindow( "Marching Cubes" );
    glutDisplayFunc( vDrawScene );
    glutIdleFunc( vIdle );
    glutReshapeFunc( vResize );
    glutKeyboardFunc( vKeyboard );
    glutSpecialFunc( vSpecial );

    glClearColor( 0.0, 0.0, 0.0, 1.0 );
    glClearDepth( 1.0 );

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glPolygonMode(GL_FRONT_AND_BACK, ePolygonMode);

    glLightfv( GL_LIGHT0, GL_AMBIENT,  afPropertiesAmbient);
    glLightfv( GL_LIGHT0, GL_DIFFUSE,  afPropertiesDiffuse);
    glLightfv( GL_LIGHT0, GL_SPECULAR, afPropertiesSpecular);
    glLightModelf(GL_LIGHT_MODEL_TWO_SIDE, 1.0);

    glEnable( GL_LIGHT0 );

    glMaterialfv(GL_BACK,  GL_AMBIENT,   afAmbientGreen);
    glMaterialfv(GL_BACK,  GL_DIFFUSE,   afDiffuseGreen);
    glMaterialfv(GL_FRONT, GL_AMBIENT,   afAmbientBlue);
    glMaterialfv(GL_FRONT, GL_DIFFUSE,   afDiffuseBlue);
    glMaterialfv(GL_FRONT, GL_SPECULAR,  afSpecularWhite);
    glMaterialf( GL_FRONT, GL_SHININESS, 25.0);

    vResize(iWidth, iHeight);

    vPrintHelp();
    glutMainLoop();

    return 0;
}

GLvoid vPrintHelp()
{
    printf("Marching Cubes Example by Cory Bloyd (dejaspaminacan@my-deja.com)\n\n");

    printf("+/-  increase/decrease sample density\n");
    printf("PageUp/PageDown  increase/decrease surface value\n");
    printf("s  change sample function\n");
    printf("c  toggle marching cubes / marching tetrahedrons\n");
    printf("w  wireframe on/off\n");
    printf("l  toggle lighting / color-by-normal\n");
    printf("Home  spin scene on/off\n");
    printf("End  source point animation on/off\n");
}


void vResize( GLsizei iWidth, GLsizei iHeight )
{
    GLfloat fAspect, fHalfWorldSize = (1.4142135623730950488016887242097/2);

    glViewport( 0, 0, iWidth, iHeight );
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity ();

    if(iWidth <= iHeight)
    {
        fAspect = (GLfloat)iHeight / (GLfloat)iWidth;
        glOrtho(-fHalfWorldSize, fHalfWorldSize, -fHalfWorldSize*fAspect,
                fHalfWorldSize*fAspect, -10*fHalfWorldSize, 10*fHalfWorldSize);
    }
    else
    {
        fAspect = (GLfloat)iWidth / (GLfloat)iHeight;
        glOrtho(-fHalfWorldSize*fAspect, fHalfWorldSize*fAspect, -fHalfWorldSize,
                fHalfWorldSize, -10*fHalfWorldSize, 10*fHalfWorldSize);
    }

    glMatrixMode( GL_MODELVIEW );
}

void vKeyboard(unsigned char cKey, int iX, int iY)
{
    switch(cKey)
    {
        case 'w' :
        {
            if(ePolygonMode == GL_LINE)
            {
                ePolygonMode = GL_FILL;
            }
            else
            {
                ePolygonMode = GL_LINE;
            }
            glPolygonMode(GL_FRONT_AND_BACK, ePolygonMode);
        } break;
        case '+' :
        case '=' :
        {
            ++iDataSetSize;
            fStepSize = 1.0/iDataSetSize;
        } break;
        case '-' :
        {
            if(iDataSetSize > 1)
            {
                --iDataSetSize;
                fStepSize = 1.0/iDataSetSize;
            }
        } break;
        case 'c' :
        {
            if(vMarchCube == vMarchCube1)
            {
                vMarchCube = vMarchCube2;//Use Marching Tetrahedrons
            }
            else
            {
                vMarchCube = vMarchCube1;//Use Marching Cubes
            }
        } break;
        case 's' :
        {
            if(fSample == fSample1)
            {
                fSample = fSample2;
            }
            else if(fSample == fSample2)
            {
                fSample = fSample3;
            }
            else
            {
                fSample = fSample1;
            }
        } break;
        case 'l' :
        {
            if(bLight)
            {
                glDisable(GL_LIGHTING);//use vertex colors
            }
            else
            {
                glEnable(GL_LIGHTING);//use lit material color
            }

            bLight = !bLight;
        };
    }
}


void vSpecial(int iKey, int iX, int iY)
{
    switch(iKey)
    {
        case GLUT_KEY_PAGE_UP :
        {
            if(fTargetValue < 1000.0)
            {
                fTargetValue *= 1.1;
            }
        } break;
        case GLUT_KEY_PAGE_DOWN :
        {
            if(fTargetValue > 1.0)
            {
                fTargetValue /= 1.1;
            }
        } break;
        case GLUT_KEY_HOME :
        {
            bSpin = !bSpin;
        } break;
        case GLUT_KEY_END :
        {
            bMove = !bMove;
        } break;
    }
}

void vIdle()
{
    glutPostRedisplay();
}

void vDrawScene()
{
    static GLfloat fPitch = 0.0;
    static GLfloat fYaw   = 0.0;
    static GLfloat fTime = 0.0;

    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    glPushMatrix();

    if(bSpin)
    {
        fPitch += 4.0;
        fYaw   += 2.5;
    }
    if(bMove)
    {
        fTime  += 0.025;
    }

    vSetTime(fTime);

    glTranslatef(0.0, 0.0, -1.0);
    glRotatef( -fPitch, 1.0, 0.0, 0.0);
    glRotatef(     0.0, 0.0, 1.0, 0.0);
    glRotatef(    fYaw, 0.0, 0.0, 1.0);

    glPushAttrib(GL_LIGHTING_BIT);
    glDisable(GL_LIGHTING);
    glColor3f(1.0, 1.0, 1.0);
    glutWireCube(1.0);
    glPopAttrib();


    glPushMatrix();
    glTranslatef(-0.5, -0.5, -0.5);
    glBegin(GL_TRIANGLES);
    glColor3f(afDiffuseBlue[0], afDiffuseBlue[1], afDiffuseBlue[2]);
    std::vector<Vector> vertices;
    std::vector<Vector> normals;
    vMarchingCubes(vertices, normals);
    for (unsigned long i = 0; i < vertices.size(); ++i) {
        glNormal3f(normals[i].fX, normals[i].fY, normals[i].fZ);
        glVertex3f(vertices[i].fX, vertices[i].fY, vertices[i].fZ);
    }
    glEnd();
    glPopMatrix();


    glPopMatrix();

    glutSwapBuffers();
}