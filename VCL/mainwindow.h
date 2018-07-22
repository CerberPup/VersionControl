#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSortFilterProxyModel>
#include <modifiedFileSystemModel.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(int argc, char *argv[],QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
	ModifiedFileSystemModel* directoryModel;
	QSortFilterProxyModel* directoryProxyModel;
};

#endif // MAINWINDOW_H
