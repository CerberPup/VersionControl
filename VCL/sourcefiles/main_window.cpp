#include "headerfiles/main_window.h"

#include "headerfiles/config_manager.h"
#include "headerfiles/custom_delegate.h"
#include "headerfiles/dialog_diff_apply.h"
#include "headerfiles/dialog_diff_gen.h"
#include "headerfiles/dialog_settings.h"
#include "ui_mainwindow.h"

#include <queue>
#include <fstream>

#include <QDateTime>
#include <QFileDialog>
#include <QMessageBox>
#include <QScrollBar>
#include <QTextStream>

namespace 
{
    std::string intToUtcOffset(int &hours) 
    {
        std::string returnValue;
        if (hours > 0)
        {
            if (hours < 10)
            {
                returnValue = "+0" + std::to_string(hours) + "00";
            }
            else
            {
                returnValue = "+" + std::to_string(hours) + "00";
            }
        }
        else
        {
            if (hours > -10)
            {
                returnValue = "-0" + std::to_string(hours) + "00";
            }
            else
            {
                returnValue = "-" + std::to_string(hours) +  "00";
            }
        }
        return returnValue;
    }

    template <class T> class FifoContainer
    {
        std::queue<T> data;
        size_t size;
    public:
        FifoContainer(size_t _size):size(_size){}

        void push(T _element) 
        {
            if (data.size() == size)
                data.pop();
            data.push(_element);
        }

        T pop() {return data.pop() }
        std::queue<T> getData() {return data}
    };

    class ContextContainer
    {
        FifoContainer<std::string> begin;
        FifoContainer<std::string> end;
        std::queue<std::string> data;
    public:
        ContextContainer():begin(3),end(3)
        {
            
        }
        int push(std::string _row, bool _first) 
        {
            if (_first) 
            {

            }
            else 
            {

            }
        }
    };
    class MagicInvoker
    {
        typedef std::map<size_t, std::string> rawContainer;
        std::string oldFilePath;
        std::string newFilePath;
        rawContainer rawDataOld;
        rawContainer rawDataNew;

        void insertData(const std::string& _data, size_t _row, bool _oldFile)
        {
            if (_oldFile)
            {
                rawContainer::iterator it = rawDataNew.find(_row);
                if (it != rawDataNew.end())
                {
                    rawDataNew.erase(it);
                    return;
                }
                else
                {
                    rawDataOld[_row] = _data;
                    return;
                }
            }
            else
            {
                rawContainer::iterator it = rawDataOld.find(_row);
                if (it != rawDataOld.end())
                {
                    rawDataOld.erase(it);
                    return;
                }
                else
                {
                    rawDataNew[_row] = _data;
                    return;
                }
            }
        }

    public:
        MagicInvoker(std::string _oldFilePath, std::string _newFilePath)
            : oldFilePath(_oldFilePath)
            , newFilePath(_newFilePath)
        {
            size_t row = 0;
            std::string bufor;
            std::ifstream oldFile(_oldFilePath, std::ios::in);
            std::ifstream newFile(_newFilePath, std::ios::in);
            if (oldFile.good() && newFile.good())
            {
                while (!oldFile.eof()&& !newFile.eof())
                {
                    std::getline(oldFile, bufor);
                    insertData(bufor, row, true);
                    std::getline(newFile, bufor);
                    insertData(bufor, row, false);
                    row++;
                }
                while (!oldFile.eof())
                {
                    std::getline(oldFile, bufor);
                    insertData(bufor, row, true);
                    row++;
                }
                while (!newFile.eof())
                {
                    std::getline(newFile, bufor);
                    insertData(bufor, row, false);
                    row++;
                }
                oldFile.close();
                newFile.close();
            }
        }
    };

}

