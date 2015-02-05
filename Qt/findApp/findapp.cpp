#include "findapp.h"
#include "ui_findapp.h"

FindApp::FindApp(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FindApp)
{
    ui->setupUi(this);
}

FindApp::~FindApp()
{
    delete ui;
}

void FindApp::on_goButton_clicked()
{

}
