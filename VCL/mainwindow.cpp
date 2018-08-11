#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "customdelegate.h"
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
	m_diffModel->loadFileAndDiff("D:\\git\\VersionControll\\diff\\test.cpp", "D:\\git\\VersionControll\\diff\\test-u.diff");
	ui->OldListView->setModel(m_diffModel);
	ui->OldListView->setModelColumn(1);
	ui->NewListView->setModel(m_diffModel);
	ui->NewListView->setModelColumn(0);
	ui->NewListView->setItemDelegate(new CustomDelegate(ui->NewListView, ui->NewListView, ui->OldListView));
	ui->OldListView->setItemDelegate(new CustomDelegate(ui->OldListView, ui->NewListView, ui->OldListView));

#ifdef _WIN32
	ControlManager::initVersionControl(QString("D:/at"));
#else
	ControlManager::initVersionControl(QString("/home/dev/V"));
#endif
	
	m_currentSliderValue = 0;
	QScrollBar *lFctScrollBar = ui->NewListView->verticalScrollBar();
	QScrollBar *lValueScrollBar = ui->OldListView->verticalScrollBar();
	connect(lFctScrollBar, &QAbstractSlider::valueChanged,
		[=](int aSliderPosition) {if (aSliderPosition != m_currentSliderValue)
	{
		lValueScrollBar->setValue(aSliderPosition);
		m_currentSliderValue = aSliderPosition;
	}
	});
	connect(lValueScrollBar, &QAbstractSlider::valueChanged,
		[=](int aSliderPosition) {if (aSliderPosition != m_currentSliderValue)
	{
		lFctScrollBar->setValue(aSliderPosition);
		m_currentSliderValue = aSliderPosition;
	}
	});
	connect(ui->splitter, SIGNAL(splitterMoved(int,int)), this, SLOT(onSplitterMove(int,int)));
	connect(ui->splitter_2, SIGNAL(splitterMoved(int, int)), this, SLOT(onSplitterMove(int, int)));
	connect(ui->splitter_3, SIGNAL(splitterMoved(int, int)), this, SLOT(onSplitterMove(int, int)));
	onSplitterMove(0, 0);
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