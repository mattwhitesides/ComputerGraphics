/*
    GLWidget.cpp - GLWidget class implementation.
    Class for widget doing OpenGL drawing for CS 4610/7610.
    Written by:
    Anoop Haridas
*/

#include "GLWidget.h"
#include "LineDialog.h"
#include "loadObj.h"

#include "PrintDialog.h"
#include "DrawingAlgorithms.h"

#include <math.h>

#include <QColorDialog>
#include <QTimer>
#include <QMouseEvent>
#include <QVector>
#include <QString>

const int GLWidget::NONE = 0;
const int GLWidget::MOUSE = 1;
const int GLWidget::DIALOG = 2;

const int GLWidget::CLEAR = 0;
const int GLWidget::LINE = 1;
const int GLWidget::POLYGON = 4;

bool wKey = false;
bool aKey = false;
bool sKey = false;
bool dKey = false;
bool iKey = false;
bool jKey = false;
bool kKey = false;
bool lKey = false;
bool upKey = false;
bool leftKey = false;
bool downKey = false;
bool rightKey = false;
bool shiftUpKey = false;
bool shiftDownKey = false;

Translate t = {0.0,0.0,-2.0};
Rotate r = {0.0,0.0,0.0};
Scale s = {1.0,1.0,1.0};
Camera c = {90.0,0.1,600,0.0};

Shape shape = TETRA;
loadObj *objLoader = new loadObj();

//------------------------GLWidget::GLWidget-------------------------
GLWidget::GLWidget(QWidget *parent) : QGLWidget(parent)
{
    //Initialize all the variables
    lineColor[0] = 255;
    lineColor[1] = 255;
    lineColor[2] = 255;

    clickCounter = drawMode = shapeMode = 0;

    clearShapeVariables();

    printOnce = false;

    //Create Dialogs
    printDiag = new PrintDialog(this);
    printDiag->setModal(false);
    printDiag->setVisible(true);

    //Input that comes up when selecting Graphics->Draw->Line
    lineDiag = new LineDialog(this);
    lineDiag->setModal(false);
    lineDiag->setVisible(false);
    connect(lineDiag, SIGNAL(valuesUpdated(int, int, int, int)), this, SLOT(updateDialogLine(int, int, int, int)));

    // The following code allows for animated graphics by attempting to refresh the screen at 50fps.
    //	STEP 1: Create a timer
    QTimer *timer = new QTimer(this);
    //	STEP 2: Update the GL graphics every time the timer is fired off
    connect(timer, SIGNAL(timeout()), this, SLOT(updateGL()));
    //connect(timer, SIGNAL(timeout()), this, SLOT(keyHoldUpdate()));
    //	STEP 3: Start the timer to go off every 20 milliseconds.
    timer->start(16);

    // Enables mouse tracking. This means that whenever the mouse is moved
    // and/or clicked on the widget, a mouse event is generated
    setMouseTracking(true);

    setFocusPolicy( Qt::StrongFocus );
    setFocus( Qt::PopupFocusReason );
    setEnabled( true );
}

//--------------------------GLWidget::~GLWidget----------------------------
GLWidget::~GLWidget()
{

}

//-------------------------GLWidget::minimumSizeHint-----------------------
QSize GLWidget::minimumSizeHint() const
{
    return QSize(50, 50);
}


//--------------------------GLWidget::sizeHint-----------------------------
QSize GLWidget::sizeHint() const
{
    return QSize(500, 500);
}

//--------------------------GLWidget::setDrawingMode-----------------------
void GLWidget::setDrawingMode(int mode)
{
    drawMode = mode;
}

//--------------------------GLWidget::setShapeMode-------------------------
void GLWidget::setShapeMode(int mode)
{
    shapeMode = mode;
}

/*----------------------GLWidget::togglePrintDialog------------------------
Toggles the print dialog for displaying results.
*/
void GLWidget::togglePrintDialog()
{
    if(printDiag->isHidden())
    {
        printDiag->setVisible(true);
    }
    else
    {
        printDiag->setVisible(false);
    }
}

//------------------------GLWidget::drawDialogLine--------------------------
void GLWidget::drawDialogLine()
{
    drawMode = GLWidget::DIALOG;
    shapeMode = GLWidget::LINE;
    clearShapeVariables();
    lineDiag->show();
}

/*-----------------------GLWidget::updateDialogLine-------------------------*/
void GLWidget::updateDialogLine(int x1, int y1, int x2, int y2)
{
    drawMode = GLWidget::DIALOG;  //Set the drawing mode to dialog
    shapeMode = GLWidget::LINE;   //Set shape to LINE
    clearShapeVariables();        //Clear the state variables

    //Set the line variables
    startX = x1;
    startY = y1;
    finishX = x2;
    finishY = y2;

    areShapesClear = false;       //Indicate a shape is ready to draw
    printOnce = false;            //Clear to allow the results to print once
}

