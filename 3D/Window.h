#ifndef WINDOW_H
#define WINDOW_H

#include <QWidget>

class GLWidget;
class MainWindow;

class Window : public QWidget
{
    Q_OBJECT

public:

    Window(MainWindow *mw);

signals:

	void printCallFromMW();
	void chooseColorFromMW();
	void drawDialogLineFromMW();
	void drawMouseLineFromMW();
	void drawMousePolygonFromMW();
    void drawCubeFromMW();
    void drawTetraFromMW();
    void drawObjFromMW();

private:
	
	GLWidget* glWindow;
	MainWindow* mainWindow;
};

#endif
