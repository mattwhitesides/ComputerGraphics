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

    if(isSteep) {
        std::swap(xa, ya);
        std::swap(xb, yb);
    }

    if(xa > xb) {
        std::swap(xa, xb);
        std::swap(ya, yb);
    }

    //3. Calculate the constants Δx, Δy, 2Δy and get the first value for the decision parameter as: P0 = 2Δy - Δx
    const int dy = abs(yb - ya);
    const int dx = xb - xa;

    //Check if the line is vertical
    if (dx == 0) return drawVertical(xa,ya,yb);

    //Check if the line is horizontal
    //if (dy == 0) return drawHorizontal(xa,ya,xb);

    //Check if the slope is exactly 45
    //if (dx == dy) return drawForteyFive(xa,ya,xb);

    const int twoDy = 2 * dy;
    int decision = twoDy - dx;
    const int yIteration = (ya < yb) ? 1 : -1;
    int y = ya;

    glBegin(GL_POINTS);

    //2. Plot the point (x0, y0)
    glVertex2i(xa,ya);
    output.append(DrawingAlgorithms::convertCoordsToString(++k,xa,ya));

    //4. At each xk along the line, starting at k = 0, perform the following test. If pk < 0, the next point to plot is (xk+1, yk+1) and: Pk+1 = Pk + 2Δy
    //   Otherwise, the next point to plot is (xk+1, yk+1) and: Pk+1 = Pk + 2Δy - 2Δx
    for (int x = (xa + 1); x <= xb; x++) {
        if (isSteep) {
            glVertex2i(y,x);
            output.append(DrawingAlgorithms::convertCoordsToString(++k,y,x));
        } else {
            glVertex2i(x,y);
            output.append(DrawingAlgorithms::convertCoordsToString(++k,x,y));
        }

        decision -= dy;
        if(decision < 0) {
            y += yIteration;
            decision += dx;
        }
        //5. Repeat Step 4, (Δx – 1) times
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
    glLineWidth(3);
    glColor3f(0.0f, 1.0f, 0.0f);

    glBegin(GL_LINES);

    glVertex2i((GLint) xa, (GLint) ya);
    glVertex2i((GLint) xb, (GLint) yb);

    glEnd();
}

QVector<QString> DrawingAlgorithms::drawPolyLine(QList<Coord> coords) {
    QVector<QString> output;
    glLineWidth(3);

    int i = 0;
    glBegin(GL_LINES);

    glVertex2i((GLint) coords[0].x, (GLint) coords[0].y);
    glVertex2i((GLint) coords[1].x, (GLint) coords[1].y);
    output.append(DrawingAlgorithms::convertCoordsToString(i, roundf2(coords[0].x), roundf2(coords[0].y)));

    for (i = 1; i < coords.size(); ++i) {
        glVertex2i((GLint) coords[i - 1].x, (GLint) coords[i - 1].y);
        glVertex2i((GLint) coords[i].x, (GLint) coords[i].y);
        output.append(DrawingAlgorithms::convertCoordsToString(i, roundf2(coords[i].x), roundf2(coords[i].y)));
    }

    glVertex2i((GLint) coords[0].x, (GLint) coords[0].y);
    glVertex2i((GLint) coords[i - 1].x, (GLint) coords[i - 1].y);
    output.append(DrawingAlgorithms::convertCoordsToString(i, roundf2(coords[0].x), roundf2(coords[0].y)));

    glEnd();

    return output;
}

QVector<QString> DrawingAlgorithms::drawCircle(int xa, int ya, int xb, int yb) {
    QVector<QString> output;
    int i = 0;

    //Calculate Radius
    int r = sqrt(pow((xb - xa),2) + pow((yb - ya),2));

    //Init y to radius and x to 0
    int x = 0;
    int y = r;

    //Round decision variable to 1 - r
    int p = 1 - r;

    glBegin(GL_POINTS);

    //Plot first point
    glVertex2i((GLint) x, (GLint) y);

    //Calculate all points based on first segment of circle
    while (x < y) {
        if (p < 0) {
            p += 2 * x + 3;
            ++x;
        } else {
            p += 2 * (x - y) + 5;
            ++x;
            --y;
        }

        //Plot all 8 symetric points
        glVertex2i(x + xa, y + ya);
        glVertex2i(y + xa, x + ya);
        glVertex2i(-x + xa, y + ya);
        glVertex2i(-y + xa, x + ya);
        glVertex2i(-x + xa, -y + ya);
        glVertex2i(-y + xa, -x + ya);
        glVertex2i(x + xa, -y + ya);
        glVertex2i(y + xa, -x + ya);

        output.append(DrawingAlgorithms::convertCoordsToString(++i, x + xa, y + ya));
        output.append(DrawingAlgorithms::convertCoordsToString(++i, y + xa, x + ya));
        output.append(DrawingAlgorithms::convertCoordsToString(++i, -x + xa, y + ya));
        output.append(DrawingAlgorithms::convertCoordsToString(++i, -y + xa, x + ya));
        output.append(DrawingAlgorithms::convertCoordsToString(++i, -x + xa, -y + ya));
        output.append(DrawingAlgorithms::convertCoordsToString(++i, -y + xa, -x + ya));
        output.append(DrawingAlgorithms::convertCoordsToString(++i, x + xa, -y + ya));
        output.append(DrawingAlgorithms::convertCoordsToString(++i, y + xa, -x + ya));
    }

    glEnd();

    return output;
}

