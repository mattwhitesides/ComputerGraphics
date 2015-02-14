#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QGLWidget>

class GLWidget : public QGLWidget
{
    Q_OBJECT

public:
    explicit GLWidget(QWidget* parent = 0);
    ~GLWidget();

    void resizeGL(int w, int h);
    void initializeGL();
    void paintGL();
};

#endif // GLWIDGET_H
