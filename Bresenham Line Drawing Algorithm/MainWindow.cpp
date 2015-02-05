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
    resize(500, 500);
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

	mouseLineAct  = new QAction(tr("Line"), this);
	mouseLineAct->setStatusTip(tr("Activate mouse line drawing"));
    connect(mouseLineAct, SIGNAL(triggered()), childWindow, SIGNAL(drawMouseLineFromMW()));
	//connect(mouseLineAct, SIGNAL(triggered()), glWindow, SLOT(drawMouseLine()));

	mousePolylineAct = new QAction(tr("Polyline"), this);
    mousePolylineAct->setStatusTip(tr("Activate mouse polyline drawing"));
    connect(mousePolylineAct, SIGNAL(triggered()), childWindow, SIGNAL(drawMousePolyLineFromMW()));
	//connect(mousePolylineAct, SIGNAL(triggered()), glWindow, SLOT(drawMousePolyline()));

    mousePolygonAct = new QAction(tr("Polygon"), this);
    mousePolygonAct->setStatusTip(tr("Activate mouse polygon drawing"));
    connect(mousePolygonAct, SIGNAL(triggered()), childWindow, SIGNAL(drawMousePolygonFromMW()));
	//connect(mousePolygonAct, SIGNAL(triggered()), glWindow, SLOT(drawMousePolygon()));

    bowTieAct = new QAction(tr("BowTie"), this);
    bowTieAct->setStatusTip(tr("Draw a bowtie on screen"));
    connect(bowTieAct, SIGNAL(triggered()), childWindow, SIGNAL(drawMousePolygonFromMW()));

    houseAct = new QAction(tr("House"), this);
    houseAct->setStatusTip(tr("Draw a House on screen"));
    connect(houseAct, SIGNAL(triggered()), childWindow, SIGNAL(drawMousePolygonFromMW()));

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
	drawMenu->addAction(diagLineAct);
		
	//The rasterization menu
    rasterizeMenu = graphicsMenu->addMenu(tr("&Rasterize"));
	
	//The transform menu
	transformMenu = graphicsMenu->addMenu(tr("&Transform"));
	
  }

  /*<<<<<<<<<<<<<<<<<<<<<<createToolBar>>>>>>>>>>>>>>>>>>>>>>>>>>>>>*/
  void MainWindow::createToolBar()
  {
    interactToolBar = addToolBar(tr("Interact"));
	interactToolBar->addAction(mouseLineAct);
    //interactToolBar->addAction(mousePolylineAct);
    //interactToolBar->addAction(mousePolygonAct);
    interactToolBar->addAction(bowTieAct);
    interactToolBar->addAction(houseAct);
  }
