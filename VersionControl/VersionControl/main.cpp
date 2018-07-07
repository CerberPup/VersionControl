#include "VersionControl.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);
	VersionControl VC;
	VC.show();
	return app.exec();
}