MainWindow::MainWindow(int /*argc*/, char ** /*argv*/,QWidget *parent)
	: QMainWindow(parent)
    , ui(new Ui::MainWindow)
	, m_directoryModel(new ModifiedFileSystemModel(this))
	, m_diffModel(new DiffModel(this))
{
    ConfigManager::getInstance().initialize(QCoreApplication::applicationDirPath());

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
    connect(ui->actionSettings, SIGNAL(triggered()), this, SLOT(onSettingsRequest()));
    connect(ui->actionApply_patch, SIGNAL(triggered()), this, SLOT(onApplyDiff()));
    connect(ui->actionGenerate_patch, SIGNAL(triggered()), this, SLOT(onGenerateDiff()));
    connect(ui->actionSave_generated_file, SIGNAL(triggered()), this, SLOT(onSaveGeneratedFile()));
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

void MainWindow::generateDiffFile(const QString & _oldFile, const QString & _newFile, const QString & _diffFile, const bool & _systemGenerator)
{
    if (_systemGenerator)
    {
#ifndef _WIN32
        std::string command = "diff -u " + _oldFile.toUtf8().toStdString()+" " + _newFile.toUtf8().toStdString() + " > " + _diffFile.toUtf8().toStdString();
        system(command.c_str());
#else
        QMessageBox(QMessageBox::Icon::Warning, "Warning", "Windows doesn't have any good diff tool.");
#endif // !_WIN32

    }
    else
    {
        QFileInfo oldFileInfo(_oldFile);
        QFileInfo newFileInfo(_newFile);
        QFile file(_diffFile);
        if (file.open(QIODevice::ReadWrite)) 
        {
            QTextStream stream(&file);

            int t = oldFileInfo.fileTime(QFileDevice::FileModificationTime).offsetFromUtc() / 3600;
            stream << "--- " + oldFileInfo.fileName() + '\t' + 
                oldFileInfo.fileTime(QFileDevice::FileModificationTime).toString("yyyy-MM-dd HH:mm:ss.zzz000000 ") +
                intToUtcOffset(t).c_str()
                << endl;

            t = newFileInfo.fileTime(QFileDevice::FileModificationTime).offsetFromUtc() / 3600;
            stream << "+++ " + newFileInfo.fileName() + '\t' +
                newFileInfo.fileTime(QFileDevice::FileModificationTime).toString("yyyy-MM-dd HH:mm:ss.zzz000000 ") +
                intToUtcOffset(t).c_str()
                << endl;
            MagicInvoker i(_oldFile.toStdString(), _newFile.toStdString());

        }

        
    }
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

void MainWindow::onSettingsRequest()
{
    DialogSettings settingsDialog(this);
    settingsDialog.exec();
}

void MainWindow::onGenerateDiff()
{
    DialogDiffGen genDialog(this);
    if (genDialog.exec()) 
    {
        generateDiffFile(genDialog.getOld(), genDialog.getNew(), genDialog.getPatch(), genDialog.getGenerationType());
        //generateDiffFile("D:/git/VersionControll/diff/test.cpp", "D:/git/VersionControll/diff/test2.cpp", "D:/git/VersionControll/diff/testp-u.diff", false);
    }
}

void MainWindow::onApplyDiff()
{
    DialogDiffApply applyDialog(this);
    if (applyDialog.exec())
    {
        if (m_diffModel->loadFileAndDiff(applyDialog.getBasePath().toUtf8().constData(), applyDialog.getDiffPath().toUtf8().constData()))
        //if (m_diffModel->loadFileAndDiff("D:/git/VersionControll/diff/test.cpp", "D:/git/VersionControll/diff/test-u.diff"))
        {
            onDiffModelDataChange();
        }
        else 
        {
            QMessageBox msg(QMessageBox::Icon::Critical, "Error", "Parsing diff file failed." );
            msg.exec();
        }
        
    }
}

void MainWindow::onSaveGeneratedFile()
{
    QString Ouptutfile = QFileDialog::getSaveFileName(this, "Save generated file", m_diffModel->getSourceFileName(), "All files (*.*)");
    QFile file(Ouptutfile);
    if (file.open(QIODevice::ReadWrite)) {
        QTextStream stream(&file);
        std::list<QString> outputData = m_diffModel->getOutputFileData();
        std::list<QString>::iterator lastElement = --outputData.end();
        for (std::list<QString>::iterator it = outputData.begin(); it != lastElement; it++)
        {
            stream << *it << endl;
        }
        if (lastElement != outputData.begin())
            stream << *lastElement;
    }
}
