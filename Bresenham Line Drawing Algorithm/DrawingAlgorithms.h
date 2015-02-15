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
	
    // Draws a line using 2 points to start and end using the DDA Algorithm

	/* Input:
      int xa - the x coord of the start point
	  int ya - the y coord of the start point
	  int xb - the x coord of the end point
	  int yb - the y coord of the end point
	Output:
	  QVector<QString> - a list of the output points formatted as strings
	*/
	static QVector<QString> dda(int xa, int ya, int xb, int yb);

	/*<<<<<<<<<<<<<<<<<<<<<drawLine>>>>>>>>>>>>>>>>>>>>>>>>
    // Draws a line using 2 points to start and end using the Bresenham Algorithm

      int xa - the x coord of the start point
      int ya - the y coord of the start point
      int xb - the x coord of the end point
      int yb - the y coord of the end point
    Output:
      QVector<QString> - a list of the output points formatted as strings
	*/
	static QVector<QString> drawLine(int xa, int ya, int xb, int yb);

    /*<<<<<<<<<<<<<<<<<<<<<drawLines>>>>>>>>>>>>>>>>>>>>>>>>
    // Draws a line using and array of 2 points to start and end using the Bresenham Algorithm

      int xa - the x coord of the start point
      int ya - the y coord of the start point
      int xb - the x coord of the end point
      int yb - the y coord of the end point
    Output:
      QVector<QString> - a list of the output points formatted as strings
    */
    static QVector<QString> drawLines(int xa[], int ya[], int xb[], int yb[], int size);

    static QVector<QString> drawForteyFive(int xa, int ya, int xb);

    static QVector<QString> drawVertical(int xa, int ya, int yb);

    static QVector<QString> drawHorizontal(int xa, int ya, int xb);

    /*<<<<<<<<<<<<<<<<<<<<<drawLines>>>>>>>>>>>>>>>>>>>>>>>>
    // Draws a single pixel at a given x and y coord

      int x - the x coord point
      int y - the y coord point
    */
    static void drawPoint(int x, int y);

	/*<<<<<<<<<<<<<<<<<<<<<<<<<round2f>>>>>>>>>>>>>>>>>>>
    Global function to round floats to nearest integers
    */
    static int roundf2(float f);   

    /*<<<<<<<<<<<<<<<<<<swapIntValues>>>>>>>>>>>>>>>
    Swaps the values of two given ints
    Input:
      int* a
        The first value to swap
      int* b
        The second value to swap
    */
    static void swapIntValues(int* a,int* b);

    //Test to see what OpenGL's line drawings look like
    static void openGLDrawLine(int xa, int ya, int xb, int yb);

    /*<<<<<<<<<<<<<<<<<<drawPolyLine>>>>>>>>>>>>>>>
    Draws a polyline based upon a list of coords given
    Input:
        QList<Coord> coords
            A list of coordnate values using the Coord struct
    Return:
        A Vector List of Strings based on the output of the algorithem
    */
    static QVector<QString> drawPolyLine(QList<Coord> coords);

    /*<<<<<<<<<<<<<<<<<<drawCircle>>>>>>>>>>>>>>>
    Draws a circle using the circle algorithem
    Input:
      int xa - the x coord of the start point
      int ya - the y coord of the start point
      int xb - the x coord of the end point
      int yb - the y coord of the end point
    Return:
        A Vector List of Strings based on the output of the algorithem
    */
    static QVector<QString> drawCircle(int xa, int ya, int xb, int yb);

    /*<<<<<<<<<<<<<<<<<<drawCircle>>>>>>>>>>>>>>>
    Draws a circle using the circle algorithem
    Input:
      int xa - the x coord of the start point
      int ya - the y coord of the start point
      int r - the radius of the desired circle
    Return:
        A Vector List of Strings based on the output of the algorithem
    */
    static QVector<QString> drawCircle(int xa, int ya, int r);

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
