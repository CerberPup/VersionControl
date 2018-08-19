/********************************************************************************
** Form generated from reading UI file 'dialog_diffApply.ui'
**
** Created by: Qt User Interface Compiler version 5.11.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOG_DIFFAPPLY_H
#define UI_DIALOG_DIFFAPPLY_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_DialogDiffApply
{
public:
    QGridLayout *gridLayout;
    QDialogButtonBox *buttonBox;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label;
    QLineEdit *lineEdit;
    QPushButton *pushButton;
    QHBoxLayout *horizontalLayout;
    QLabel *label_2;
    QLineEdit *lineEdit_2;
    QPushButton *pushButton_2;
    QLabel *label_error;

    void setupUi(QDialog *DialogDiffApply)
    {
        if (DialogDiffApply->objectName().isEmpty())
            DialogDiffApply->setObjectName(QStringLiteral("DialogDiffApply"));
        DialogDiffApply->resize(508, 99);
        gridLayout = new QGridLayout(DialogDiffApply);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        buttonBox = new QDialogButtonBox(DialogDiffApply);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(buttonBox->sizePolicy().hasHeightForWidth());
        buttonBox->setSizePolicy(sizePolicy);
        buttonBox->setMinimumSize(QSize(0, 0));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        gridLayout->addWidget(buttonBox, 1, 1, 1, 1);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        label = new QLabel(DialogDiffApply);
        label->setObjectName(QStringLiteral("label"));
        label->setMinimumSize(QSize(40, 0));

        horizontalLayout_2->addWidget(label);

        lineEdit = new QLineEdit(DialogDiffApply);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));

        horizontalLayout_2->addWidget(lineEdit);

        pushButton = new QPushButton(DialogDiffApply);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        sizePolicy.setHeightForWidth(pushButton->sizePolicy().hasHeightForWidth());
        pushButton->setSizePolicy(sizePolicy);
        pushButton->setMaximumSize(QSize(24, 20));

        horizontalLayout_2->addWidget(pushButton);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label_2 = new QLabel(DialogDiffApply);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setMinimumSize(QSize(40, 0));

        horizontalLayout->addWidget(label_2);

        lineEdit_2 = new QLineEdit(DialogDiffApply);
        lineEdit_2->setObjectName(QStringLiteral("lineEdit_2"));

        horizontalLayout->addWidget(lineEdit_2);

        pushButton_2 = new QPushButton(DialogDiffApply);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
        pushButton_2->setMaximumSize(QSize(24, 20));

        horizontalLayout->addWidget(pushButton_2);


        verticalLayout->addLayout(horizontalLayout);


        gridLayout->addLayout(verticalLayout, 0, 0, 1, 2);

        label_error = new QLabel(DialogDiffApply);
        label_error->setObjectName(QStringLiteral("label_error"));
        label_error->setLayoutDirection(Qt::LeftToRight);
        label_error->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(label_error, 1, 0, 1, 1);

        QWidget::setTabOrder(pushButton, pushButton_2);
        QWidget::setTabOrder(pushButton_2, lineEdit_2);
        QWidget::setTabOrder(lineEdit_2, lineEdit);

        retranslateUi(DialogDiffApply);
        QObject::connect(buttonBox, SIGNAL(accepted()), DialogDiffApply, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), DialogDiffApply, SLOT(reject()));

        QMetaObject::connectSlotsByName(DialogDiffApply);
    } // setupUi

    void retranslateUi(QDialog *DialogDiffApply)
    {
        DialogDiffApply->setWindowTitle(QApplication::translate("DialogDiffApply", "Dialog", nullptr));
        label->setText(QApplication::translate("DialogDiffApply", "Base file", nullptr));
        pushButton->setText(QApplication::translate("DialogDiffApply", "...", nullptr));
        label_2->setText(QApplication::translate("DialogDiffApply", "DIff File", nullptr));
        pushButton_2->setText(QApplication::translate("DialogDiffApply", "...", nullptr));
        label_error->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class DialogDiffApply: public Ui_DialogDiffApply {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOG_DIFFAPPLY_H
