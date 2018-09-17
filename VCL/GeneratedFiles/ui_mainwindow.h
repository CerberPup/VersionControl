/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.11.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QListView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTreeView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionSet_Root;
    QAction *actionExit;
    QAction *actionInitialize_Version_Control;
    QAction *actionCommit_Changes;
    QAction *actionReset_Root_folder;
    QAction *actionGenerate_patch;
    QAction *actionApply_patch;
    QAction *actionAbout_QT;
    QAction *actionSave_generated_file;
    QAction *actionSettings;
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    QSplitter *splitter_3;
    QTreeView *DirectoryTreeView;
    QSplitter *splitter_2;
    QSplitter *splitter;
    QListView *OldListView;
    QListView *NewListView;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QMenu *menuOption;
    QMenu *menuSettings;
    QMenu *menuMenage;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(719, 524);
        actionSet_Root = new QAction(MainWindow);
        actionSet_Root->setObjectName(QStringLiteral("actionSet_Root"));
        actionExit = new QAction(MainWindow);
        actionExit->setObjectName(QStringLiteral("actionExit"));
        actionInitialize_Version_Control = new QAction(MainWindow);
        actionInitialize_Version_Control->setObjectName(QStringLiteral("actionInitialize_Version_Control"));
        actionCommit_Changes = new QAction(MainWindow);
        actionCommit_Changes->setObjectName(QStringLiteral("actionCommit_Changes"));
        actionReset_Root_folder = new QAction(MainWindow);
        actionReset_Root_folder->setObjectName(QStringLiteral("actionReset_Root_folder"));
        actionGenerate_patch = new QAction(MainWindow);
        actionGenerate_patch->setObjectName(QStringLiteral("actionGenerate_patch"));
        actionApply_patch = new QAction(MainWindow);
        actionApply_patch->setObjectName(QStringLiteral("actionApply_patch"));
        actionApply_patch->setShortcutContext(Qt::WindowShortcut);
        actionApply_patch->setAutoRepeat(true);
        actionAbout_QT = new QAction(MainWindow);
        actionAbout_QT->setObjectName(QStringLiteral("actionAbout_QT"));
        actionAbout_QT->setMenuRole(QAction::AboutQtRole);
        actionSave_generated_file = new QAction(MainWindow);
        actionSave_generated_file->setObjectName(QStringLiteral("actionSave_generated_file"));
        actionSettings = new QAction(MainWindow);
        actionSettings->setObjectName(QStringLiteral("actionSettings"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        splitter_3 = new QSplitter(centralWidget);
        splitter_3->setObjectName(QStringLiteral("splitter_3"));
        splitter_3->setOrientation(Qt::Horizontal);
        splitter_3->setChildrenCollapsible(false);
        DirectoryTreeView = new QTreeView(splitter_3);
        DirectoryTreeView->setObjectName(QStringLiteral("DirectoryTreeView"));
        DirectoryTreeView->setEnabled(true);
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(4);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(DirectoryTreeView->sizePolicy().hasHeightForWidth());
        DirectoryTreeView->setSizePolicy(sizePolicy);
        DirectoryTreeView->setMinimumSize(QSize(100, 200));
        DirectoryTreeView->setMaximumSize(QSize(16777215, 16777215));
        DirectoryTreeView->setSizeIncrement(QSize(0, 0));
        DirectoryTreeView->setBaseSize(QSize(0, 0));
        splitter_3->addWidget(DirectoryTreeView);
        DirectoryTreeView->header()->setVisible(true);
        splitter_2 = new QSplitter(splitter_3);
        splitter_2->setObjectName(QStringLiteral("splitter_2"));
        splitter_2->setOrientation(Qt::Vertical);
        splitter_2->setChildrenCollapsible(false);
        splitter = new QSplitter(splitter_2);
        splitter->setObjectName(QStringLiteral("splitter"));
        splitter->setOrientation(Qt::Horizontal);
        splitter->setChildrenCollapsible(false);
        OldListView = new QListView(splitter);
        OldListView->setObjectName(QStringLiteral("OldListView"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(OldListView->sizePolicy().hasHeightForWidth());
        OldListView->setSizePolicy(sizePolicy1);
        OldListView->setMinimumSize(QSize(0, 142));
        splitter->addWidget(OldListView);
        NewListView = new QListView(splitter);
        NewListView->setObjectName(QStringLiteral("NewListView"));
        sizePolicy1.setHeightForWidth(NewListView->sizePolicy().hasHeightForWidth());
        NewListView->setSizePolicy(sizePolicy1);
        NewListView->setMinimumSize(QSize(0, 100));
        splitter->addWidget(NewListView);
        splitter_2->addWidget(splitter);
        splitter_3->addWidget(splitter_2);

        gridLayout->addWidget(splitter_3, 0, 0, 1, 1);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 719, 21));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QStringLiteral("menuFile"));
        menuOption = new QMenu(menuBar);
        menuOption->setObjectName(QStringLiteral("menuOption"));
        menuSettings = new QMenu(menuBar);
        menuSettings->setObjectName(QStringLiteral("menuSettings"));
        menuMenage = new QMenu(menuBar);
        menuMenage->setObjectName(QStringLiteral("menuMenage"));
        menuMenage->setEnabled(true);
        MainWindow->setMenuBar(menuBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);
        QWidget::setTabOrder(DirectoryTreeView, OldListView);

        menuBar->addAction(menuFile->menuAction());
        menuBar->addAction(menuMenage->menuAction());
        menuBar->addAction(menuSettings->menuAction());
        menuBar->addAction(menuOption->menuAction());
        menuFile->addAction(actionSet_Root);
        menuFile->addAction(actionReset_Root_folder);
        menuFile->addSeparator();
        menuFile->addAction(actionExit);
        menuSettings->addAction(actionSettings);
        menuMenage->addAction(actionInitialize_Version_Control);
        menuMenage->addAction(actionCommit_Changes);
        menuMenage->addSeparator();
        menuMenage->addAction(actionGenerate_patch);
        menuMenage->addAction(actionApply_patch);
        menuMenage->addSeparator();
        menuMenage->addAction(actionSave_generated_file);

        retranslateUi(MainWindow);
        QObject::connect(actionExit, SIGNAL(triggered()), MainWindow, SLOT(close()));

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", nullptr));
        actionSet_Root->setText(QApplication::translate("MainWindow", "Select Root folder", nullptr));
        actionExit->setText(QApplication::translate("MainWindow", "Exit", nullptr));
        actionInitialize_Version_Control->setText(QApplication::translate("MainWindow", "Initialize Version Control", nullptr));
        actionCommit_Changes->setText(QApplication::translate("MainWindow", "Commit Changes", nullptr));
        actionReset_Root_folder->setText(QApplication::translate("MainWindow", "Reset Root folder", nullptr));
        actionGenerate_patch->setText(QApplication::translate("MainWindow", "Generate patch", nullptr));
#ifndef QT_NO_SHORTCUT
        actionGenerate_patch->setShortcut(QApplication::translate("MainWindow", "Ctrl+G", nullptr));
#endif // QT_NO_SHORTCUT
        actionApply_patch->setText(QApplication::translate("MainWindow", "Apply patch", nullptr));
#ifndef QT_NO_SHORTCUT
        actionApply_patch->setShortcut(QApplication::translate("MainWindow", "Ctrl+A", nullptr));
#endif // QT_NO_SHORTCUT
        actionAbout_QT->setText(QApplication::translate("MainWindow", "About Qt", nullptr));
        actionSave_generated_file->setText(QApplication::translate("MainWindow", "Save generated file", nullptr));
        actionSettings->setText(QApplication::translate("MainWindow", "Settings...", nullptr));
        menuFile->setTitle(QApplication::translate("MainWindow", "File", nullptr));
        menuOption->setTitle(QApplication::translate("MainWindow", "Help", nullptr));
        menuSettings->setTitle(QApplication::translate("MainWindow", "Settings", nullptr));
        menuMenage->setTitle(QApplication::translate("MainWindow", "Menage", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
