/********************************************************************************
** Form generated from reading UI file 'dialog_settings.ui'
**
** Created by: Qt User Interface Compiler version 5.11.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOG_SETTINGS_H
#define UI_DIALOG_SETTINGS_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QTreeView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_DialogSettings
{
public:
    QGridLayout *gridLayout;
    QSplitter *splitter_2;
    QSplitter *splitter;
    QTreeView *treeView;
    QWidget *widget;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *DialogSettings)
    {
        if (DialogSettings->objectName().isEmpty())
            DialogSettings->setObjectName(QStringLiteral("DialogSettings"));
        DialogSettings->resize(412, 387);
        gridLayout = new QGridLayout(DialogSettings);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        splitter_2 = new QSplitter(DialogSettings);
        splitter_2->setObjectName(QStringLiteral("splitter_2"));
        splitter_2->setOrientation(Qt::Vertical);
        splitter = new QSplitter(splitter_2);
        splitter->setObjectName(QStringLiteral("splitter"));
        splitter->setOrientation(Qt::Horizontal);
        treeView = new QTreeView(splitter);
        treeView->setObjectName(QStringLiteral("treeView"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(treeView->sizePolicy().hasHeightForWidth());
        treeView->setSizePolicy(sizePolicy);
        splitter->addWidget(treeView);
        widget = new QWidget(splitter);
        widget->setObjectName(QStringLiteral("widget"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(widget->sizePolicy().hasHeightForWidth());
        widget->setSizePolicy(sizePolicy1);
        splitter->addWidget(widget);
        splitter_2->addWidget(splitter);
        buttonBox = new QDialogButtonBox(splitter_2);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        splitter_2->addWidget(buttonBox);

        gridLayout->addWidget(splitter_2, 0, 0, 1, 1);


        retranslateUi(DialogSettings);
        QObject::connect(buttonBox, SIGNAL(accepted()), DialogSettings, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), DialogSettings, SLOT(reject()));

        QMetaObject::connectSlotsByName(DialogSettings);
    } // setupUi

    void retranslateUi(QDialog *DialogSettings)
    {
        DialogSettings->setWindowTitle(QApplication::translate("DialogSettings", "Settings", nullptr));
    } // retranslateUi

};

namespace Ui {
    class DialogSettings: public Ui_DialogSettings {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOG_SETTINGS_H
