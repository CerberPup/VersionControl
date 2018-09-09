#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSortFilterProxyModel>
#include <QFontMetrics>

#include "custom_delegate.h"
#include "diff_model.h"
#include "modified_file_system_model.h"
#include "version_control_system.h"

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
	void onGenerateDiff();
	void onApplyDiff();
    void onSaveGeneratedFile();
	void onSetRoot();
	void onInitializeVersionControl();
	void onChangeRoot();
	void onClearRoot();

private:
    void onDiffModelDataChange();
    void generateDiffFile(const QString& _oldFile, const QString& _newFile, const QString& _diffFile, const bool& _systemGenerator);
	QMenu * contextMenu;
    Ui::MainWindow *ui;
	DiffModel* m_diffModel;
	ModifiedFileSystemModel* m_directoryModel;
    CustomDelegate* m_customDelegate;
	int m_currentSliderValue;
};

#endif // MAINWINDOW_H
