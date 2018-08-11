#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSortFilterProxyModel>
#include "modifiedFileSystemModel.h"
#include "ControlManager.h"
#include "diffmodel.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(int argc, char *argv[],QWidget *parent = 0);
    ~MainWindow();
	void resizeEvent(QResizeEvent* event);
public slots:
	void onSplitterMove(int pos, int index);
	void onCustomContextMenu(const QPoint &point);
	void onChangeRoot();
	void onClearRoot();
private:
	QMenu * contextMenu;
    Ui::MainWindow *ui;
	DiffModel* m_diffModel;
	ModifiedFileSystemModel* m_directoryModel;
	int m_currentSliderValue;
};

#endif // MAINWINDOW_H
