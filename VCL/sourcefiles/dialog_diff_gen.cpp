#include "headerfiles/dialog_diff_gen.h"
#include <QFileInfo>

DialogDiffGen::DialogDiffGen(QWidget *parent)
    : QDialog(parent)
{
    setupUi(this);
    setWindowTitle("Generate patch");
    label_error->setStyleSheet("QLabel { color : red; }");

    connect(lineEdit, SIGNAL(textChanged(const QString &)), this, SLOT(onValidateInputs()));
    connect(lineEdit_2, SIGNAL(textChanged(const QString &)), this, SLOT(onValidateInputs()));
}

DialogDiffGen::~DialogDiffGen()
{
}

void DialogDiffGen::onValidateInputs()
{
    QString oldError = "Old file doesn't exist";
    QString diffError = "New file doesn't exist";
    bool base = QFileInfo(lineEdit->text()).isFile();
    bool diff = QFileInfo(lineEdit_2->text()).isFile();
    QString error = "";
    if (!base)
    {
        error = oldError;
        if (!diff)
        {
            error.append(", ");
            error.append(diffError);
        }
    }
    else
    {
        if (!diff)
        {
            error = diffError;
        }
    }
    label_error->setText(error);
    buttonBox->button(QDialogButtonBox::Ok)->setEnabled(error == "");
}