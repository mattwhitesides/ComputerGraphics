#ifndef CIRCLEDIALOG_H
#define CIRCLEDIALOG_H

#include <QLineEdit>
#include <QDialog>

class CircleDialog : public QDialog {

    Q_OBJECT

public:
    CircleDialog(QWidget *parent = 0);
    ~CircleDialog();

signals:
    void valuesUpdated(int x, int y, int rX,  int rY);

private:
    QLineEdit *editX, *editY, *editXR, *editYR;


private slots:
    void hideDialog();
    void getValues();
};

#endif // CIRCLEDIALOG_H
