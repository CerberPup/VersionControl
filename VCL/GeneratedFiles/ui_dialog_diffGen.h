/********************************************************************************
** Form generated from reading UI file 'dialog_diffGen.ui'
**
** Created by: Qt User Interface Compiler version 5.11.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOG_DIFFGEN_H
#define UI_DIALOG_DIFFGEN_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_DialogDiffGen
{
public:
    QHBoxLayout *horizontalLayout_5;
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label;
    QLineEdit *lineEdit;
    QPushButton *pushButton;
    QHBoxLayout *horizontalLayout;
    QLabel *label_2;
    QLineEdit *lineEdit_2;
    QPushButton *pushButton_2;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_3;
    QLineEdit *lineEdit_3;
    QPushButton *pushButton_3;
    QGroupBox *groupBox;
    QFormLayout *formLayout;
    QRadioButton *radioButton;
    QRadioButton *radioButton_2;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_error;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *DialogDiffGen)
    {
        if (DialogDiffGen->objectName().isEmpty())
            DialogDiffGen->setObjectName(QStringLiteral("DialogDiffGen"));
        DialogDiffGen->resize(507, 222);
        horizontalLayout_5 = new QHBoxLayout(DialogDiffGen);
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        label = new QLabel(DialogDiffGen);
        label->setObjectName(QStringLiteral("label"));
        label->setMinimumSize(QSize(40, 0));

        horizontalLayout_2->addWidget(label);

        lineEdit = new QLineEdit(DialogDiffGen);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));

        horizontalLayout_2->addWidget(lineEdit);

        pushButton = new QPushButton(DialogDiffGen);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(pushButton->sizePolicy().hasHeightForWidth());
        pushButton->setSizePolicy(sizePolicy);
        pushButton->setMaximumSize(QSize(24, 20));

        horizontalLayout_2->addWidget(pushButton);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label_2 = new QLabel(DialogDiffGen);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setMinimumSize(QSize(40, 0));

        horizontalLayout->addWidget(label_2);

        lineEdit_2 = new QLineEdit(DialogDiffGen);
        lineEdit_2->setObjectName(QStringLiteral("lineEdit_2"));

        horizontalLayout->addWidget(lineEdit_2);

        pushButton_2 = new QPushButton(DialogDiffGen);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
        pushButton_2->setMaximumSize(QSize(24, 20));

        horizontalLayout->addWidget(pushButton_2);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        label_3 = new QLabel(DialogDiffGen);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setMinimumSize(QSize(40, 0));

        horizontalLayout_3->addWidget(label_3);

        lineEdit_3 = new QLineEdit(DialogDiffGen);
        lineEdit_3->setObjectName(QStringLiteral("lineEdit_3"));

        horizontalLayout_3->addWidget(lineEdit_3);

        pushButton_3 = new QPushButton(DialogDiffGen);
        pushButton_3->setObjectName(QStringLiteral("pushButton_3"));
        pushButton_3->setMaximumSize(QSize(24, 20));

        horizontalLayout_3->addWidget(pushButton_3);


        verticalLayout->addLayout(horizontalLayout_3);


        verticalLayout_2->addLayout(verticalLayout);

        groupBox = new QGroupBox(DialogDiffGen);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Minimum);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(groupBox->sizePolicy().hasHeightForWidth());
        groupBox->setSizePolicy(sizePolicy1);
        groupBox->setFlat(true);
        groupBox->setCheckable(false);
        formLayout = new QFormLayout(groupBox);
        formLayout->setObjectName(QStringLiteral("formLayout"));
        radioButton = new QRadioButton(groupBox);
        radioButton->setObjectName(QStringLiteral("radioButton"));
        radioButton->setChecked(true);

        formLayout->setWidget(0, QFormLayout::LabelRole, radioButton);

        radioButton_2 = new QRadioButton(groupBox);
        radioButton_2->setObjectName(QStringLiteral("radioButton_2"));

        formLayout->setWidget(1, QFormLayout::LabelRole, radioButton_2);


        verticalLayout_2->addWidget(groupBox);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        label_error = new QLabel(DialogDiffGen);
        label_error->setObjectName(QStringLiteral("label_error"));
        QSizePolicy sizePolicy2(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(label_error->sizePolicy().hasHeightForWidth());
        label_error->setSizePolicy(sizePolicy2);
        label_error->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_4->addWidget(label_error);

        buttonBox = new QDialogButtonBox(DialogDiffGen);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        sizePolicy.setHeightForWidth(buttonBox->sizePolicy().hasHeightForWidth());
        buttonBox->setSizePolicy(sizePolicy);
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        horizontalLayout_4->addWidget(buttonBox);


        verticalLayout_2->addLayout(horizontalLayout_4);


        horizontalLayout_5->addLayout(verticalLayout_2);


        retranslateUi(DialogDiffGen);
        QObject::connect(buttonBox, SIGNAL(accepted()), DialogDiffGen, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), DialogDiffGen, SLOT(reject()));

        QMetaObject::connectSlotsByName(DialogDiffGen);
    } // setupUi

    void retranslateUi(QDialog *DialogDiffGen)
    {
        DialogDiffGen->setWindowTitle(QApplication::translate("DialogDiffGen", "Dialog", nullptr));
        label->setText(QApplication::translate("DialogDiffGen", "Old File", nullptr));
        pushButton->setText(QApplication::translate("DialogDiffGen", "...", nullptr));
        label_2->setText(QApplication::translate("DialogDiffGen", "New File", nullptr));
        pushButton_2->setText(QApplication::translate("DialogDiffGen", "...", nullptr));
        label_3->setText(QApplication::translate("DialogDiffGen", "Output", nullptr));
        pushButton_3->setText(QApplication::translate("DialogDiffGen", "...", nullptr));
        groupBox->setTitle(QApplication::translate("DialogDiffGen", "Diff Generator", nullptr));
        radioButton->setText(QApplication::translate("DialogDiffGen", "System", nullptr));
        radioButton_2->setText(QApplication::translate("DialogDiffGen", "Program", nullptr));
        label_error->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class DialogDiffGen: public Ui_DialogDiffGen {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOG_DIFFGEN_H
