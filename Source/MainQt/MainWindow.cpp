#include "Preincludes.h"
#include "MainWindow.h"

#include "Network.h"
#include "RenderWidget.h"

#include <Simulation/Simulation.h>
#include <Utils/StopWatch.h>
#include <Utils/Util.h>


namespace
{
	int round(float a)
	{
		return a + 0.5;
	}
	float secondsToMs(float secs)
	{
		return secs * 1000;
	}
}

MainWindow::MainWindow()
{
	testNetwork();

	// Init members
	m_renderWidget = new RenderWidget(this);
	setCentralWidget(m_renderWidget);
	m_renderWidget->setMinimumSize(20, 20);
	m_loopTimer = new QTimer(this);
	m_simulation = shared_ptr<Simulation>(new Simulation);

	// Init window
	setDockOptions(AllowNestedDocks | AllowTabbedDocks);
	setContextMenuPolicy(Qt::PreventContextMenu);
	setIconSize(QSize(20, 20));
	setTitle("Aberrant Engine");
	resize(500, 200);

	// Start update loop
	setFpsCap(120);
	connect(m_loopTimer, SIGNAL(timeout()), this, SLOT(update()));
	m_loopTimer->start();
}

void MainWindow::update()
{
	// Calculate delta time
	static StopWatch timer;
	float deltaTime = timer.time();
	timer.start();

	// Show fps and ms of latest frame in title
	displayFrameTime(deltaTime);

	// Update simulation
	m_simulation->update(deltaTime);

	// Cap frame rate
	capFps(timer.time());
}

void MainWindow::displayFrameTime(float deltaTime)
{
	static float timeSinceAvg = 0.0f;
	static float timeSinceMinMax = 0.0f;
	static int fpsCount = 0;
	static float minTime = Math::FLOAT_MAX;
	static float maxTime = 0.0f;

	timeSinceAvg += deltaTime;
	timeSinceMinMax += deltaTime;
	fpsCount++;
	if (deltaTime < minTime)
		minTime = deltaTime;
	if (deltaTime > maxTime)
		maxTime = deltaTime;

	static float minTimeUpdate = minTime;
	static float maxTimeUpdate = maxTime;

	if (timeSinceMinMax > 1.5)
	{
		minTimeUpdate = minTime;
		maxTimeUpdate = maxTime;

		minTime = Math::FLOAT_MAX;
		maxTime = 0;
		timeSinceMinMax = 0;
	}
	if (timeSinceAvg > 0.2)
	{
		float fps = fpsCount / timeSinceAvg;
		float ms = (timeSinceAvg / fpsCount) * 1000;

		QString message = QString(" | fps %1 | ms %2 (min %3, max %4)")
		                  .arg(QString::number(fps, 'f', 1))
		                  .arg(QString::number(ms, 'f', 1))
		                  .arg(QString::number(secondsToMs(minTimeUpdate), 'f', 1))
		                  .arg(QString::number(secondsToMs(maxTimeUpdate), 'f', 1));
		setTitleMessage(message);

		timeSinceAvg = 0;
		fpsCount = 0;
	}
}

void MainWindow::setFpsCap(int fps)
{
	m_loopTimer->setInterval(1);
	m_fpsCap = fps;
}

void MainWindow::capFps(float loopDelay)
{
	float msCap = (1.0f / m_fpsCap) * 1000;
	int interval = (int)(msCap);

	// Somehow intervals smaller than 1 ms is impossible with Qt, but if it wasn't
	// this would be how to do it.
	float decimalDelay = msCap - interval;
	//Util::busyWait(decimalDelay);

	// Compensate for simulation loop delay
	interval -= Math::round(secondsToMs(loopDelay));

	// Always apply at least 1 ms delay to allow Qt to reach its message loop.
	// This is required to prevent freeze in newer versions of Qt (such as Qt5),
	// if computation delay exceeds timer delay.
	if (interval < 1)
		interval = 1;
	m_loopTimer->setInterval(interval);
}

void MainWindow::setTitle(QString title)
{
	m_title = title;
	setWindowTitle("Aberrant Engine");
}

void MainWindow::setTitleMessage(QString message)
{
	QString fullTitle = m_title + " " + message;
	setWindowTitle(fullTitle);
}

void MainWindow::testNetwork()
{
	Network* net = new Network(this);
	net->sayHello();
}
