#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QGLWidget>
#include <qgl.h>

class GLWidget : public QGLWidget
{
    Q_OBJECT

public:
    explicit GLWidget(QWidget* parent = 0);
    ~GLWidget();

    void resizeGL(int w, int h);
    void initializeGL();
    void paintGL();

    void updateBtnClicked(int x1, int y1, int x2, int y2);
    void clearVariables();

private:
    int x1;
    int x2;
    int y1;
    int y2;
};

#endif // GLWIDGET_H
