#include "VersionControl.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	VersionControl w;
	w.show();
	return a.exec();
}
