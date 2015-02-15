#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "Drawings.h"
#include <QString>
#include <QTextStream>

GLWidget* glWidget;
Drawings* drawings;

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    glWidget = new GLWidget;
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::on_updateBtn_clicked()
{

}

void MainWindow::on_updateBtn_released()
{
   glWidget->updateBtnClicked(
    ui->x1LineEdit->text().toInt(),
    ui->y1LineEdit->text().toInt(),
    ui->x2LineEdit->text().toInt(),
    ui->y2LineEdit->text().toInt()
    );
}
