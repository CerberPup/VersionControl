#include "headerfiles/main_window.h"

#include <iostream>

#include <QApplication>

int main(int argc, char *argv[])
{

	QApplication a(argc, argv);
	MainWindow w(argc, argv);
	w.show();
	return a.exec();
}