#include "headerfiles/main_window.h"

#include "headerfiles/diff_generator.h"
#include "headerfiles/config_manager.h"
#include "headerfiles/custom_delegate.h"
#include "headerfiles/dialog_diff_apply.h"
#include "headerfiles/dialog_settings.h"

#include "ui_mainwindow.h"

#include <queue>
#include <fstream>
#include <set>
#include <time.h>

#include <QDateTime>
#include <QFileDialog>
#include <QMessageBox>
#include <QScrollBar>
#include <QTextStream>

#undef _DEBUG

namespace {
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
                returnValue = "-" + std::to_string(hours) + "00";
            }
        }
        return returnValue;
    }

    DialogDiffGen::generatorType str2generatorType(std::string toParse) 
    {
        for (auto & c : toParse) c = toupper(c);

        if (toParse == "PROGRAM")
        {
            return DialogDiffGen::generatorType::program;
        }if (toParse == "SYSTEM")
        {
            return DialogDiffGen::generatorType::system;
        }if (toParse == "USER")
        {
            return DialogDiffGen::generatorType::user;
        }
        return DialogDiffGen::generatorType::invalid;
    }
}
#define EnsureHasNext if (i >= argc-1 || argv[i + 1][0] == '-') { throw std::invalid_argument(argument + " is missing argument"); }

void MainWindow::parseArguments(int argc, char *argv[])
{
    bool apply = false;
    std::string dump;
    bool noGui = false;
    std::string input;
    std::string second;
    std::string output;
    DialogDiffGen::generatorType generator = DialogDiffGen::generatorType::invalid;
    for (int i = 0; i < argc; i++)
    {
        std::string argument(argv[i]);
        for (auto & c : argument) c = toupper(c);
        
        if (argument == "-INPUT")
        {
            EnsureHasNext;
            input = argv[++i];
            continue;
        }
        if (argument == "-SECOND")
        {
            EnsureHasNext;
            second = argv[++i];
            continue;
        }
        if (argument == "-OUTPUT")
        {
            EnsureHasNext;
            output = argv[++i];
            continue;
        }
        if (argument == "-GENERATE")
        {
            EnsureHasNext;
            generator = str2generatorType(argv[++i]);
            if (generator == DialogDiffGen::generatorType::invalid)
                throw std::invalid_argument(argument);
            continue;
        }
        if (argument == "-DUMP")
        {
            EnsureHasNext;
            dump = argv[++i];
            continue;
        }
        if (argument == "-APPLY")
        {
            apply = true;
            continue;
        }
        if (argument == "-NOGUI")
        {
            noGui = true;
            continue;
        }
    }

    if (generator != DialogDiffGen::generatorType::invalid)
    {
        generateDiffFile(input.c_str(), second.c_str(), output.c_str(), generator);
    }
    if (apply && !noGui)
    {
        clock_t execution = clock();
        m_diffModel->loadFileAndDiff(input, generator == DialogDiffGen::generatorType::invalid? second : output);
        double execution_time = double(clock() - execution) / CLOCKS_PER_SEC;
        if (ConfigManager::getInstance().getBool(ConfigKeys::TimerKey))
        {
            QMessageBox(QMessageBox::Icon::NoIcon, "Execution time", "Execution time = " + QString::number(execution_time) + " seconds").exec();
        }
        onDiffModelDataChange();
    }
    if (dump.size()!=0)
    {
        if (!(apply && !noGui))//Not applied
        {
            m_diffModel->loadFileAndDiff(input, generator == DialogDiffGen::generatorType::invalid ? second : output);
            onDiffModelDataChange();
        }
        SaveGeneratedFile(dump.c_str());
    }
}

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
    , ui(new Ui::MainWindow)
	, m_directoryModel(new ModifiedFileSystemModel(this))
    , m_customDelegate(new CustomDelegate(this))
{
    m_diffModel = new DiffModel(this, m_customDelegate);
    ConfigManager::getInstance().initialize(QCoreApplication::applicationDirPath());
    QApplication::setFont(ConfigManager::getInstance().getQFont(ConfigKeys::FontKey));
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

    ui->OldListView->setMouseTracking(true);
    ui->NewListView->setMouseTracking(true);

	ui->NewListView->setItemDelegate(m_customDelegate);
	ui->OldListView->setItemDelegate(m_customDelegate);
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
	//connect(ui->splitter_3, SIGNAL(splitterMoved(int, int)), this, SLOT(onSplitterMove(int, int)));
	onSplitterMove(0, 0);

	m_directoryContextMenu = new QMenu(ui->DirectoryTreeView);
	m_directoryContextMenu->addAction("Set as Root", this, SLOT(onChangeRoot()));
	m_directoryContextMenu->addAction("Clear Root",this,SLOT(onClearRoot()));
	ui->DirectoryTreeView->setContextMenuPolicy(Qt::CustomContextMenu);
	connect(ui->DirectoryTreeView, SIGNAL(customContextMenuRequested(const QPoint &)), this, SLOT(onCustomContextMenuDirectory(const QPoint &)));

    ui->OldListView->setContextMenuPolicy(Qt::CustomContextMenu);
    ui->NewListView->setContextMenuPolicy(Qt::CustomContextMenu);
	connect(ui->OldListView, SIGNAL(customContextMenuRequested(const QPoint &)), this, SLOT(onCustomContextMenuDiff(const QPoint &)));
	connect(ui->NewListView, SIGNAL(customContextMenuRequested(const QPoint &)), this, SLOT(onCustomContextMenuDiff(const QPoint &)));
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
    m_customDelegate->maxNumber(m_diffModel->rowCount());
}

