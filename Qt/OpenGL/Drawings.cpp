#include "Drawings.h"
#include "GLWidget.h"
#include <QTextStream>

void Drawings::drawLine(int x1, int y1, int x2, int y2) {
    glBegin(GL_LINES);
    QTextStream(stdout) << "x1: " << x1 << " y1: " << y1 << " x2: " << x2 << " y2: " << y2 << endl;
    glVertex2d(x1,y1);
    glVertex2d(x2,y2);
    glEnd();
}

