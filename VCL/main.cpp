#include "mainwindow.h"
#include <QApplication>
#include <iostream>;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w(argc, argv);
	std::cout << argv[0];
    w.show();
    return a.exec();
}
