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
	void drawMousePolyLineFromMW();
	void drawMousePolygonFromMW();
    void drawFanTestFromMW();
    void drawHouseTestFromMW();
    void drawBowTestFromMW();
    void drawTestFromMW();
    void drawCircleFromMW();
    void drawDialogCircleFromMW();
	
private:
	
	GLWidget* glWindow;
	MainWindow* mainWindow;
};

#endif
