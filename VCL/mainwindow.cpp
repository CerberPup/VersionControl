#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>

MainWindow::MainWindow(int argc, char *argv[],QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
	directoryModel(new ModifiedFileSystemModel(this))
{
    ui->setupUi(this);
	ui->DirectoryTreeView->setModel(directoryModel);
	ui->DirectoryTreeView->setRootIndex(directoryModel->setRootPath(""));
	ui->DirectoryTreeView->setSortingEnabled(true);
	ui->DirectoryTreeView->sortByColumn(0, Qt::SortOrder::AscendingOrder);
	ui->DirectoryTreeView->setColumnHidden(1, true);
	ui->DirectoryTreeView->setColumnHidden(2, true);
	ui->DirectoryTreeView->setColumnHidden(3, true);
#ifdef _WIN32
	ControlManager::initVersionControl(QString("D:/a"));
#else
	ControlManager::initVersionControl(QString("/home/dev/V"));
#endif
	
	
}

MainWindow::~MainWindow()
{
    delete ui;
}
