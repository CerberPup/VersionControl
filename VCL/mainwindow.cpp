#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>

MainWindow::MainWindow(int argc, char *argv[],QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
	directoryModel(new ModifiedFileSystemModel(this)),
	directoryProxyModel(new QSortFilterProxyModel())
{
	QMessageBox msgBox;
#ifdef _WIN32
	
	msgBox.setText("Windows");
	
#else
	msgBox.setText("Unix");
#endif

	msgBox.exec();
    ui->setupUi(this);
	ui->DirectoryTreeView->setModel(directoryProxyModel);
	directoryProxyModel->setSourceModel(directoryModel);
	directoryModel->setRootPath(QDir::currentPath());
	ui->DirectoryTreeView->setSortingEnabled(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}