/*----------------------------GLWidget::drawMouseLine-----------------------*/
void GLWidget::drawMouseLine()
{
    drawMode = GLWidget::MOUSE;
    shapeMode = GLWidget::LINE;
    drawShape = GLWidget::LINE;
    clearShapeVariables();
}

void GLWidget::drawCubePolygon() {
    shape = CUBE;
}

void GLWidget::drawAnimationTest() {
    shape = ANIMATION;
}

void GLWidget::drawTetraPolygon() {
    shape = TETRA;
}

void GLWidget::drawObjPolygon() {
    DrawingAlgorithms::drawObj(objLoader);
    shape = OBJ;
}

/*-------------------------GLWidget::drawMousePolygon-----------------------*/
void GLWidget::drawMousePolygon()
{
    drawMode = GLWidget::MOUSE;
    shapeMode = GLWidget::POLYGON;
    clearShapeVariables();
}

//----------------------------GLWidget::clearWindow---------------------------
void GLWidget::clearWindow()
{
    drawMode = GLWidget::NONE;

    clearShapeVariables();

    // Clears the OpenGL color and depth buffers. This effectively clears the screen.
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

//-------------------------GLWidget::chooseColor------------------------------
void GLWidget::chooseColor()
{

    // This function pops up a color selection dialog and sets the color, user selected

    // Get the current color
    QColor color(lineColor[0], lineColor[1], lineColor[2]);

    // Pop-up the color dialog and get the chosen color
    color = QColorDialog::getColor(color, this);

    // Set the new color
    lineColor[0] = color.red();
    lineColor[1] = color.green();
    lineColor[2] = color.blue();

    // Set the current OpenGL drawing color. The 'ub' stands for 'unsigned byte', and
    // the 'v' is present because the values are placed in a 'vector' (ie. an array).
    glColor3ubv(lineColor);
}

//-------------------------GLWidget::initializeGL-----------------------------
void GLWidget::initializeGL()
{
    // This function initializes the OpenGL prior to drawing anything

    glShadeModel(GL_SMOOTH);
    glClearColor(0.0f, 0.0f, 0.0f, 0.5f);
    glClearDepth(1.0f);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
}

//-----------------------GLWidget::resizeGL-----------------------------------
void GLWidget::resizeGL(int w, int h)
{
    //    // This function is called whenever a window is resized

    //    // Loads the identity matrix onto the matrix stack.
    //    glLoadIdentity();

    //    // Sets the viewport
    //    glViewport(0, 0, w, h);

    //    GLdouble left, right, up, down;

    //    /* These variables specify the coordinate set to be used in glOrtho() */
    //    /* width() gives the width of the window */
    //    /* height() gives the height of the window */
    //    /* See QWidget documentation for more info */
    //    left = - (float) w / 2;
    //    right = (float) w / 2;
    //    down = - (float) h / 2;
    //    up = (float) h / 2;

    //    glOrtho(left, right, down, up, -1, 1);

    DrawingAlgorithms::myReshape(w, h);
    c.aspect = w/h;
}


//--------------------------GLWidget::paintGL----------------------------------
void GLWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    switch (shape) {
    case TETRA:
        DrawingAlgorithms::displayTetra(&t,&r,&s,&c);
        break;
    case CUBE:
        DrawingAlgorithms::drawCube(&t,&r,&s,&c);
        break;
    case ANIMATION:
        DrawingAlgorithms::animationTest();
        break;
    case OBJ:
        objLoader->drawmodel(&t,&r,&s,&c);
        break;
    }

    glFlush();
}

//---------------------GLWidget::MouseMoveEvent-----------------------------
void GLWidget::mouseMoveEvent(QMouseEvent* e)
{
    //Everytime the mouse moves inside the OpenGL widget, it
    //sends out the new mouse position (centered at the middle)
    //to the MainWindow
    emit mouseMoved(e->x() - width()/2 , height()/2 - e->y());
}

//---------------------GLWidget::MousePressEvent----------------------------
void GLWidget::mousePressEvent(QMouseEvent* e)
{
    //This is a method overridden from the base QWidget.
    //When a mouse button is pressed this method is automatically called.
    //The QMouseEvent parameter has information including
    //which button was pressed and more importantly the position
    if(e->button() == Qt::LeftButton)
    {
        if(drawMode == GLWidget::MOUSE)
        {
            switch(shapeMode)
            {
            case GLWidget::LINE:
                if(clickCounter == 0)
                {
                    clearShapeVariables();            // Clear all the variables
                    startX = e->x() - width()/2;      // Get the X mouse position and translate so (0,0) is screen center

                    startY = height()/2 - e->y();     // Get the Y mouse position and translate so (0,0) is screen center

                    areShapesClear = false;           // Indicate that a shape is being created
                }
                else if(clickCounter == 1)
                {
                    finishX = e->x() - width()/2;   // Get the X coord of the line end point
                    finishY = height()/2 - e->y();  // Get the Y coord of the line end point
                    printOnce = false;              // Setting this to false ensures the values of the line will only be printed once rather than repeatedly
                }

                clickCounter = (clickCounter + 1) % 2;

                break;

            case GLWidget::POLYGON:
                //Starts and and continues a polygon
                break;
            }
        }
    }
    else if(e->button() == Qt::RightButton)
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        switch(shapeMode)
        {
        case GLWidget::POLYGON:
            //Ends and closes the polygon
            break;
        }
    }
}

