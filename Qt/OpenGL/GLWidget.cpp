#include "GLWidget.h"
#include "Drawings.h"
#include <QTextStream>
#include <QTimer>


GLWidget::GLWidget(QWidget* parent) : QGLWidget(parent) {
    clearVariables();
}

GLWidget::~GLWidget() {
}

void GLWidget::resizeGL(int w, int h) {
    // This function is called whenever a window is resized

    // Loads the identity matrix onto the matrix stack.
    glLoadIdentity();

    // Sets the viewport
    glViewport(0, 0, w, h);

    GLdouble left, right, up, down;

    /* These variables specify the coordinate set to be used in glOrtho() */
    /* width() gives the width of the window */
    /* height() gives the height of the window */
    /* See QWidget documentation for more info */
    left = - (float) w / 2;
    right = (float) w / 2;
    down = - (float) h / 2;
    up = (float) h / 2;

    glOrtho(left, right, down, up, -1, 1);
}

void GLWidget::initializeGL() {
    //Set the background a blue color
    qglClearColor(QColor(33,150,243));
    //Set line drawing width and color white
    glLineWidth(3);
    glColor3f(1.0f, 1.0f, 1.0f);
}

void GLWidget::paintGL() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //Draws a simple line using GL_LINES
    Drawings::drawLine(x1,y1,x2,y2);
}

void GLWidget::updateBtnClicked(int xa, int ya, int xb, int yb) {
    x1 = xa;
    y1 = ya;
    x2 = xb;
    y2 = yb;
    QGLWidget::update();
}

void GLWidget::clearVariables() {
    x1 = 200;
    y1 = 200;
    x2 = -200;
    y2 = -200;
}

