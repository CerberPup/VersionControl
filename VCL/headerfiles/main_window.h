#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSortFilterProxyModel>
#include <QFontMetrics>

#include "custom_delegate.h"
#include "diff_model.h"
#include "modified_file_system_model.h"
#include "GeneratedFiles/ui_mainwindow.h"

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
	void onCustomContextMenuDirectory(const QPoint &point);
	void onCustomContextMenuDiff(const QPoint &point);
    void onSettingsRequest();
	void onGenerateDiff();
	void onApplyDiff();
    void onSaveGeneratedFile();
	void onSetRoot();
	void onInitializeVersionControl();
	void onChangeRoot();
	void onClearRoot();

public:
    DiffModel * m_diffModel;
private:
    void onDiffModelDataChange();
    void generateDiffFile(const QString& _oldFile, const QString& _newFile, const QString& _diffFile, const bool& _systemGenerator);

	QMenu * m_directoryContextMenu;
	QMenu * m_diffContextMenu;
    Ui::MainWindow *ui;
	
	ModifiedFileSystemModel* m_directoryModel;
    CustomDelegate* m_customDelegate;
	int m_currentSliderValue;
};

#endif // MAINWINDOW_H
