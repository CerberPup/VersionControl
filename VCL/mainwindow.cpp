#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(int argc, char *argv[],QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
	directoryModel(new QFileSystemModel(this)),
	directoryProxyModel(new QSortFilterProxyModel)
{
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
