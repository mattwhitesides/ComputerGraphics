/*
    GLWidget.cpp - GLWidget class implementation.
    Class for widget doing OpenGL drawing for CS 4610/7610.
    Written by:
    Anoop Haridas & Matt Whitesides
*/

#include "GLWidget.h"
#include "LineDialog.h"
#include "CircleDialog.h"

#include "PrintDialog.h"
#include "DrawingAlgorithms.h"
#include "ScanlineFill.h"

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
const int GLWidget::SCANFILL = 6;
const int GLWidget::SHADING = 10;

const int GLWidget::FAN = 6;
const int GLWidget::HOUSE = 7;
const int GLWidget::BOW = 8;
const int GLWidget::TEST = 9;

const int GLWidget::MULTI = 11;
const int GLWidget::GSHADE = 12;

QList<Coord> polyLineList;
QList<Coord> scanFillEdgeList;
ScanlineFill* filler = NULL;
ScanlineFill* fillAry[10];

//------------------------GLWidget::GLWidget-------------------------
GLWidget::GLWidget(QWidget *parent) : QGLWidget(parent)
{
    //Initialize all the variables
    lineColor[0] = 255;
    lineColor[1] = 255;
    lineColor[2] = 255;

    printAET = false;

    clickCounter = 0;
    drawMode = shapeMode = scanMode = 0;

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

    //Input that comes up when selecting Graphics->Draw->Circle
    circleDiag = new CircleDialog(this);
    circleDiag->setModal(false);
    circleDiag->setVisible(false);
    connect(circleDiag, SIGNAL(valuesUpdated(int, int, int, int)), this, SLOT(updateDialogCircle(int, int, int, int)));

    // The following code allows for animated graphics by attempting to refresh the screen at 50fps.
    //	STEP 1: Create a timer
    QTimer *timer = new QTimer(this);
    //	STEP 2: Update the GL graphics every time the timer is fired off
    connect(timer, SIGNAL(timeout()), this, SLOT(updateGL()));
    //	STEP 3: Start the timer to go off every 20 milliseconds.
    timer->start(200);

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

//------------------------GLWidget::drawDialogCircle--------------------------
void GLWidget::drawDialogCircle()
{
    drawMode = GLWidget::DIALOG;
    shapeMode = GLWidget::CIRCLE;
    clearShapeVariables();
    circleDiag->show();
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

/*-----------------------GLWidget::updateDialogCircle-------------------------*/
void GLWidget::updateDialogCircle(int x, int y, int rX, int rY)
{
    drawMode = GLWidget::DIALOG;  //Set the drawing mode to dialog
    shapeMode = GLWidget::CIRCLE;   //Set shape to LINE
    clearShapeVariables();        //Clear the state variables

    //Set the line variables
    startX = x;
    startY = y;
    radiusX = rX;
    radiusY = rY;

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

/*-------------------------GLWidget::drawCircle-----------------------*/
void GLWidget::drawCircle()
{
    drawMode = GLWidget::MOUSE;
    shapeMode = GLWidget::CIRCLE;
    clearShapeVariables();
}

void GLWidget::enableAETAct()
{
    if (!printAET) {
        printAET = true;
        printf("Enabled Active Edge Table printing.\n");
    } else {
        printAET = false;
        printf("Disabled Active Edge Table Printing.\n");
    }
}

void GLWidget::enableSETAct()
{

}

void GLWidget::drawScanFillTest()
{
    drawMode = GLWidget::MOUSE;
    shapeMode = GLWidget::SCANFILL;
    scanMode = GLWidget::GSHADE;
    clickCounter++;
    clearShapeVariables();
    Coord pp[] = {{120,120},{280,320},{280,320},{40,240},{40,240},{120,120}};
    filler = new ScanlineFill(pp, 6);
}

void GLWidget::drawScanFillTest2()
{
    drawMode = GLWidget::MOUSE;
    shapeMode = GLWidget::SCANFILL;
    scanMode = GLWidget::SHADING;
    clickCounter++;
    clearShapeVariables();
    Coord polygon8[] =  { {0, 0}, {35, 0}, {35, 40}, {0, 40}, {0, 10},{25, 10}, {25, 30}, {10, 30}, {10, 20}, {15, 20},{15, 25}, {20, 25}, {20, 15}, {5, 15}, {5, 35}, {30, 35}, {30, 5}, {0, 5} };
    filler = new ScanlineFill(polygon8, 18);
}

void GLWidget::drawScanFillTest3()
{
    drawMode = GLWidget::MOUSE;
    shapeMode = GLWidget::SCANFILL;
    scanMode = GLWidget::SHADING;
    clickCounter++;
    clearShapeVariables();
    Coord polygon9[] = { {0, 0}, {15, 20}, {30, 0}, {45, 20}, {60, 0}, {75, 20}, {90, 0}, {90, 30}, {70, 30}, {60, 15},{50, 30}, {40, 30}, {30, 15}, {20, 30}, {0, 30}, {0,0}};
    filler = new ScanlineFill(polygon9, 16);
}

void GLWidget::drawScanFillTest4()
{
    drawMode = GLWidget::MOUSE;
    shapeMode = GLWidget::SCANFILL;
    scanMode = GLWidget::MULTI;
    clickCounter++;
    clearShapeVariables();

    Coord polyAry1[] = { {0, 30}, {10, 10}, {50, 10}, {80, 40}, {100, 40}, {110, 50}, {110, 115}, {130, 120}, {130, 130}, {100, 135}, {130, 140}, {130, 150}, {110, 160}, {80, 160}, {70, 150}, {70, 130}, {80, 120}, {70, 110}, {60, 60}, {40, 30}, {30, 20}, {10, 20} };
    Coord polyAry2[] = { {80, 100}, {90, 90}, {100, 90}, {130, 80}, {140, 90}, {160, 90}, {150, 95}, {160, 100}, {150, 100}, {155, 110}, {145, 100}, {140, 110}, {140, 100}, {130, 90}, {110, 110}, {90, 110} };
    Coord polyAry3[] = { {-80, -60}, {-80, -40}, {-90, -30}, {-90, -20}, {-80, -10}, {-80, -5}, {-90, -0}, {-120, -0}, {-100, -10}, {-100, -20}, {-120, -40}, {-110, -60}, {-100, -70}, {-90, -70} };
    Coord polyAry4[] = { {87, 150}, {90, 147}, {96, 147}, {101, 150}, {96, 152}, {90, 152} };
    Coord polyAry5[] = { {125,275}, {375,275}, { 150, 150}, {250, 350}, {350, 150} };
    Coord polyAry6[] = { {9*4,5*4}, {14*4,5*4}, {14*4,11*4}, {22*4,11*4}, {27*4,16*4}, {20*4,25*4}, {13*4,25*4}, {13*4,20*4}, {8*4,20*4}, {8*4,16*4}, {4*4,16*4}, {4*4,9*4} };
    Coord polyAry7[] = { {2,3}, {7,1}, {13,5}, {13,11}, {7,7}, {2,9} };
    Coord polyAry8[] =  { {0, 0}, {35, 0}, {35, 40}, {0, 40}, {0, 10},{25, 10}, {25, 30}, {10, 30}, {10, 20}, {15, 20},{15, 25}, {20, 25}, {20, 15}, {5, 15}, {5, 35}, {30, 35}, {30, 5}, {0, 5} };
    Coord polyAry9[] = { {0, 0}, {15, 20}, {30, 0}, {45, 20}, {60, 0}, {75, 20}, {90, 0}, {90, 30}, {70, 30}, {60, 15},{50, 30}, {40, 30}, {30, 15}, {20, 30}, {0, 30}, {0,0}};

    fillAry[0] = new ScanlineFill(polyAry1, 22);
    fillAry[1] = new ScanlineFill(polyAry2, 16);
    fillAry[2] = new ScanlineFill(polyAry3, 14);
    fillAry[3] = new ScanlineFill(polyAry4, 6);
    fillAry[4] = new ScanlineFill(polyAry5, 5);
    fillAry[5] = new ScanlineFill(polyAry6, 12);
    fillAry[6] = new ScanlineFill(polyAry7, 6);
    fillAry[7] = new ScanlineFill(polyAry8, 18);
    fillAry[8] = new ScanlineFill(polyAry9, 16);
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

    if(!areShapesClear)
    {
        switch(shapeMode)
        {
        case GLWidget::SCANFILL:
            if (filler) filler->scanLineFillAlgorithm();
            else printf("Filler not initialized\n");
            break;
        case GLWidget::LINE:
            if(clickCounter == 0 || (drawMode == GLWidget::DIALOG))
            {
                //Breenhem Algorithm
                output = DrawingAlgorithms::drawLine(startX * 2, startY * 2, finishX * 2, finishY * 2);
            }
            else if(clickCounter == 1)
            {
                //Draw first point
                glBegin(GL_POINTS);
                glVertex2i(startX, startY);
                glEnd();
            }
            break;

        case GLWidget::POLYLINE:
            if (scanMode == GLWidget::MULTI) {
                fillAry[0]->scanLineFillAlgorithm(printAET);
                fillAry[1]->scanLineFillAlgorithm(printAET);
                fillAry[2]->scanLineFillAlgorithm(printAET);
                fillAry[3]->scanLineFillAlgorithm(printAET);
                fillAry[4]->scanLineFillAlgorithm(printAET);
                fillAry[5]->scanLineFillAlgorithm(printAET);
                fillAry[6]->scanLineFillAlgorithm(printAET);
                fillAry[7]->scanLineFillAlgorithm(printAET);
                fillAry[8]->scanLineFillAlgorithm(printAET);
            } else if (scanMode == GLWidget::GSHADE && filler) {
                filler->goraudShading();
            } else if (filler && scanMode == GLWidget::SHADING) filler->scanLineFillAlgorithm(printAET);

            //            output = DrawingAlgorithms::drawPolyLine(polyLineList);
            break;

        case GLWidget::CIRCLE:
            if(clickCounter == 0 || (drawMode == GLWidget::DIALOG))
            {
                //Circle Algorithm called if radiuses are equal otherwise ellipse is called
                if (radiusX == radiusY || radiusY == 0) {
                    if (drawMode == GLWidget::MOUSE) radiusX = sqrt(pow((finishX - startX),2) + pow((finishY - startY),2));
                    output = DrawingAlgorithms::drawCircle(startX * 2, startY * 2, radiusX * 2);
                } else {
                    output = DrawingAlgorithms::drawEllipse(startX * 2, startY * 2, radiusX * 2, radiusY * 2);
                }
            }
            else if(clickCounter == 1)
            {
                //Draw first point
                glBegin(GL_POINTS);
                glVertex2i(startX, startY);
                glEnd();
            }
            break;

        default: break;
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
            case GLWidget::CIRCLE:
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
                if (clickCounter > 0) areShapesClear = false;
                ++clickCounter;
                //                startX = e->x() - width()/2;      // Get the X mouse position and translate so (0,0) is screen center
                //                startY = height()/2 - e->y();     // Get the Y mouse position and translate so (0,0) is screen center

                //                printf("Adding to polyline list: (%d,%d).\n",startX,startY);
                //                newCoord.x = startX * 2;
                //                newCoord.y = startY * 2;
                //                polyLineList.append(newCoord);
                break;
            case GLWidget::SCANFILL:
                //Coord polygon8[] = { {0, 0}, {35, 0}, {35, 40}, {0, 40}, {0, 10}, {25, 10}, {25, 30}, {10, 30}, {10, 20}, {15, 20}, {15, 25}, {20, 25}, {20, 15}, {5, 15}, {5, 35}, {30, 35}, {30, 5}, {0, 5} };
                //filler = new ScanlineFill(polygon8, 18);

                //Coord polygon9[] = { {0, 0}, {15, 20}, {30, 0}, {45, 20}, {60, 0}, {75, 20}, {90, 0}, {90, 30}, {70, 30}, {60, 15},{50, 30}, {40, 30}, {30, 15}, {20, 30}, {0, 30},  {0, 0}};
                //filler = new ScanlineFill(polygon9, 16);

                //Coord pp[] = {{200,100},{300,500},{300,500},{600,600},{600,600},{300,800},{300,800},{0,400},{0,400},{200,100}};

                //                Coord pp[] = {{20,10},{30,50},{30,50},{60,60},{60,60},{30,80},{30,80},{0,40},{0,40},{20,10}};
                //                filler = new ScanlineFill(pp, 10);

                //Coord pp[] = {{0,0},{5,5},{5,5},{-5,-5},{-5,-5},{0,0}};
                //Coord pp[] = {{0,0},{50,50},{50,50},{-50,-50},{-50,-50},{0,0}};
                //Coord pp[] = {{120,120},{280,320},{280,320},{40,240},{40,240},{120,120}};
                //filler = new ScanlineFill(polygon8, 6);
                //filler->printBucketContents();
                //filler->printBucketContents();
                //filler->scanLineFillAlgorithm();
                break;
            }
        }
    }
    else if(e->button() == Qt::RightButton)
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        switch(shapeMode)
        {
        case GLWidget::POLYLINE:
            clearShapeVariables();
            clickCounter = 0;
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

    polyLineList.clear();
    scanFillEdgeList.clear();
}
