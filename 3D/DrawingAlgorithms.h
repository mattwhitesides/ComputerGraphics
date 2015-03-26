/*
	DrawingAlgorithms.h - DrawingAlgorithms class declaration. 
	Written by:
	Anoop Haridas
*/

#ifndef DRAWINGALGORITHMS_H
#define DRAWINGALGORITHMS_H
  
#include <QVector>
#include <GLWidget.h>

class DrawingAlgorithms
{
public:

	/*<<<<<<<<<<<<<<<<<<<<<<<<<round2f>>>>>>>>>>>>>>>>>>>
    Global function to round floats to nearest integers
    */
    static int roundf2(float f);   

    //Test to see what OpenGL's line drawings look like
    static void openGLDrawLine(int xa, int ya, int xb, int yb);

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
