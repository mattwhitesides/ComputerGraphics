/*
    DrawingAlgorithms.h - DrawingAlgorithms class implementation.
    Written by:
    Anoop Haridas
*/

#include "DrawingAlgorithms.h"
#include <math.h>
#include <stdlib.h>
#include <qgl.h>

GLfloat v[4][3]={{0.0, 0.0, 1.0}, {0.0, 0.942809, -0.33333},
      {-0.816497, -0.471405, -0.333333}, {0.816497, -0.471405, -0.333333}};

GLfloat colors[4][3] = {{1.0, 0.0, 0.0}, {0.0, 1.0, 0.0},
                        {0.0, 0.0, 1.0}, {0.0, 0.0, 0.0}};
GLfloat	rtri = 0.0;
GLfloat	rquad = 0.0;
int numDivisions = 2;

//Use OpenGL to draw a line for testing
void DrawingAlgorithms::openGLDrawLine(int xa, int ya, int xb, int yb) {
    //    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLineWidth(3);
    glColor3f(0.0f, 1.0f, 0.0f);

    glBegin(GL_LINES);

    glVertex2i((GLint) xa, (GLint) ya);
    glVertex2i((GLint) xb, (GLint) yb);

    glEnd();
}

/*<<<<<<<<<<<<<<<<<<<<<<<<<round2f>>>>>>>>>>>>>>>>>>>*/
int DrawingAlgorithms::roundf2(float f)
{
    if (f >= 0)
        return ( ((int) (f+0.5)));
    else
        return ( ((int) (f-0.5)));
}


void DrawingAlgorithms::drawCube() {
    glLoadIdentity();
    glTranslatef(0.0f,0.0f,0.0f);
    glRotatef(rquad,0.25f,0.50f,0.25f);
    glBegin(GL_QUADS);
        glColor3f(0.0f,1.0f,0.0f);
        glVertex3f( 0.5f, 0.5f,-0.5f);
        glVertex3f(-0.5f, 0.5f,-0.5f);
        glVertex3f(-0.5f, 0.5f, 0.5f);
        glVertex3f( 0.5f, 0.5f, 0.5f);
        glColor3f(1.0f,0.5f,0.0f);
        glVertex3f( 0.5f,-0.5f, 0.5f);
        glVertex3f(-0.5f,-0.5f, 0.5f);
        glVertex3f(-0.5f,-0.5f,-0.5f);
        glVertex3f( 0.5f,-0.5f,-0.5f);
        glColor3f(1.0f,0.0f,0.0f);
        glVertex3f( 0.5f, 0.5f, 0.5f);
        glVertex3f(-0.5f, 0.5f, 0.5f);
        glVertex3f(-0.5f,-0.5f, 0.5f);
        glVertex3f( 0.5f,-0.5f, 0.5f);
        glColor3f(1.0f,1.0f,0.0f);
        glVertex3f( 0.5f,-0.5f,-0.5f);
        glVertex3f(-0.5f,-0.5f,-0.5f);
        glVertex3f(-0.5f, 0.5f,-0.5f);
        glVertex3f( 0.5f, 0.5f,-0.5f);
        glColor3f(0.0f,0.0f,1.0f);
        glVertex3f(-0.5f, 0.5f, 0.5f);
        glVertex3f(-0.5f, 0.5f,-0.5f);
        glVertex3f(-0.5f,-0.5f,-0.5f);
        glVertex3f(-0.5f,-0.5f, 0.5f);
        glColor3f(1.0f,0.0f,1.0f);
        glVertex3f( 0.5f, 0.5f,-0.5f);
        glVertex3f( 0.5f, 0.5f, 0.5f);
        glVertex3f( 0.5f,-0.5f, 0.5f);
        glVertex3f( 0.5f,-0.5f,-0.5f);
    glEnd();

    rtri+=0.2f;
    rquad-=0.15f;
}

/*<<<<<<<<<<<<<<<<<<convertCoordsToString>>>>>>>>>>>>>>>*/
QString DrawingAlgorithms::convertCoordsToString(int num, int x, int y)
{
    return QString::number(num) + ": X: " + QString::number(x) + ", Y: " + QString::number(y);
}

void DrawingAlgorithms::triangle(GLfloat *va, GLfloat *vb, GLfloat *vc)
{
       glVertex3fv(va);
       glVertex3fv(vb);
       glVertex3fv(vc);
}

void DrawingAlgorithms::tetra(GLfloat *a, GLfloat *b, GLfloat *c, GLfloat *d)
{
    glColor3fv(colors[0]);
    triangle(a, b, c);
    glColor3fv(colors[1]);
    triangle(a, c, d);
    glColor3fv(colors[2]);
    triangle(a, d, b);
    glColor3fv(colors[3]);
    triangle(b, d, c);
}

void DrawingAlgorithms::divide_tetra(GLfloat *a, GLfloat *b, GLfloat *c, GLfloat *d, int m)
{

    GLfloat mid[6][3];
    int j;
    if(m>0)
    {
        /* compute six midpoints */

        for(j=0; j<3; j++) mid[0][j]=(a[j]+b[j])/2;
        for(j=0; j<3; j++) mid[1][j]=(a[j]+c[j])/2;
        for(j=0; j<3; j++) mid[2][j]=(a[j]+d[j])/2;
        for(j=0; j<3; j++) mid[3][j]=(b[j]+c[j])/2;
        for(j=0; j<3; j++) mid[4][j]=(c[j]+d[j])/2;
        for(j=0; j<3; j++) mid[5][j]=(b[j]+d[j])/2;

        /* create 4 tetrahedrons by subdivision */

        divide_tetra(a, mid[0], mid[1], mid[2], m-1);
        divide_tetra(mid[0], b, mid[3], mid[5], m-1);
        divide_tetra(mid[1], mid[3], c, mid[4], m-1);
        divide_tetra(mid[2], mid[4], d, mid[5], m-1);

    }
    else(tetra(a,b,c,d)); /* draw tetrahedron at end of recursion */
}


void DrawingAlgorithms::displayTetra()
{
    //glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glTranslatef(0.0f,0.0f,0.0f);
    glRotatef(rtri,0.25f,0.50f,0.25f);
    glBegin(GL_TRIANGLES);
    divide_tetra(v[0], v[1], v[2], v[3], numDivisions);
    glEnd();
    glFlush();
    rtri+=0.35f;
}


void DrawingAlgorithms::myReshape(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if (w <= h)
        glOrtho(-2.0, 2.0, -2.0 * (GLfloat) h / (GLfloat) w,
            2.0 * (GLfloat) h / (GLfloat) w, -10.0, 10.0);
    else
        glOrtho(-2.0 * (GLfloat) w / (GLfloat) h,
            2.0 * (GLfloat) w / (GLfloat) h, -2.0, 2.0, -10.0, 10.0);
    glMatrixMode(GL_MODELVIEW);
    glutPostRedisplay();
}
