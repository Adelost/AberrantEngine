#pragma once

#include "Preforwards.h"
#include <QMainWindow.h>

class Simulation;

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow();

	void testNetwork();
	void capFps(float loopDelay);
	void displayFrameTime(float deltaTime);
	void setFpsCap(int fps);
	void setTitle(QString title);
	void setTitleMessage(QString message);

public slots:
	void update();

protected:

private:
	int m_fpsCap;
	QString m_title;
	QTimer* m_loopTimer;
	QWidget* m_renderWidget;
	shared_ptr<Simulation> m_simulation;
};