void GLWidget::keyPressEvent(QKeyEvent* event) {
    GLfloat moveInc = 0.15;
    GLfloat rotInc = 2.0;
    GLfloat scaleInc = 0.05;
    switch (event->key()) {
    case Qt::Key_Up:
        if(event->modifiers() & Qt::ShiftModifier ) {
            t.z += moveInc;
            shiftUpKey = true;
        }
        else {
            t.y += moveInc;
            upKey = true;
        }
        break;
    case Qt::Key_Down:
        if(event->modifiers() & Qt::ShiftModifier ) {
            t.z -= moveInc;
            shiftDownKey = true;
        }
        else {
            t.y -= moveInc;
            downKey = true;
        }
        break;
    case Qt::Key_Left:
        t.x -= moveInc;
        leftKey = true;
        break;
    case Qt::Key_Right:
        t.x += moveInc;
        rightKey = true;
        break;
    case Qt::Key_W:
        r.x += rotInc;
        wKey = true;
        break;
    case Qt::Key_A:
        r.y -= rotInc;
        aKey = true;
        break;
    case Qt::Key_S:
        r.x -= rotInc;
        sKey = true;
        break;
    case Qt::Key_D:
        r.y += rotInc;
        dKey = true;
        break;
    case Qt::Key_I:
        s.y += scaleInc;
        iKey = true;
        break;
    case Qt::Key_J:
        s.x -= scaleInc;
        jKey = true;
        break;
    case Qt::Key_K:
        s.y -= scaleInc;
        kKey = true;
        break;
    case Qt::Key_L:
        s.x += scaleInc;
        lKey = true;
        break;
    case Qt::Key_Z:
        c.fov += 1;
        break;
    case Qt::Key_X:
        c.fov -= 1;
    case Qt::Key_C:
        c.zNear += 0.1;
        break;
    case Qt::Key_V:
        c.zNear -= 0.1;
        break;
    }
    printf("Translate:\n\t%lf\n\t%lf\n\t%lf\n\n",t.x,t.y,t.z);
}

void GLWidget::keyReleaseEvent(QKeyEvent* event) {
    switch (event->key()) {
    case Qt::Key_Up:
        if(event->modifiers() & Qt::ShiftModifier ) {
            shiftUpKey = false;
        }
        else {
            upKey = false;
        }
        break;
    case Qt::Key_Down:
        if(event->modifiers() & Qt::ShiftModifier ) {
            shiftDownKey = false;
        }
        else {
            downKey = false;
        }
        break;
    case Qt::Key_Left:
        leftKey = false;
        break;
    case Qt::Key_Right:
        rightKey = false;
        break;
    case Qt::Key_W:
        wKey = false;
        break;
    case Qt::Key_A:
        aKey = false;
        break;
    case Qt::Key_S:
        sKey = false;
        break;
    case Qt::Key_D:
        dKey = false;
        break;
    case Qt::Key_I:
        iKey = false;
        break;
    case Qt::Key_J:
        jKey = false;
        break;
    case Qt::Key_K:
        kKey = false;
        break;
    case Qt::Key_L:
        lKey = false;
        break;
    }
}

//-----------------GLWidget::ClearShapeVariables-------------------------
void GLWidget::clearShapeVariables()
{
    //The end point coordinates for the line
    startX = startY = finishX = finishY = 0;

    areShapesClear = true;

    printOnce = true;
}

void GLWidget::keyHoldUpdate() {
    GLfloat moveInc = 0.15;
    GLfloat rotInc = 2.0;
    GLfloat scaleInc = 0.05;
    if(shiftUpKey) t.z += moveInc;
    if(upKey) t.y += moveInc;
    if(shiftDownKey) t.z -= moveInc;
    if(downKey) t.y -= moveInc;
    if(leftKey) t.x -= moveInc;
    if(rightKey) t.x += moveInc;
    if(wKey) r.x += rotInc;
    if(aKey) r.y -= rotInc;
    if(sKey) r.x -= rotInc;
    if(dKey) r.y += rotInc;
    if(iKey) s.y += scaleInc;
    if(jKey) s.x -= scaleInc;
    if(kKey) s.y -= scaleInc;
    if(lKey) s.x += scaleInc;
}
