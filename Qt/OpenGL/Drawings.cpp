#include "Drawings.h"
#include "GLWidget.h"

void Drawings::drawLine(int x1, int y1, int x2, int y2) {
    glBegin(GL_LINES);
    glVertex2d(x1,y1);
    glVertex2d(x2,y2);
    glEnd();
}

