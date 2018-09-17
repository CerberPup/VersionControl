/********************************************************************************
** Form generated from reading UI file 'dialog_settings_color.ui'
**
** Created by: Qt User Interface Compiler version 5.11.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOG_SETTINGS_COLOR_H
#define UI_DIALOG_SETTINGS_COLOR_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_DialogSettingsColor
{
public:
    QFormLayout *formLayout;
    QVBoxLayout *verticalLayout;
    QLabel *Title;

    void setupUi(QWidget *DialogSettingsColor)
    {
        if (DialogSettingsColor->objectName().isEmpty())
            DialogSettingsColor->setObjectName(QStringLiteral("DialogSettingsColor"));
        DialogSettingsColor->resize(413, 230);
        formLayout = new QFormLayout(DialogSettingsColor);
        formLayout->setObjectName(QStringLiteral("formLayout"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        Title = new QLabel(DialogSettingsColor);
        Title->setObjectName(QStringLiteral("Title"));

        verticalLayout->addWidget(Title);


        formLayout->setLayout(0, QFormLayout::LabelRole, verticalLayout);


        retranslateUi(DialogSettingsColor);

        QMetaObject::connectSlotsByName(DialogSettingsColor);
    } // setupUi

    void retranslateUi(QWidget *DialogSettingsColor)
    {
        DialogSettingsColor->setWindowTitle(QApplication::translate("DialogSettingsColor", "Form", nullptr));
        Title->setText(QApplication::translate("DialogSettingsColor", "TextLabel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class DialogSettingsColor: public Ui_DialogSettingsColor {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOG_SETTINGS_COLOR_H
