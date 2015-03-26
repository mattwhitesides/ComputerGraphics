/*
    MainWindow.cpp - MainWindow class implementation.
    Written by:
    Anoop Haridas
*/

#include "MainWindow.h"
#include "Window.h"
//#include "GLWidget.h"

#include <QtGui>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMenu>
#include <QMainWindow>
#include <QMenuBar>
#include <QStatusBar>
#include <QApplication>
#include <QLabel>
#include <QString>
#include <QToolBar>

MainWindow::MainWindow() 
{
    //Create widget to hold everything else in this widget
    //QWidget* w = new QWidget;
    //setCentralWidget(w);

    //QVBoxLayout* mainLayout = new QVBoxLayout;
    //QHBoxLayout* container = new QHBoxLayout;

    // Create the OpenGL window
    //glWindow = new GLWidget(w);
    //connect(glWindow, SIGNAL(mouseMoved(int, int)), this, SLOT(updateStatusLabel(int, int)));

    //container->addWidget(glWindow);
    //w->setLayout(container);
    //mainLayout->addWidget(w);
    //setLayout(mainLayout);

    childWindow = new Window(this);
    setCentralWidget(childWindow);

    //Creates the actions fired when a menu item is selected
    createActions();

    //Creates all the menus
    createMenus();

    //Creates the toolbar
    createToolBar();

    //setCentralWidget(new Window(this));

    statusBar()->showMessage(tr("X: ???, Y: ???"));

    setWindowTitle(tr("CS 4610/7610 Assignment 1 Framework"));
    setMinimumSize(100, 100);
    resize(720, 540);
}

void MainWindow::updateStatusLabel(int x, int y)
{
    QString statString = QString("X: ") + QString::number(x) + QString(" Y: ") + QString::number(y);
    statusBar()->showMessage(statString);
}

/*<<<<<<<<<<<<<<<<<<<<<<createActions>>>>>>>>>>>>>>>>>>>>>>>>>>>>*/
void MainWindow::createActions()
{
    printAct = new QAction(tr("Print"), this);
    printAct->setStatusTip(tr("Print the output"));
    //printAct->setCheckable(true);
    //printAct->setChecked(true);
    connect(printAct, SIGNAL(triggered()), childWindow, SIGNAL(printCallFromMW()));
    //connect(printAct, SIGNAL(triggered()), glWindow, SLOT(togglePrintDialog()));

    exitAct = new QAction(tr("E&xit"), this);
    exitAct->setShortcut(tr("Ctrl+Q"));
    exitAct->setStatusTip(tr("Exit the application"));
    connect(exitAct, SIGNAL(triggered()), this, SLOT(close()));

    colorAct = new QAction(tr("Set Color"), this);
    colorAct->setStatusTip(tr("Set the current drawing color"));
    connect(colorAct, SIGNAL(triggered()), childWindow, SIGNAL(chooseColorFromMW()));
    //connect(colorAct, SIGNAL(triggered()), glWindow, SLOT(chooseColor()));

    diagLineAct = new QAction(tr("Line"), this);
    diagLineAct->setStatusTip(tr("Open dialog for line drawing"));
    connect(diagLineAct, SIGNAL(triggered()), childWindow, SIGNAL(drawDialogLineFromMW()));
    //connect(diagLineAct, SIGNAL(triggered()), glWindow, SLOT(drawDialogLine()));

    diagCircleAct = new QAction(tr("Circle/Ellipse"), this);
    diagCircleAct->setStatusTip(tr("Open dialog for circle drawing"));
    connect(diagCircleAct, SIGNAL(triggered()), childWindow, SIGNAL(drawDialogCircleFromMW()));

    mouseLineAct  = new QAction(tr("Line"), this);
    mouseLineAct->setStatusTip(tr("Activate mouse line drawing"));
    connect(mouseLineAct, SIGNAL(triggered()), childWindow, SIGNAL(drawMouseLineFromMW()));
    //connect(mouseLineAct, SIGNAL(triggered()), glWindow, SLOT(drawMouseLine()));

    mousePolylineAct = new QAction(tr("Draw"), this);
    mousePolylineAct->setStatusTip(tr("Draw Test To Screen"));
    connect(mousePolylineAct, SIGNAL(triggered()), childWindow, SIGNAL(drawMousePolyLineFromMW()));
    //connect(mousePolylineAct, SIGNAL(triggered()), glWindow, SLOT(drawMousePolyline()));

    //    mousePolygonAct = new QAction(tr("Polygon"), this);
    //    mousePolygonAct->setStatusTip(tr("Activate mouse polygon drawing"));
    //    connect(mousePolygonAct, SIGNAL(triggered()), childWindow, SIGNAL(drawMousePolygonFromMW()));
    //    //connect(mousePolygonAct, SIGNAL(triggered()), glWindow, SLOT(drawMousePolygon()));

    //    bowTieAct = new QAction(tr("BowTie"), this);
    //    bowTieAct->setStatusTip(tr("Draw a bowtie on screen (Note: You have to click twice on the screen)"));
    //    connect(bowTieAct, SIGNAL(triggered()), childWindow, SIGNAL(drawBowTestFromMW()));

    //    houseAct = new QAction(tr("House"), this);
    //    houseAct->setStatusTip(tr("Draw a House on screen (Note: You have to click twice on the screen)"));
    //    connect(houseAct, SIGNAL(triggered()), childWindow, SIGNAL(drawHouseTestFromMW()));

    //    fanAct = new QAction(tr("Fan"), this);
    //    fanAct->setStatusTip(tr("Draw fans on screen (Note: You have to click twice on the screen)"));
    //    connect(fanAct, SIGNAL(triggered()), childWindow, SIGNAL(drawFanTestFromMW()));

    //    testAct = new QAction(tr("TestLines"), this);
    //    testAct->setStatusTip(tr("Draw a test image on screen (Note: You have to click twice on the screen)"));
    //    connect(testAct, SIGNAL(triggered()), childWindow, SIGNAL(drawTestFromMW()));

    //    drawCircleAct = new QAction(tr("Circle"), this);
    //    drawCircleAct->setStatusTip(tr("Draw a circle or ellipse on screen"));
    //    connect(drawCircleAct, SIGNAL(triggered()), childWindow, SIGNAL(drawCircleFromMW()));

    scanFillTestAct = new QAction(tr("GoraudShadingTriangle"), this);
    scanFillTestAct->setStatusTip(tr("Draw the first test scanfill algorithem"));
    connect(scanFillTestAct, SIGNAL(triggered()), childWindow, SIGNAL(drawScanFillTestFromMW()));
    //connect(mousePolylineAct, SIGNAL(triggered()), glWindow, SLOT(drawScanFillTestFromMW()));

    scanFillTest2Act = new QAction(tr("Polygon8"), this);
    scanFillTest2Act->setStatusTip(tr("Draw the second test scanfill algorithem"));
    connect(scanFillTest2Act, SIGNAL(triggered()), childWindow, SIGNAL(drawScanFillTest2FromMW()));
    //connect(mousePolylineAct, SIGNAL(triggered()), glWindow, SLOT(drawScanFillTestFromMW()));

    scanFillTest3Act = new QAction(tr("Polygon9"), this);
    scanFillTest3Act->setStatusTip(tr("Draw the third test scanfill algorithem"));
    connect(scanFillTest3Act, SIGNAL(triggered()), childWindow, SIGNAL(drawScanFillTest3FromMW()));
    //connect(mousePolylineAct, SIGNAL(triggered()), glWindow, SLOT(drawScanFillTestFromMW()));

    scanFillTest4Act = new QAction(tr("OtherPolygons"), this);
    scanFillTest4Act->setStatusTip(tr("Draw the other test polygons using scanfill"));
    connect(scanFillTest4Act, SIGNAL(triggered()), childWindow, SIGNAL(drawScanFillTest4FromMW()));
    //connect(mousePolylineAct, SIGNAL(triggered()), glWindow, SLOT(drawScanFillTestFromMW()));

    enableSETAct = new QAction(tr("EnableSETPrint"), this);
    enableSETAct->setStatusTip(tr("Prints out the Sorted Edge Table to console"));
    connect(enableSETAct, SIGNAL(triggered()), childWindow, SIGNAL(enableSETActFromMW()));

    enableAETAct = new QAction(tr("EnableAETPrinting"), this);
    enableAETAct->setStatusTip(tr("Prints out the Active Edge Table to console"));
    connect(enableAETAct, SIGNAL(triggered()), childWindow, SIGNAL(enableAETActFromMW()));
    //connect(mousePolylineAct, SIGNAL(triggered()), glWindow, SLOT(drawScanFillTestFromMW()));
}

