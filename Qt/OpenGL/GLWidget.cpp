#include "GLWidget.h"
#include "Drawings.h"

GLWidget::GLWidget(QWidget* parent) : QGLWidget(parent)
{

}

GLWidget::~GLWidget()
{

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
    qglClearColor(QColor(33,150,243));
    glLineWidth(3);
    glColor3f(1.0f, 1.0f, 1.0f);
}

void GLWidget::paintGL() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    Drawings::drawLine(-200,-200,200,200);
}

