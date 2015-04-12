/*
    DrawingAlgorithms.h - DrawingAlgorithms class implementation.
    Written by:
    Anoop Haridas
*/

#include "DrawingAlgorithms.h"
#include "loadObj.h"
#include <math.h>
#include <stdlib.h>
#include <qgl.h>
#include <qdir.h>
#include <qstring.h>
#include <stdio.h>
#include <qfiledialog.h>
#ifdef WINDOWS
#include <direct.h>
#define GetCurrentDir _getcwd
#else
#include <unistd.h>
#define GetCurrentDir getcwd
#endif

//244,67,54
//33,150,243
//76,175,80


GLfloat v[4][3]={{0.0f, 0.0f, 1.0f}, {0.0f, 0.942809f, -0.33333f}, {-0.816497f, -0.471405f, -0.333333f}, {0.816497f, -0.471405f, -0.333333f}};
GLfloat colors[4][3] = {{0.97f, 0.26f, 0.21f}, {0.13f, 0.59f, 0.95f}, {0.30f, 0.69f, 0.31f}, {1.0f, 0.47f, 0.0f}};
GLdouble aspect = 0.0;

GLfloat	rtri = 0.0f;
GLfloat	rquad = 0.0f;
Scale sAni = {0.5f,0.5f,0.5f};
Translate tAni = {0.0f,0.0f,-2.0f};
bool sAniSwitch = true;
bool tAniSwitch = true;
bool tYAniSwitch = true;

int numDivisions = 3;

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


void DrawingAlgorithms::drawCube(Translate* t, Rotate* r, Scale* s, Camera* c) {
    glLoadIdentity();
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(c->fov,aspect,c->zNear,c->zFar);
    glTranslatef(t->x,t->y,t->z);
    glRotatef(r->x, 1.0f, 0.0f, 0.0f);   //X
    glRotatef(r->y, 0.0f, 1.0f, 0.0f);   //Y
    glRotatef(r->z, 0.0f, 0.0f, 1.0f);   //Z
    glScalef(s->x,s->y,s->z);
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


void DrawingAlgorithms::displayTetra(Translate* t, Rotate* r, Scale* s, Camera* c)
{
    //glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(c->fov,aspect,c->zNear,c->zFar);
    glTranslatef(t->x,t->y,t->z);
    glRotatef(r->x, 1.0f, 0.0f, 0.0f);   //X
    glRotatef(r->y, 0.0f, 1.0f, 0.0f);   //Y
    glRotatef(r->z, 0.0f, 0.0f, 1.0f);   //Z
    glScalef(s->x,s->y,s->z);
    glBegin(GL_TRIANGLES);
    divide_tetra(v[0], v[1], v[2], v[3], numDivisions);
    glEnd();
    glFlush();
    //rtri += .35;
}


void DrawingAlgorithms::myReshape(int w, int h)
{
    aspect = w/h;
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluPerspective(90,aspect,0.1,600);

    //    if (w <= h) {
    //        //glOrtho(-2.0, 2.0, -2.0 * (GLfloat) h / (GLfloat) w, 2.0 * (GLfloat) h / (GLfloat) w, -10.0, 10.0);
    //        //glFrustum(GLdouble left, GLdouble right, GLdouble bottom, GLdouble top, GLdouble near, GLdouble far);
    //    }
    //    else {
    //        //glOrtho(-2.0 * (GLfloat) w / (GLfloat) h, 2.0 * (GLfloat) w / (GLfloat) h, -2.0, 2.0, -10.0, 10.0);
    //    }

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

}

void DrawingAlgorithms::animationTest() {
    glLoadIdentity();
    glTranslatef(tAni.x,tAni.y,tAni.z);
    glRotatef(rtri, 1.0f, 0.0f, 0.0f);   //X
    glRotatef(rtri, 0.0f, 1.0f, 0.0f);   //Y
    glRotatef(rtri, 0.0f, 0.0f, 1.0f);   //Z
    glScalef(sAni.x,sAni.y,sAni.z);
    glBegin(GL_QUADS);
    glColor3f(0.80f,0.86f,0.22f);
    glutSolidSphere(1,50,30);
    glEnd();

    rtri+= 2.0f;

    if (sAni.x > 0.6f) sAniSwitch = false;
    if (sAni.x < 0.25f) sAniSwitch = true;
    if (sAniSwitch) {
        sAni.x += 0.001f;
        sAni.y += 0.001f;
        sAni.z += 0.001f;
    } else {
        sAni.x -= 0.001f;
        sAni.y -= 0.001f;
        sAni.z -= 0.001f;
    }

    if (tAni.x > 1.0f) tAniSwitch = false;
    if (tAni.x < -2.0f) tAniSwitch = true;
    if (tAniSwitch) {
        tAni.x += 0.005f;
        //tAni.y += 0.007f;
        tAni.z += 0.002f;
    } else {
        tAni.x -= 0.005f;
        //tAni.y -= 0.007f;
        tAni.z -= 0.002f;
    }

    if (tAni.y > 2.0f) tYAniSwitch = false;
    if (tAni.y < -2.0f) tYAniSwitch = true;
    if (tYAniSwitch) {
        tAni.y += 0.007f;
    } else {
        tAni.y -= 0.007f;
    }
}

void DrawingAlgorithms::drawObj(loadObj* obj) {
    QString fn = QFileDialog::getOpenFileName(NULL, "Open File", "", "Obj files (*.obj)");
    QByteArray ba = fn.toLatin1();
    char* fn2 = ba.data();
    printf("\nFn2: %s", fn2);

    obj->Load(fn2);
}
