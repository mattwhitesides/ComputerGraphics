/*
    CircleDialog.cpp - CircleDialog class implementation.
    Dialog for circle startpoint input and management.
    Written by:
    Anoop Haridas
    Matthew Whitesides

*/
#include "CircleDialog.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLabel>


//The dialog box where the user enters their x and y values
CircleDialog::CircleDialog(QWidget *parent) : QDialog(parent) {

    //This code builds a dialog box with 2 buttons and a set of labelled
    //lineEdits (text boxes).  It also connects the action of pushing
    //the buttons to the code (ie. slots) handling the outcome

    printf("Initialized circle dialog\n");

    //Make two push buttons
    QPushButton *drawButton, *hideButton;

    drawButton = new QPushButton("Draw", this);
    hideButton = new QPushButton("Hide", this);

    //When the draw buton is clicked the getValues SLOT is called
    connect(drawButton, SIGNAL(clicked()), this, SLOT(getValues()));

    //When the hide button is clicked the hideDialog SLOT is called
    connect(hideButton, SIGNAL(clicked()), this, SLOT(hideDialog()));

    //Create a set of labels
    QLabel *labelX, *labelY, *labelXR, *labelYR;
    labelX = new QLabel("X:", this);
    labelY = new QLabel("Y:", this);
    labelXR = new QLabel("X Radius:", this);
    labelYR = new QLabel("Y Radius:", this);

    //Create a set of LineEdits
    editX = new QLineEdit(this);
    editY = new QLineEdit(this);
    editXR = new QLineEdit(this);
    editYR = new QLineEdit(this);

    //The following code is used to layout the buttons, labels and line edits.

    //The QVBoxLayout is like an invisible container for stacking GUI objects vertically
    QVBoxLayout *vLay = new QVBoxLayout(this);

    //The QHBoxLayout is similar but stacks them horizontally
    QHBoxLayout *h1 = new QHBoxLayout();
    h1->addSpacing(10);			 //Add space between widget
    h1->addWidget(labelX);		 //Add label
    h1->addWidget(editX,5);	 //Add lineEdit

    QHBoxLayout *h2 = new QHBoxLayout();
    h2->addSpacing(10);
    h2->addWidget(labelY);
    h2->addWidget(editY,5);

    QHBoxLayout *h3 = new QHBoxLayout();
    h3->addSpacing(10);
    h3->addWidget(labelXR);
    h3->addWidget(editXR,5);

    QHBoxLayout *h4 = new QHBoxLayout();
    h3->addSpacing(10);
    h3->addWidget(labelYR);
    h3->addWidget(editYR,5);

    QHBoxLayout *h5 = new QHBoxLayout();
    h4->addSpacing(10);
    h4->addWidget(drawButton);  //Add draw button
    h4->addStretch(5);
    h4->addWidget(hideButton);   //Add hide button
    h4->addSpacing(10);

    //Add all the horizontal layouts we created to the vertical layout
    vLay->addLayout(h1);
    vLay->addLayout(h2);
    vLay->addLayout(h3);
    vLay->addLayout(h4);
    vLay->addLayout(h5);
  }

CircleDialog::~CircleDialog(){
}

void CircleDialog::hideDialog(){
    hide();
}

void CircleDialog::getValues(){
   //Whenever then draw button is pushed this signal is called
   emit valuesUpdated(editX->text().toInt(), editY->text().toInt(), editXR->text().toInt(), editYR->text().toInt());
}
