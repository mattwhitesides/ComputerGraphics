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

QVector<QString> DrawingAlgorithms::drawVertical(int xa, int ya, int yb) {
    int k = 0;
    QVector<QString> output;

    glBegin(GL_POINTS);
    if (ya < yb) {
        for (int y = ya; y <= yb; ++y) {
            glVertex2i(xa,y);
            output.append(DrawingAlgorithms::convertCoordsToString(++k,xa,y));
        }
    } else {
        for (int y = ya; y >= yb; --y) {
            glVertex2i(xa,y);
            output.append(DrawingAlgorithms::convertCoordsToString(++k,xa,y));
        }
    }
    glEnd();
    return output;
}

QVector<QString> DrawingAlgorithms::drawHorizontal(int xa, int ya, int xb) {
    int k = 0;
    QVector<QString> output;

    glBegin(GL_POINTS);
    if (xa < xb) {
        for (int x = xa; x <= xb; ++x) {
            glVertex2i(x,ya);
            output.append(DrawingAlgorithms::convertCoordsToString(++k,x,ya));
        }
    } else {
        for (int x = xa; x >= xb; --x) {
            glVertex2i(x,ya);
            output.append(DrawingAlgorithms::convertCoordsToString(++k,x,ya));
        }
    }
    glEnd();
    return output;
}

QVector<QString> DrawingAlgorithms::drawForteyFive(int xa, int ya, int xb) {
    int k = 0;
    QVector<QString> output;

    glBegin(GL_POINTS);
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



/*<<<<<<<<<<<<<<<<<<<<<drawLine>>>>>>>>>>>>>>>>>>>>>>>>*/
//1. Input the two line end-points, storing the left endpointin (x0, y0)
QVector<QString> DrawingAlgorithms::drawLine(int xa, int ya, int xb, int yb)
{
    // Bresenham's line algorithm
    int k = 0;
    QVector<QString> output;

    const bool isSteep = (abs(yb - ya) > abs(xb - xa));

    if(isSteep)
    {
        std::swap(xa, ya);
        std::swap(xb, yb);
    }

    if(xa > xb)
    {
        std::swap(xa, xb);
        std::swap(ya, yb);
    }

    const int dx = xb - xa;
    const int dy = abs(yb - ya);

    float error = dx / 2.0f;
    const int ystep = (ya < yb) ? 1 : -1;
    int y = ya;

    glBegin(GL_POINTS);

    for(int x = xa; x < xb; x++) {
        if (isSteep) {
            glVertex2i(y,x);
            output.append(DrawingAlgorithms::convertCoordsToString(++k,y,x));
        } else {
            glVertex2i(x,y);
            output.append(DrawingAlgorithms::convertCoordsToString(++k,x,y));
        }

        error -= dy;
        if(error < 0) {
            y += ystep;
            error += dx;
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
