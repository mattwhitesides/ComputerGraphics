#include "mainwindow.h"
#include "ui_mainwindow.h"

GLWidget* glWidget;

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    glWidget = new GLWidget;
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::on_updateBtn_clicked()
{
    glWidget->paintGL();
}
