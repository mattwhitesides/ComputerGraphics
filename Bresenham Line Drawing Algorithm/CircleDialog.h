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
    void valuesUpdated(int x, int y, int r);

private:
    QLineEdit *editX, *editY, *editR;


private slots:
    void hideDialog();
    void getValues();
};

#endif // CIRCLEDIALOG_H
