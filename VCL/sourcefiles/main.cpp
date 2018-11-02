#include "headerfiles/main_window.h"

#include <iostream>

#include <QApplication>
#include <QCommandlineParser>

int main(int argc, char *argv[])
{

	QApplication application(argc, argv);
    QCoreApplication::setApplicationName("Patch Tool");
    QCoreApplication::setApplicationVersion("1.0");

    QCommandLineParser parser;
    parser.setApplicationDescription("Test helper");
    parser.addHelpOption();
    parser.addVersionOption();
    parser.process(application);

	MainWindow mainWindow(argc, argv);
	mainWindow.show();
	return application.exec();
}