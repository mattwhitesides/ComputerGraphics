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
QVector<QString> DrawingAlgorithms::drawLine(int xa, int ya, int xb, int yb)
{
    QVector<QString> output;

    //Check if the angle is larger than 45 degrees if so swap x and y
    bool isSteep = (abs(yb - ya) > abs(xb - xa));
    //Check if xa > xb to dertermine if you draw left to right or right to left
    bool isRightToLeft = (xa > xb);

    //Swap values of x and y if angle is steep
    if (isSteep) {
        swapIntValues(&xa, &ya);
        swapIntValues(&xb, &yb);
    }

    //Calculate the absoulte value of the change in Y get absoulte value because we dident check y
    int deltaY = abs(yb - ya);

    //Calculate the change in X
    int deltaX = xb - xa;

    //Check if the Y step shoould be positive or negitive if yb is greater than ya it's negitive
    int stepY = ya > yb ? -1 : 1;

    //Set our error amt for each step in X
    float error = 0.0;

    //Init our X increment and our y for that position
    int xIncrement = 0;
    int y = 0;

    //Counter
    int k = 0;

    //Check if we need to increment backwoards or fowards
    if (isRightToLeft) {
        //Loop until we hit our desired Xb checking for our isSteep value
        for (xIncrement = xa; xIncrement <= xb; ++xIncrement) {

            //Begin OpenGL Commands, swap x and y if it is steep and append our values for refrence output
            glBegin((GL_POINTS));

            if (!isSteep) {
                output.append(DrawingAlgorithms::convertCoordsToString(++k, roundf2(xIncrement), roundf2(y)));
                glVertex2i(xIncrement,y);
            } else {
                output.append(DrawingAlgorithms::convertCoordsToString(++k, roundf2(y), roundf2(xIncrement)));
                glVertex2i(y,xIncrement);
            }

            glEnd();

            error += deltaY;

            //If the margin of error has passed the midpoint increment our y step and reset the error to it's previous value
            if (error >= 0.5 * deltaX) {
                y += stepY;
                error -= deltaX;
            }
        }
    } else {
        for (xIncrement = xa; xIncrement >= xb; --xIncrement) {

            //Begin OpenGL Commands, swap x and y if it is steep and append our values for refrence output
            glBegin((GL_POINTS));

            if (!isSteep) {
                output.append(DrawingAlgorithms::convertCoordsToString(++k, roundf2(xIncrement), roundf2(y)));
                glVertex2i(xIncrement,y);
            } else {
                output.append(DrawingAlgorithms::convertCoordsToString(++k, roundf2(y), roundf2(xIncrement)));
                glVertex2i(y,xIncrement);
            }

            glEnd();

            error += deltaY;

            //If the margin of error has passed the midpoint increment our y step and reset the error to it's previous value
            if (error >= 0.5 * deltaX) {
                y += stepY;
                error -= deltaX;
            }
        }
    }

    return output;
}

/*<<<<<<<<<<<<<<<<<<<<<drawLine>>>>>>>>>>>>>>>>>>>>>>>>*/
QVector<QString> DrawingAlgorithms::drawLines(int xa[], int ya[], int xb[], int yb[], int size)
{
    QVector<QString> output;

    for (int i = 0; i < size; ++i) {

        printf("xa: %d\n", xa[i]);

        //Check if the angle is larger than 45 degrees if so swap x and y
        bool isSteep = (abs(yb[i] - ya[i]) > abs(xb[i] - xa[i]));
        //Check if xa > xb to dertermine if you draw left to right or right to left
        bool isRightToLeft = (xa[i] > xb[i]);

        //Swap values of x and y if angle is steep
        if (isSteep) {
            swapIntValues(&xa[i], &ya[i]);
            swapIntValues(&xb[i], &yb[i]);
        }

        //Calculate the absoulte value of the change in Y get absoulte value because we dident check y
        int deltaY = abs(yb[i] - ya[i]);

        //Calculate the change in X
        int deltaX = xb[i] - xa[i];

        //Check if the Y step shoould be positive or negitive if yb is greater than ya it's negitive
        int stepY = ya[i] > yb[i] ? -1 : 1;

        //Set our error amt for each step in X
        float error = 0.0;

        //Init our X increment and our y for that position
        int xIncrement = 0;
        int y = 0;

        //Counter
        int k = 0;

        //Check if we need to increment backwoards or fowards
        if (isRightToLeft) {
            //Loop until we hit our desired Xb checking for our isSteep value
            for (xIncrement = xa[i]; xIncrement <= xb[i]; ++xIncrement) {

                //Begin OpenGL Commands, swap x and y if it is steep and append our values for refrence output
                glBegin((GL_POINTS));

                if (!isSteep) {
                    output.append(DrawingAlgorithms::convertCoordsToString(++k, roundf2(xIncrement), roundf2(y)));
                    glVertex2i(xIncrement,y);
                } else {
                    output.append(DrawingAlgorithms::convertCoordsToString(++k, roundf2(y), roundf2(xIncrement)));
                    glVertex2i(y,xIncrement);
                }

                glEnd();

                error += deltaY;

                //If the margin of error has passed the midpoint increment our y step and reset the error to it's previous value
                if (error >= 0.5 * deltaX) {
                    y += stepY;
                    error -= deltaX;
                }
            }
        } else {
            for (xIncrement = xa[i]; xIncrement >= xb[i]; --xIncrement) {

                //Begin OpenGL Commands, swap x and y if it is steep and append our values for refrence output
                glBegin((GL_POINTS));

                if (!isSteep) {
                    output.append(DrawingAlgorithms::convertCoordsToString(++k, roundf2(xIncrement), roundf2(y)));
                    glVertex2i(xIncrement,y);
                } else {
                    output.append(DrawingAlgorithms::convertCoordsToString(++k, roundf2(y), roundf2(xIncrement)));
                    glVertex2i(y,xIncrement);
                }

                glEnd();

                error += deltaY;

                //If the margin of error has passed the midpoint increment our y step and reset the error to it's previous value
                if (error >= 0.5 * deltaX) {
                    y += stepY;
                    error -= deltaX;
                }
            }
        }
        printf("Done with line %d\n", i);
    }

    return output;
}

//Swicthes the values of two given values
void DrawingAlgorithms::swapIntValues(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void DrawingAlgorithms::openGLDrawLine(int xa, int ya, int xb, int yb) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLineWidth(1);
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

/*<<<<<<<<<<<<<<<<<<convertCoordsToString>>>>>>>>>>>>>>>*/
QString DrawingAlgorithms::convertCoordsToString(int num, int x, int y)
{
    return QString::number(num) + ": X: " + QString::number(x) + ", Y: " + QString::number(y);
}
