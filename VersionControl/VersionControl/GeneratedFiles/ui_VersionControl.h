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
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_VersionControlClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *VersionControlClass)
    {
        if (VersionControlClass->objectName().isEmpty())
            VersionControlClass->setObjectName(QStringLiteral("VersionControlClass"));
        VersionControlClass->resize(600, 400);
        menuBar = new QMenuBar(VersionControlClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        VersionControlClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(VersionControlClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        VersionControlClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(VersionControlClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        VersionControlClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(VersionControlClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        VersionControlClass->setStatusBar(statusBar);

        retranslateUi(VersionControlClass);

        QMetaObject::connectSlotsByName(VersionControlClass);
    } // setupUi

    void retranslateUi(QMainWindow *VersionControlClass)
    {
        VersionControlClass->setWindowTitle(QApplication::translate("VersionControlClass", "VersionControl", nullptr));
    } // retranslateUi

};

namespace Ui {
    class VersionControlClass: public Ui_VersionControlClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_VERSIONCONTROL_H
