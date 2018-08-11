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
    QAction *actionOpen;
    QAction *actionExit;
    QAction *actionInitialize_Version_Control;
    QAction *actionCommit_Changes;
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    QSplitter *splitter_3;
    QTreeView *DirectoryTreeView;
    QSplitter *splitter_2;
    QListView *CommitListView;
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
        actionOpen = new QAction(MainWindow);
        actionOpen->setObjectName(QStringLiteral("actionOpen"));
        actionExit = new QAction(MainWindow);
        actionExit->setObjectName(QStringLiteral("actionExit"));
        actionInitialize_Version_Control = new QAction(MainWindow);
        actionInitialize_Version_Control->setObjectName(QStringLiteral("actionInitialize_Version_Control"));
        actionCommit_Changes = new QAction(MainWindow);
        actionCommit_Changes->setObjectName(QStringLiteral("actionCommit_Changes"));
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
        CommitListView = new QListView(splitter_2);
        CommitListView->setObjectName(QStringLiteral("CommitListView"));
        splitter_2->addWidget(CommitListView);
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
        menuFile->addAction(actionOpen);
        menuFile->addSeparator();
        menuFile->addAction(actionExit);
        menuMenage->addAction(actionInitialize_Version_Control);
        menuMenage->addAction(actionCommit_Changes);

        retranslateUi(MainWindow);
        QObject::connect(actionExit, SIGNAL(triggered()), MainWindow, SLOT(close()));

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", nullptr));
        actionOpen->setText(QApplication::translate("MainWindow", "Select Root Folder", nullptr));
        actionExit->setText(QApplication::translate("MainWindow", "Exit", nullptr));
        actionInitialize_Version_Control->setText(QApplication::translate("MainWindow", "Initialize Version Control", nullptr));
        actionCommit_Changes->setText(QApplication::translate("MainWindow", "Commit Changes", nullptr));
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
