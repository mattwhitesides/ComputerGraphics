#include <QApplication>
#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>
#include <QSlider>
#include <QSpinBox>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    QWidget *mainWindow = new QWidget;
    mainWindow->setWindowTitle("How many stuff?");

    QSpinBox *spinner = new QSpinBox;
    QSlider *slider = new QSlider(Qt::Horizontal);
    spinner->setRange(1,50);
    slider->setRange(1,50);

    //First Param which widget do you want to do somting to
    //second what the user does
    //third what to execute the fourth param upon
    QObject::connect(spinner, SIGNAL(valueChanged(int)), slider, SLOT(setValue(int)));
    //Sync both
    QObject::connect(slider, SIGNAL(valueChanged(int)), spinner, SLOT(setValue(int)));

    //Set initial values
    spinner->setValue(10);

    //Create a layout
    //QHBoxLayout Horizonal box layout
    QHBoxLayout *layout = new QHBoxLayout;
    layout->addWidget(slider);
    layout->addWidget(spinner);
    mainWindow->setLayout(layout);
    mainWindow->show();

    return a.exec();
}


//QLabel *label = new QLabel("Hello");
//label->show();

//QPushButton *button = new QPushButton("Button Pressed");
//button->show();
//QObject::connect(button, SIGNAL(clicked()), &a, SLOT(quit()));
