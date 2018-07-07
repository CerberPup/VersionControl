/********************************************************************************
** Form generated from reading UI file 'VersionControl.ui'
**
** Created by: Qt User Interface Compiler version 5.11.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_VERSIONCONTROL_H
#define UI_VERSIONCONTROL_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_VersionControlClass
{
public:
    QWidget *centralWidget;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QMenu *menuSettings;
    QMenu *menuHelp;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *VersionControlClass)
    {
        if (VersionControlClass->objectName().isEmpty())
            VersionControlClass->setObjectName(QStringLiteral("VersionControlClass"));
        VersionControlClass->resize(600, 400);
        centralWidget = new QWidget(VersionControlClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        VersionControlClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(VersionControlClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 600, 21));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QStringLiteral("menuFile"));
        menuSettings = new QMenu(menuBar);
        menuSettings->setObjectName(QStringLiteral("menuSettings"));
        menuHelp = new QMenu(menuBar);
        menuHelp->setObjectName(QStringLiteral("menuHelp"));
        VersionControlClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(VersionControlClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        VersionControlClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(VersionControlClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        VersionControlClass->setStatusBar(statusBar);

        menuBar->addAction(menuFile->menuAction());
        menuBar->addAction(menuSettings->menuAction());
        menuBar->addAction(menuHelp->menuAction());

        retranslateUi(VersionControlClass);

        QMetaObject::connectSlotsByName(VersionControlClass);
    } // setupUi

    void retranslateUi(QMainWindow *VersionControlClass)
    {
        VersionControlClass->setWindowTitle(QApplication::translate("VersionControlClass", "VersionControl", nullptr));
        menuFile->setTitle(QApplication::translate("VersionControlClass", "File", nullptr));
        menuSettings->setTitle(QApplication::translate("VersionControlClass", "Settings", nullptr));
        menuHelp->setTitle(QApplication::translate("VersionControlClass", "Help", nullptr));
    } // retranslateUi

};

namespace Ui {
    class VersionControlClass: public Ui_VersionControlClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_VERSIONCONTROL_H
