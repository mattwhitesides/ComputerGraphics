/*
    DrawingAlgorithms.h - DrawingAlgorithms class implementation.
    Written by:
    Anoop Haridas
*/

#include "DrawingAlgorithms.h"
#include <math.h>
#include <stdlib.h>
#include <qgl.h>

QVector<QString> DrawingAlgorithms::dda(int xa, int ya, int xb, int yb) 
{
    QVector<QString> output;
    float xIncrement, yIncrement, x, y;
    int dx, dy, steps, k;

    // Find the distance from the start and end points in the x and y direction
    dx = xb - xa;
    dy = yb - ya;

    // Initialize the start point
    x = xa;
    y = ya;

    // If the absolute distance in the x direction is greater than the y direction
    // then take x number of steps otherwise take dy steps
    if (abs(dx) > abs(dy))
        steps = abs(dx);
    else
        steps = abs(dy);

    // Determine the increments needed for the number of steps
    xIncrement = dx / (float)steps;
    yIncrement = dy / (float)steps;

    glBegin(GL_POINTS);
    //Convert the coords to a string and add to the output list
    output.append(DrawingAlgorithms::convertCoordsToString(0, roundf2(x), roundf2(y)));
    glVertex2i( roundf2(x),  roundf2(y));
    glEnd();

    for ( k=0; k<steps; k++)
    {
        //Increase a little in the x and y direction each step
        //By rounding the values then you get the result of staying
        //At the current pixel coord or moving to the next pixel coord
        x += xIncrement;
        y += yIncrement;

        glBegin(GL_POINTS);
        //Convert the coords to a string and add to the output list
        output.append(DrawingAlgorithms::convertCoordsToString(k+1, roundf2(x), roundf2(y)));
        glVertex2i(roundf2(x),  roundf2(y));
        glEnd();
    }

    output.append("----------\n");

    return output;
}

