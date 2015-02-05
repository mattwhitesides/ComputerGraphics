#include "findapp.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    FindApp w;
    w.show();

    return a.exec();
}
