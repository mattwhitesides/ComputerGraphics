/*
    GLWidget.cpp - GLWidget class implementation.
    Class for widget doing OpenGL drawing for CS 4610/7610.
    Written by:
    Anoop Haridas
*/

#include "GLWidget.h"
#include "LineDialog.h"

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
const int GLWidget::CIRCLE = 2;
const int GLWidget::ELLIPSE = 3;
const int GLWidget::POLYGON = 4;
const int GLWidget::POLYLINE = 5;

const int GLWidget::FAN = 6;
const int GLWidget::HOUSE = 7;
const int GLWidget::BOW = 8;
const int GLWidget::TEST = 9;


//------------------------GLWidget::GLWidget-------------------------
GLWidget::GLWidget(QWidget *parent) : QGLWidget(parent)
{
    //Initialize all the variables
    lineColor[0] = 255;
    lineColor[1] = 255;
    lineColor[2] = 255;

    clickCounter = 0;
    drawMode = shapeMode = 0;

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
    //	STEP 3: Start the timer to go off every 20 milliseconds.
    timer->start(20);

    // Enables mouse tracking. This means that whenever the mouse is moved
    // and/or clicked on the widget, a mouse event is generated
    setMouseTracking(true);
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

/*------------------------GLWidget::drawMousePolyline-----------------------*/
void GLWidget::drawMousePolyline()
{
    drawMode = GLWidget::MOUSE;
    shapeMode = GLWidget::POLYLINE;
    clearShapeVariables();
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

    glClearColor(0.0, 0.0, 0.0, 0.0);		// Sets the OpenGL color when the widget is cleared, a dark blue in this case
    glShadeModel(GL_FLAT);				// Sets the flat shading model
    glEnable(GL_DEPTH_TEST);				// Enables depth testing
    glEnable(GL_CULL_FACE);				// Enables face culling
}

//-----------------------GLWidget::resizeGL-----------------------------------
void GLWidget::resizeGL(int w, int h)
{
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

void GLWidget::drawFanTest() {
    printf("Fan Test Called\n");

    drawMode = GLWidget::MOUSE;
    shapeMode = GLWidget::LINE;
    drawShape = GLWidget::FAN;
    clearShapeVariables();
}

void GLWidget::drawBowTest() {
    printf("Fan Test Called\n");

    drawMode = GLWidget::MOUSE;
    shapeMode = GLWidget::LINE;
    drawShape = GLWidget::BOW;
    clearShapeVariables();
}

void GLWidget::drawHouseTest() {
    printf("Fan House Called\n");

    drawMode = GLWidget::MOUSE;
    shapeMode = GLWidget::LINE;
    drawShape = GLWidget::HOUSE;
    clearShapeVariables();
}

void GLWidget::drawTest() {
    printf("Test Called\n");

    drawMode = GLWidget::MOUSE;
    shapeMode = GLWidget::LINE;
    drawShape = GLWidget::TEST;
    clearShapeVariables();
}

//--------------------------GLWidget::paintGL----------------------------------
void GLWidget::paintGL()
{
    QVector<QString> output;

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    if(!areShapesClear) {
        if (shapeMode == GLWidget::LINE) {
            if(clickCounter == 0 || (drawMode == GLWidget::DIALOG))
            {

                //Breenhem Algorithm
                if (drawShape == GLWidget::FAN) {
                    //Test for all 16 possible regions
                    int xaFanTest[] = {  0,   0,  0,   0,  0,   0,   0,   0,  0,  0,   0,   0,  0,  0,   0,   0,  0,   0};
                    int yaFanTest[] = {  0,   0,  0,   0,  0,   0,   0,   0,  0,  0,   0,   0,  0,  0,   0,   0,  0,   0};
                    int xbFanTest[] = {100,-100,100,-100,100,-100, 100,-100, 50,-50,  50, -50,100,100,-100,-100,  0,   0};
                    int ybFanTest[] = {100,-100,  0,   0,100,-100,-100, 100,100,100,-100,-100, 50,-50,  50, -50,100,-100};

                    for (int i = 0; i < 18; ++i)
                        DrawingAlgorithms::drawLine((xbFanTest[i] * 2) + 220, ybFanTest[i] * 2, (xaFanTest[i] * 2) + 220, yaFanTest[i] * 2);

                    for (int i = 0; i < 18; ++i)
                        DrawingAlgorithms::drawLine((xaFanTest[i] * 2) - 220, yaFanTest[i] * 2, (xbFanTest[i] * 2) - 220, ybFanTest[i] * 2);

                } else if (drawShape == GLWidget::BOW) {
                    //Bowtie
                    int xaBow[] = {100,100,120,140,140,120};
                    int yaBow[] = {100, 60, 76, 60,100, 84};
                    int xbBow[] = {100,120,140,140,120,100};
                    int ybBow[] = {60 , 76, 60,100, 84,100};
                    for (int i = 0; i < 6; ++i)
                        DrawingAlgorithms::drawLine(xaBow[i] * 2, yaBow[i] * 2, xbBow[i] * 2, ybBow[i] * 2);
                } else if (drawShape == HOUSE) {
                    int xa[] = {40,40,70,100,100,50,50,60,50,60,80,90,85};
                    int ya[] = {40,90,120,90,40,100,120,120,40,75,75,75,90};
                    int xb[] = {40,70,100,100,40,50,60,60,60,70,90,85,80};
                    int yb[] = {90,120,90,40,40,120,120,110,75,40,75,90,75};
                    for (int i = 0; i < 13; ++i)
                        DrawingAlgorithms::drawLine(xa[i] * 2, ya[i] * 2, xb[i] * 2, yb[i] * 2);
                } else if (drawShape == TEST) {
                    int xa[] = {10,-2,8,0,3,16,1,-1,1,-1,-1};
                    int ya[] = {-10,8,8,-7,-9,5,1,0,0,1,-1};
                    int xb[] = {-10,8,-2,0,16,3,1,1,-1,10,10};
                    int yb[] = {10,8,8,5,5,-9,1,10,10,-1,1};
                    for (int i = 0; i < 11; ++i)
                        DrawingAlgorithms::drawLine(xa[i], ya[i], xb[i], yb[i]);

                } else {
                    output = DrawingAlgorithms::drawLine(startX, startY, finishX, finishY);
                    //DDA Algorithm
                    //output = DrawingAlgorithms::dda(startX, startY, finishX, finishY);
                }

            }
            else if(clickCounter == 1)
            {
                //Draw first point
                glBegin(GL_POINTS);
                glVertex2i(startX, startY);
                glEnd();
            }
        }
        if(!printOnce)
        {
            printOnce = true;
            printDiag->setContents(output);
        }
    }
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

            case GLWidget::POLYLINE:
                //Starts and continues a polyline
                break;

            case GLWidget::POLYGON:
                //Starts and and continues a polygon
                break;
            }
        }
    }
    else if(e->button() == Qt::MidButton)
    {
        switch(shapeMode)
        {
        case GLWidget::POLYLINE:
            //Ends a polyline
            break;

        case GLWidget::POLYGON:
            //Ends and closes the polygon
            break;
        }
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
