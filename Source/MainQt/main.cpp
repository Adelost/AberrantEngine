#include "Preincludes.h"
#include "Preforwards.h"
#include "MainWindow.h"

int main(int argc, char *argv[])
{
	// Detect memory leaks

#if defined(DEBUG) | defined(_DEBUG)
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

	// Startup program

	QApplication a(argc, argv);
	MainWindow w;
	w.show();
	return a.exec();
}
