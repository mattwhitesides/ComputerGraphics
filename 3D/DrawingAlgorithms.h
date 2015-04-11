/*
	DrawingAlgorithms.h - DrawingAlgorithms class declaration. 
	Written by:
	Anoop Haridas
*/

#ifndef DRAWINGALGORITHMS_H
#define DRAWINGALGORITHMS_H
  
#include <QVector>
#include <GLWidget.h>
#include "loadObj.h"
#include "structures.h"

class DrawingAlgorithms
{
public:

	/*<<<<<<<<<<<<<<<<<<<<<<<<<round2f>>>>>>>>>>>>>>>>>>>
    Global function to round floats to nearest integers
    */
    static int roundf2(float f);   

    //Test to see what OpenGL's line drawings look like
    static void openGLDrawLine(int xa, int ya, int xb, int yb);

    static void triangle(GLfloat *va, GLfloat *vb, GLfloat *vc);

    static void tetra(GLfloat *a, GLfloat *b, GLfloat *c, GLfloat *d);

    static void divide_tetra(GLfloat *a, GLfloat *b, GLfloat *c, GLfloat *d, int m);

    static void displayTetra(Translate* t, Rotate* r, Scale* s);

    static void myReshape(int w, int h);

    static void drawCube(Translate* t, Rotate* r, Scale* s);

    static void drawObj(loadObj* objLoader);

    static void animationTest();

private:
	/*<<<<<<<<<<<<<<<<<<convertCoordsToString>>>>>>>>>>>>>>>
    Converts the X and Y coordinates to a formated string output
	Input:
      int num - the point count number
      int x - the x coord
	  int y - the y coord
	Output:
	  QString - the formatted output
	*/
	static QString convertCoordsToString(int num, int x, int y);

};
#endif
