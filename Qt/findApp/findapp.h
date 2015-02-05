#ifndef FINDAPP_H
#define FINDAPP_H

#include <QWidget>

namespace Ui {
class FindApp;
}

class FindApp : public QWidget
{
    Q_OBJECT

public:
    explicit FindApp(QWidget *parent = 0);
    ~FindApp();

private slots:
    void on_goButton_clicked();

private:
    Ui::FindApp *ui;
};

#endif // FINDAPP_H
