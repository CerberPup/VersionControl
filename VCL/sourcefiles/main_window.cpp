#include "headerfiles/main_window.h"

#include "headerfiles/custom_delegate.h"
#include "headerfiles/dialog_diff_apply.h"
#include "headerfiles/dialog_diff_gen.h"
#include "ui_mainwindow.h"

#include <QFileDialog>
#include <QMessageBox>
#include <QScrollBar>

MainWindow::MainWindow(int /*argc*/, char ** /*argv*/,QWidget *parent)
	: QMainWindow(parent)
    , ui(new Ui::MainWindow)
	, m_directoryModel(new ModifiedFileSystemModel(this))
	, m_diffModel(new DiffModel(this))
{
    ui->setupUi(this);

	ui->DirectoryTreeView->setModel(m_directoryModel);
	ui->DirectoryTreeView->setRootIndex(m_directoryModel->setRootPath(""));
	ui->DirectoryTreeView->setSortingEnabled(true);
	ui->DirectoryTreeView->sortByColumn(0, Qt::SortOrder::AscendingOrder);
	ui->DirectoryTreeView->setColumnHidden(1, true);
	ui->DirectoryTreeView->setColumnHidden(2, true);
	ui->DirectoryTreeView->setColumnHidden(3, true);

	ui->OldListView->setModel(m_diffModel);
	ui->OldListView->setModelColumn(1);
	ui->NewListView->setModel(m_diffModel);
	ui->NewListView->setModelColumn(0);

    m_customDelegate = new CustomDelegate(this);
    
	ui->NewListView->setItemDelegate(m_customDelegate);
	ui->OldListView->setItemDelegate(m_customDelegate);

    m_diffModel->setFontMetrics(QFontMetrics(QString("Roboto"),this));
    //m_diffModel->loadFileAndDiff("D:\\git\\VersionControll\\diff\\test.cpp", "D:\\git\\VersionControll\\diff\\test-u.diff");
	onDiffModelDataChange();

	m_currentSliderValue = 0;
	QScrollBar *lFctScrollBar = ui->NewListView->verticalScrollBar();
	QScrollBar *lValueScrollBar = ui->OldListView->verticalScrollBar();

	connect(lFctScrollBar, &QAbstractSlider::valueChanged, [=](int aSliderPosition) {if (aSliderPosition != m_currentSliderValue)
	{
		lValueScrollBar->setValue(aSliderPosition);
		m_currentSliderValue = aSliderPosition;
	}});

	connect(lValueScrollBar, &QAbstractSlider::valueChanged,[=](int aSliderPosition) {if (aSliderPosition != m_currentSliderValue)
	{
		lFctScrollBar->setValue(aSliderPosition);
		m_currentSliderValue = aSliderPosition;
	}});

    connect(ui->actionReset_Root_folder, SIGNAL(triggered()), this, SLOT(onSetRoot()));
    connect(ui->actionApply_patch, SIGNAL(triggered()), this, SLOT(onApplyDiff()));
    connect(ui->actionGenerate_patch, SIGNAL(triggered()), this, SLOT(onGenerateDiff()));
    connect(ui->actionReset_Root_folder, SIGNAL(triggered()), this, SLOT(onClearRoot()));
    connect(ui->actionInitialize_Version_Control, SIGNAL(triggered()), this, SLOT(onInitializeVersionControl()));

    connect(ui->splitter  , SIGNAL(splitterMoved(int, int)), this, SLOT(onSplitterMove(int, int)));
	connect(ui->splitter_2, SIGNAL(splitterMoved(int, int)), this, SLOT(onSplitterMove(int, int)));
	connect(ui->splitter_3, SIGNAL(splitterMoved(int, int)), this, SLOT(onSplitterMove(int, int)));
	onSplitterMove(0, 0);

	contextMenu = new QMenu(ui->DirectoryTreeView);
	contextMenu->addAction("Set as Root", this, SLOT(onChangeRoot()));
	contextMenu->addAction("Clear Root",this,SLOT(onClearRoot()));
	ui->DirectoryTreeView->setContextMenuPolicy(Qt::CustomContextMenu);
	connect(ui->DirectoryTreeView, SIGNAL(customContextMenuRequested(const QPoint &)), this, SLOT(onCustomContextMenu(const QPoint &)));
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::resizeEvent(QResizeEvent* event)
{
	onSplitterMove(0, 0);
	QMainWindow::resizeEvent(event);
}

void MainWindow::onSplitterMove(int /*pos*/, int /*index*/)
{
	m_diffModel->setOldFileViewSize(ui->OldListView->size());
	m_diffModel->setNewFileViewSize(ui->NewListView->size());
}

void MainWindow::onChangeRoot()
{
	ui->DirectoryTreeView->setRootIndex(m_directoryModel->setRootPath(ui->DirectoryTreeView->currentIndex().data(Qt::UserRole).toString()));
}

void MainWindow::onClearRoot()
{
	ui->DirectoryTreeView->setRootIndex(m_directoryModel->setRootPath(""));
}

void MainWindow::onDiffModelDataChange()
{
    m_customDelegate->setNumberWidth(m_diffModel->rowCount());
}

void MainWindow::onSetRoot()
{
    QString dir = QFileDialog::getExistingDirectory(this, tr("Select Root directory"), "", QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
	ui->DirectoryTreeView->setRootIndex(m_directoryModel->setRootPath(dir));
}

void MainWindow::onInitializeVersionControl()
{
    QString dir = QFileDialog::getExistingDirectory(this, tr("Select folder to control"), "", QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
    
}

void MainWindow::onCustomContextMenu(const QPoint &point)
{
	QModelIndex index = ui->DirectoryTreeView->indexAt(point);
	if (index.isValid()) {
		contextMenu->exec(ui->DirectoryTreeView->mapToGlobal(point));
	}
}

void MainWindow::onGenerateDiff()
{
    DialogDiffGen genDialog(this);
    if (genDialog.exec()) 
    {

    }
}

void MainWindow::onApplyDiff()
{
    DialogDiffApply applyDialog(this);
    if (applyDialog.exec())
    {
        if (m_diffModel->loadFileAndDiff(applyDialog.getBasePath().toUtf8().constData(), applyDialog.getDiffPath().toUtf8().constData()))
        {
            onDiffModelDataChange();
        }
        else 
        {
            QMessageBox msg(QMessageBox::Icon::Warning, "Error", "Parsing diff file failed." );
            msg.exec();
        }
        
    }
}
