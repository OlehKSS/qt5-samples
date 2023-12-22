#include <QApplication>
#include "MandelbrotMainWindow.h"
#include "JobResult.h"

int main(int argc, char** argv)
{
	QApplication app(argc, argv);
    // To use the type T in queued signal and slot connections, qRegisterMetaType<T>() must be called before the first connection is established.
	qRegisterMetaType<JobResult>("JobResult");
	qRegisterMetaType<QList<JobResult>>("QList<JobResult>");

	MandelbrotMainWindow mainWindow;
	mainWindow.show();
	return app.exec();
}