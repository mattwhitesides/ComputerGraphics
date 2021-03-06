/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.4.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "glwidget.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionColor;
    QAction *actionColor_2;
    QAction *actionWidth;
    QWidget *centralWidget;
    QHBoxLayout *horizontalLayout;
    GLWidget *widget;
    QHBoxLayout *horizontalLayout_2;
    QVBoxLayout *verticalLayout;
    QLineEdit *x1LineEdit;
    QLineEdit *y1LineEdit;
    QLineEdit *x2LineEdit;
    QLineEdit *y2LineEdit;
    QPushButton *updateBtn;
    QMenuBar *menuBar;
    QMenu *menuPrefrences;
    QMenu *menuDraw;
    QMenu *menuCanvas;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->setWindowModality(Qt::ApplicationModal);
        MainWindow->resize(880, 546);
        actionColor = new QAction(MainWindow);
        actionColor->setObjectName(QStringLiteral("actionColor"));
        actionColor_2 = new QAction(MainWindow);
        actionColor_2->setObjectName(QStringLiteral("actionColor_2"));
        actionWidth = new QAction(MainWindow);
        actionWidth->setObjectName(QStringLiteral("actionWidth"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        horizontalLayout = new QHBoxLayout(centralWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        widget = new GLWidget(centralWidget);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setMinimumSize(QSize(500, 500));
        horizontalLayout_2 = new QHBoxLayout(widget);
        horizontalLayout_2->setSpacing(0);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(12, 0, 0, 0);

        horizontalLayout->addWidget(widget);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        x1LineEdit = new QLineEdit(centralWidget);
        x1LineEdit->setObjectName(QStringLiteral("x1LineEdit"));
        x1LineEdit->setMaximumSize(QSize(200, 16777215));

        verticalLayout->addWidget(x1LineEdit);

        y1LineEdit = new QLineEdit(centralWidget);
        y1LineEdit->setObjectName(QStringLiteral("y1LineEdit"));
        y1LineEdit->setMinimumSize(QSize(0, 0));
        y1LineEdit->setMaximumSize(QSize(200, 16777215));

        verticalLayout->addWidget(y1LineEdit);

        x2LineEdit = new QLineEdit(centralWidget);
        x2LineEdit->setObjectName(QStringLiteral("x2LineEdit"));
        x2LineEdit->setMaximumSize(QSize(200, 16777215));

        verticalLayout->addWidget(x2LineEdit);

        y2LineEdit = new QLineEdit(centralWidget);
        y2LineEdit->setObjectName(QStringLiteral("y2LineEdit"));
        y2LineEdit->setMaximumSize(QSize(200, 16777215));

        verticalLayout->addWidget(y2LineEdit);

        updateBtn = new QPushButton(centralWidget);
        updateBtn->setObjectName(QStringLiteral("updateBtn"));
        updateBtn->setMaximumSize(QSize(200, 16777215));

        verticalLayout->addWidget(updateBtn);


        horizontalLayout->addLayout(verticalLayout);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 880, 22));
        menuPrefrences = new QMenu(menuBar);
        menuPrefrences->setObjectName(QStringLiteral("menuPrefrences"));
        menuDraw = new QMenu(menuPrefrences);
        menuDraw->setObjectName(QStringLiteral("menuDraw"));
        menuCanvas = new QMenu(menuPrefrences);
        menuCanvas->setObjectName(QStringLiteral("menuCanvas"));
        MainWindow->setMenuBar(menuBar);

        menuBar->addAction(menuPrefrences->menuAction());
        menuPrefrences->addAction(menuDraw->menuAction());
        menuPrefrences->addAction(menuCanvas->menuAction());
        menuDraw->addAction(actionColor);
        menuDraw->addAction(actionWidth);
        menuCanvas->addAction(actionColor_2);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        actionColor->setText(QApplication::translate("MainWindow", "Color", 0));
        actionColor_2->setText(QApplication::translate("MainWindow", "Color", 0));
        actionWidth->setText(QApplication::translate("MainWindow", "Width", 0));
        x1LineEdit->setText(QApplication::translate("MainWindow", "-200", 0));
        y1LineEdit->setText(QApplication::translate("MainWindow", "-200", 0));
        x2LineEdit->setText(QApplication::translate("MainWindow", "200", 0));
        y2LineEdit->setText(QApplication::translate("MainWindow", "200", 0));
        updateBtn->setText(QApplication::translate("MainWindow", "Update ", 0));
        menuPrefrences->setTitle(QApplication::translate("MainWindow", "Prefrences", 0));
        menuDraw->setTitle(QApplication::translate("MainWindow", "Line", 0));
        menuCanvas->setTitle(QApplication::translate("MainWindow", "Canvas", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