//Overloaded version that already includes radius
QVector<QString> DrawingAlgorithms::drawCircle(int xa, int ya, int r) {
    QVector<QString> output;
    int i = 0;

    //Init y to radius and x to 0
    int x = 0;
    int y = r;

    //Round decision variable to 1 - r
    int p = 1 - r;

    glBegin(GL_POINTS);

    //Plot first point
    glVertex2i((GLint) x, (GLint) y);

    //Calculate all points based on first segment of circle
    while (x < y) {
        if (p < 0) {
            p += 2 * x + 3;
            ++x;
        } else {
            p += 2 * (x - y) + 5;
            ++x;
            --y;
        }

        //Plot all 8 symetric points
        glVertex2i(x + xa, y + ya);
        glVertex2i(y + xa, x + ya);
        glVertex2i(-x + xa, y + ya);
        glVertex2i(-y + xa, x + ya);
        glVertex2i(-x + xa, -y + ya);
        glVertex2i(-y + xa, -x + ya);
        glVertex2i(x + xa, -y + ya);
        glVertex2i(y + xa, -x + ya);

        output.append(DrawingAlgorithms::convertCoordsToString(++i, x + xa, y + ya));
        output.append(DrawingAlgorithms::convertCoordsToString(++i, y + xa, x + ya));
        output.append(DrawingAlgorithms::convertCoordsToString(++i, -x + xa, y + ya));
        output.append(DrawingAlgorithms::convertCoordsToString(++i, -y + xa, x + ya));
        output.append(DrawingAlgorithms::convertCoordsToString(++i, -x + xa, -y + ya));
        output.append(DrawingAlgorithms::convertCoordsToString(++i, -y + xa, -x + ya));
        output.append(DrawingAlgorithms::convertCoordsToString(++i, x + xa, -y + ya));
        output.append(DrawingAlgorithms::convertCoordsToString(++i, y + xa, -x + ya));
    }

    glEnd();

    return output;
}

QVector<QString> DrawingAlgorithms::drawEllipse(int x, int y, int xR, int yR) {
    QVector<QString> output;
    int i = 0;

    //Init the midpoints of x an y
    int midx = xR / 2;
    int midy = yR / 2;
    //Save the origional positions of x and y for translation later
    int x2 = x;
    int y2 = y;

    //Precalcualte x and y radius squared and that squared
    int twoXR = xR * xR;
    int twoYR = yR * yR;
    int twoXRSquard = 2 * twoXR;
    int twoYRSquard = 2 * twoYR;

    //Init desicion variables
    int dx = 0;
    x = dx;
    y = yR;
    int dy = twoXRSquard * y;

    glBegin(GL_POINTS);

    //Draw top, bottom, left and right points
    glVertex2i(midx + x + x2, midy + y + y2);
    glVertex2i(midx - x + x2, midy + y + y2);
    glVertex2i(midx + x + x2, midy - y + y2);
    glVertex2i(midx - x + x2, midy - y + y2);

    output.append(DrawingAlgorithms::convertCoordsToString(++i, midx + x + x2, midy + y + y2));
    output.append(DrawingAlgorithms::convertCoordsToString(++i, midx - x + x2, midy + y + y2));
    output.append(DrawingAlgorithms::convertCoordsToString(++i, midx + x + x2, midy - y + y2));
    output.append(DrawingAlgorithms::convertCoordsToString(++i, midx - x + x2, midy - y + y2));

    //Calculate first decision
    int d = (int)(0.5 + twoYR - (twoXR * yR) + (0.25 * twoXR));

    //Loop until the change in x surpasses the change in y
    while (dx < dy) {
        x = x + 1;
        dx = dx + twoYRSquard;

        if (d < 0) {
            d = d + twoYR + dx;
        } else {
            y = y - 1;
            dy = dy - twoXRSquard;
            d = d + twoYR + dx - dy;
        }

        //Draw the four symetrical points
        glVertex2i(midx + x + x2, midy + y + y2);
        glVertex2i(midx - x + x2, midy + y + y2);
        glVertex2i(midx + x + x2, midy - y + y2);
        glVertex2i(midx - x + x2, midy - y + y2);

        output.append(DrawingAlgorithms::convertCoordsToString(++i, midx + x + x2, midy + y + y2));
        output.append(DrawingAlgorithms::convertCoordsToString(++i, midx - x + x2, midy + y + y2));
        output.append(DrawingAlgorithms::convertCoordsToString(++i, midx + x + x2, midy - y + y2));
        output.append(DrawingAlgorithms::convertCoordsToString(++i, midx - x + x2, midy - y + y2));
    }

    //Calculate new decision for the bottom slope drawing
    d = (int)(0.5 + twoYR * (x + 0.5) * (x + 0.5) + twoXR * (y - 1) * (y - 1) - twoXR * twoYR);

    //Calculate the rest of the ellipse
    while (y > 0) {
        y = y - 1;
        dy = dy - twoXRSquard;

        if (d > 0) {
            d = d + twoXR - dy;
        } else {
            x = x + 1;
            dx = dx + twoYRSquard;
            d = d + twoXR - dy + dx;
        }

        //Draw the four symetrical points
        glVertex2i(midx + x + x2, midy + y + y2);
        glVertex2i(midx - x + x2, midy + y + y2);
        glVertex2i(midx + x + x2, midy - y + y2);
        glVertex2i(midx - x + x2, midy - y + y2);

        output.append(DrawingAlgorithms::convertCoordsToString(++i, midx + x + x2, midy + y + y2));
        output.append(DrawingAlgorithms::convertCoordsToString(++i, midx - x + x2, midy + y + y2));
        output.append(DrawingAlgorithms::convertCoordsToString(++i, midx + x + x2, midy - y + y2));
        output.append(DrawingAlgorithms::convertCoordsToString(++i, midx - x + x2, midy - y + y2));
    }

    glEnd();

    return output;
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