/*<<<<<<<<<<<<<<<<<<<<<drawLine>>>>>>>>>>>>>>>>>>>>>>>>*/
//1. Input the two line end-points, storing the left endpointin (x0, y0)
QVector<QString> DrawingAlgorithms::drawLine(int xa, int ya, int xb, int yb)
{
    QVector<QString> output;
    int k = 0;

    glBegin(GL_POINTS);

    //2. Plot the point (x0, y0)
    glVertex2i(xa,ya);
    output.append(DrawingAlgorithms::convertCoordsToString(++k,xa,ya));

    //3. Calculate the constants Δx, Δy, 2Δy, and (2Δy - 2Δx) and get the first value for the decision parameter as: P0 = 2Δy - Δx
    int deltaX = (xb - xa);
    int deltaY = (yb - ya);

    //Check if the line is vertical
    if (deltaX == 0) {
        if (ya < yb) {
            for (int y = (ya + 1); y <= yb; ++y) {
                glVertex2i(xa,y);
                output.append(DrawingAlgorithms::convertCoordsToString(++k,xa,y));
            }
        } else {
            for (int y = (ya - 1); y >= yb; --y) {
                glVertex2i(xa,y);
                output.append(DrawingAlgorithms::convertCoordsToString(++k,xa,y));
            }
        }

        glEnd();
        return output;
    }
    //Check if the line is horizontal
    if (deltaY == 0) {
        if (xa < xb) {
            for (int x = (xa + 1); x <= xb; ++x) {
                glVertex2i(x,ya);
                output.append(DrawingAlgorithms::convertCoordsToString(++k,x,ya));
            }
        } else {
            for (int x = (xa - 1); x >= xb; --x) {
                glVertex2i(x,ya);
                output.append(DrawingAlgorithms::convertCoordsToString(++k,x,ya));
            }
        }

        glEnd();
        return output;
    }
    //Check if the slope is exactly 45
    if (deltaX == deltaY) {
        if (xa < xb) {
            for (int x = xa; x <= xb; ++x) {
                glVertex2i(x,++ya);
                output.append(DrawingAlgorithms::convertCoordsToString(++k,x,ya + 1));
            }
        } else {
            for (int x = xa; x >= xb; --x) {
                glVertex2i(x,++ya);
                output.append(DrawingAlgorithms::convertCoordsToString(++k,x,ya + 1));
            }
        }

        glEnd();
        return output;
    }


    int twoDeltaY = 2 * deltaY;
    int twoDeltaX = 2 * deltaX;
    int twoDeltaYMinusTwoDeltaX = twoDeltaY - twoDeltaX;
    int P = twoDeltaY - deltaX;
    int y = ya;

    bool isSteep = (deltaY > deltaX);
    //    if (isSteep) {
    //        swapIntValues(&ya, &xa);
    //        swapIntValues(&yb, &xb);
    //    }

    if (xa < xb) {
        //4. At each xk along the line, starting at k = 0, perform the following test. If pk < 0, the next point to plot is (xk+1, yk) and: Pk+1 = Pk + 2Δy
        //   Otherwise, the next point to plot is (xk+1, yk+1) and: Pk+1 = Pk + 2Δy - 2Δ
        if (!isSteep) {
            for (int x = (xa + 1); x <= xb; ++x) {
                if (P < 0) {

                    glVertex2i(x,y);
                    output.append(DrawingAlgorithms::convertCoordsToString(++k,x,y));

                    P = P + twoDeltaY;
                } else {
                    ++y;

                    glVertex2i(x,y);
                    output.append(DrawingAlgorithms::convertCoordsToString(++k,x,y));

                    P = P + twoDeltaYMinusTwoDeltaX;
                }
                //5. Repeat Step 4, (Δx – 1) times
            }
        } else {
            int x = xa;
            for (y = (ya + 1); y <= yb; ++y) {
                if (P < 0) {

                    glVertex2i(x,y);
                    output.append(DrawingAlgorithms::convertCoordsToString(++k,x,y));

                    P = P + twoDeltaX;
                } else {
                    ++x;

                    glVertex2i(x,y);
                    output.append(DrawingAlgorithms::convertCoordsToString(++k,x,y));

                    P = P + twoDeltaX - twoDeltaY;
                }
                //5. Repeat Step 4, (Δx – 1) times
            }
        }
    } else {
        //4. At each xk along the line, starting at k = 0, perform the following test. If pk < 0, the next point to plot is (xk+1, yk) and: Pk+1 = Pk + 2Δy
        //   Otherwise, the next point to plot is (xk+1, yk+1) and: Pk+1 = Pk + 2Δy - 2Δ
        if (!isSteep) {
            for (int x = (xa - 1); x >= xb; --x) {
                if (P < 0) {

                    glVertex2i(x,y);
                    output.append(DrawingAlgorithms::convertCoordsToString(++k,x,y));

                    P = P + twoDeltaY;
                } else {
                    ++y;

                    glVertex2i(x,y);
                    output.append(DrawingAlgorithms::convertCoordsToString(++k,x,y));

                    P = P + twoDeltaYMinusTwoDeltaX;
                }
                //5. Repeat Step 4, (Δx – 1) times
            }
        } else {
            int x = xa;
            for (y = (ya - 1); y >= yb; --y) {
                if (P < 0) {

                    glVertex2i(x,y);
                    output.append(DrawingAlgorithms::convertCoordsToString(++k,x,y));

                    P = P + twoDeltaX;
                } else {
                    ++x;

                    glVertex2i(x,y);
                    output.append(DrawingAlgorithms::convertCoordsToString(++k,x,y));

                    P = P + twoDeltaX - twoDeltaY;
                }
                //5. Repeat Step 4, (Δx – 1) times
            }
        }
    }

    glEnd();

    return output;
}

/*<<<<<<<<<<<<<<<<<<<<<drawLines>>>>>>>>>>>>>>>>>>>>>>>>*/
//QVector<QString> DrawingAlgorithms::drawLines(int xa[], int ya[], int xb[], int yb[], int size)
//{
//    QVector<QString> output;

//    return output;
//}

void DrawingAlgorithms::drawPoint(int x, int y) {
    glBegin(GL_POINTS);
    glVertex2i(x,y);
    glEnd();
}

//Use OpenGL to draw a line for testing
void DrawingAlgorithms::openGLDrawLine(int xa, int ya, int xb, int yb) {
    //    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLineWidth(1);
    glColor3f(0.0f, 1.0f, 0.0f);

    glBegin(GL_LINES);

    glVertex2i((GLint) xa, (GLint) ya);
    glVertex2i((GLint) xb, (GLint) yb);

    glEnd();
}

//Swicthes the values of two given values
void DrawingAlgorithms::swapIntValues(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

/*<<<<<<<<<<<<<<<<<<<<<<<<<round2f>>>>>>>>>>>>>>>>>>>*/
int DrawingAlgorithms::roundf2(float f)
{
    if (f >= 0)
        return ( ((int) (f+0.5)));
    else
        return ( ((int) (f-0.5)));
}

/*<<<<<<<<<<<<<<<<<<convertCoordsToString>>>>>>>>>>>>>>>*/
QString DrawingAlgorithms::convertCoordsToString(int num, int x, int y)
{
    return QString::number(num) + ": X: " + QString::number(x) + ", Y: " + QString::number(y);
}