/*<<<<<<<<<<<<<<<<<<<<<<createMenus>>>>>>>>>>>>>>>>>>>>>>>>>>>>>*/
void MainWindow::createMenus()
{
    //The file menu
    fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(printAct);

    fileMenu->addSeparator();
    fileMenu->addAction(exitAct);

    //The options menu
    optionsMenu = menuBar()->addMenu(tr("&Options"));
    optionsMenu->addAction(colorAct);

    //The graphics menu
    graphicsMenu = menuBar()->addMenu(tr("&Graphics"));
    drawMenu = graphicsMenu->addMenu(tr("&Draw"));
    //    drawMenu->addAction(diagLineAct);
    //    drawMenu->addAction(diagCircleAct);

    //Test Menu
    //    testMenu = menuBar()->addMenu(tr("&Test"));
    //    houseMenu = testMenu->addMenu(tr("&House"));
    //    houseMenu->addAction(houseAct);

    //The rasterization menu
    rasterizeMenu = graphicsMenu->addMenu(tr("&Rasterize"));

    //The transform menu
    transformMenu = graphicsMenu->addMenu(tr("&Transform"));

}

/*<<<<<<<<<<<<<<<<<<<<<<createToolBar>>>>>>>>>>>>>>>>>>>>>>>>>>>>>*/
void MainWindow::createToolBar()
{
    interactToolBar = addToolBar(tr("Interact"));
    //    interactToolBar->addAction(mouseLineAct);
    interactToolBar->addAction(mousePolylineAct);
    //    interactToolBar->addAction(drawCircleAct);
    //    interactToolBar->addAction(mousePolygonAct);
    //    interactToolBar->addAction(bowTieAct);
    //    interactToolBar->addAction(houseAct);
    //    interactToolBar->addAction(testAct);
    //    interactToolBar->addAction(fanAct);
    interactToolBar->addAction(scanFillTest2Act);
    interactToolBar->addAction(scanFillTest3Act);
    interactToolBar->addAction(scanFillTest4Act);
    interactToolBar->addAction(scanFillTestAct);
    interactToolBar->addAction(enableAETAct);
    //interactToolBar->addAction(enableSETAct);
}