void MainWindow::generateDiffFile(const QString & _oldFile, const QString & _newFile, const QString & _diffFile, const DialogDiffGen::generatorType & _systemGenerator)
{
    clock_t execution = clock();
    switch (_systemGenerator)
    {
    case DialogDiffGen::generatorType::system:
        {
#ifndef _WIN32
        std::string command = "diff -u " + _oldFile.toUtf8().toStdString() + " " + _newFile.toUtf8().toStdString() + " > " + _diffFile.toUtf8().toStdString();
        system(command.c_str());
#else
        QMessageBox(QMessageBox::Icon::Warning, "Warning", "Windows doesn't have any good diff tool.");
#endif // !_WIN32
        }
        break;
    case DialogDiffGen::generatorType::user:
        {
            QString cmd = ConfigManager::getInstance().getQString(ConfigKeys::GeneratorKey + "/Executable");
            cmd += " " + ConfigManager::getInstance().getQString(ConfigKeys::GeneratorKey + "/Attributes");
            cmd = cmd.replace("$1", _oldFile);
            cmd = cmd.replace("$2", _newFile);
            cmd = cmd.replace("$3", _diffFile);
            cmd = cmd.replace("$F", _oldFile.split(QRegExp("(\\\\|/)+")).last());
            cmd = cmd.replace("$S", _newFile.split(QRegExp("(\\\\|/)+")).last());
            cmd = cmd.replace("$O", _diffFile.split(QRegExp("(\\\\|/)+")).last());
            system(cmd.toStdString().c_str());
        }
    break;
    case DialogDiffGen::generatorType::program:
        {
            QFileInfo oldFileInfo(_oldFile);
            QFileInfo newFileInfo(_newFile);
            QFile file(_diffFile);
            file.remove();
            if (file.open(QIODevice::WriteOnly))
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
                DiffGenerator::MagicInvoker i(_oldFile.toStdString(), _newFile.toStdString());
                i.save(stream);
            }
        }
    break;
    default:
        break;
    }
    double execution_time = double(clock() - execution) / CLOCKS_PER_SEC;
    if (ConfigManager::getInstance().getBool(ConfigKeys::TimerKey))
    {
        QMessageBox(QMessageBox::Icon::NoIcon, "Execution time", "Execution time = " + QString::number(execution_time) + " seconds").exec();
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

void MainWindow::onCustomContextMenuDirectory(const QPoint &point)
{
	QModelIndex index = ui->DirectoryTreeView->indexAt(point);
	if (index.isValid()) {
		m_directoryContextMenu->exec(ui->DirectoryTreeView->mapToGlobal(point));
	}
}
void MainWindow::onCustomContextMenuDiff(const QPoint &point)
{
    
    QModelIndex index;
    if (sender() == ui->NewListView)
    {
        index = ui->NewListView->indexAt(point);
    }
    else
    {
        index = ui->OldListView->indexAt(point);
    }

	
	if (index.isValid()) {
        QMenu menu;
        DT::diffRowData data = index.data().value<DT::diffRowData>();
        menu.addAction("Prefer left", m_diffModel, [this, index]() {m_diffModel->setVersion(index, DiffModel::version::left); });
        menu.addAction("Prefer right", m_diffModel, [this, index]() {m_diffModel->setVersion(index, DiffModel::version::right); });
        menu.addAction("Prefer left OVER right", m_diffModel, [this, index]() {m_diffModel->setVersion(index, DiffModel::version::leftOnRight); });
        menu.addAction("Prefer right OVER left", m_diffModel, [this, index]() {m_diffModel->setVersion(index, DiffModel::version::RightOnLeft); });
        menu.addSeparator();
        menu.addAction("Settings", this, SLOT(onSettingsRequest()));
        if (index.column()==1)//old view
        {
           
            menu.exec(ui->OldListView->mapToGlobal(point));
        }
        else//new view
        {
            menu.exec(ui->NewListView->mapToGlobal(point));
        }

		
	}
}

void MainWindow::onSettingsRequest()
{
    DialogSettings settingsDialog(this);
    connect(&settingsDialog, SIGNAL(fontChanged()), m_customDelegate, SLOT(onFontChanged()));
    settingsDialog.exec();
}

void MainWindow::onGenerateDiff()
{
    DialogDiffGen genDialog(this);
#ifdef _DEBUG
    generateDiffFile("D:/git/VersionControll/diff/test.cpp", "D:/git/VersionControll/diff/test2.cpp", "D:/git/VersionControll/diff/testp-u.diff", DialogDiffGen::generatorType::user);
#else
    if (genDialog.exec())
    {
        generateDiffFile(genDialog.getOld(), genDialog.getNew(), genDialog.getPatch(), genDialog.getGenerationType());
    }
#endif
    
}

void MainWindow::onApplyDiff()
{
    DialogDiffApply applyDialog(this);
#ifndef _DEBUG
    if (applyDialog.exec())
#endif // !_DEBUG
    {
#ifdef _DEBUG
        if (m_diffModel->loadFileAndDiff("D:/git/VersionControll/diff/test.cpp", "D:/git/VersionControll/diff/testp-u.diff"))
#else
        clock_t execution = clock();
        if (m_diffModel->loadFileAndDiff(applyDialog.getBasePath().toUtf8().constData(), applyDialog.getDiffPath().toUtf8().constData()))
#endif
        {
            double execution_time = double(clock() - execution) / CLOCKS_PER_SEC;
            if (ConfigManager::getInstance().getBool(ConfigKeys::TimerKey))
            {
                QMessageBox(QMessageBox::Icon::NoIcon, "Execution time", "Execution time = " + QString::number(execution_time) + " seconds").exec();
            }
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
    QString OutputFile = QFileDialog::getSaveFileName(this, "Save generated file", m_diffModel->getSourceFileName(), "All files (*.*)");
    SaveGeneratedFile(OutputFile);
}

void MainWindow::SaveGeneratedFile(QString _file)
{
    QFile file(_file);
    if (file.open(QIODevice::WriteOnly)) {
        QTextStream stream(&file);
        std::list<QString> outputData = m_diffModel->getOutputFileData();
        std::list<QString>::iterator lastElement = --outputData.end();
        for (std::list<QString>::iterator it = outputData.begin(); it != lastElement; it++)
        {
            stream << *it << endl;
        }
        //if (lastElement != outputData.begin())
            stream << *lastElement;
    }
    file.close();
}
