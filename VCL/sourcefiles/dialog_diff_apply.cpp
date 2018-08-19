#include "headerfiles/dialog_diff_apply.h"

#include <QFileDialog>

DialogDiffApply::DialogDiffApply(QWidget *parent)
    : QDialog(parent)
{
    setupUi(this);
    setWindowTitle("Apply patch");
    label_error->setStyleSheet("QLabel { color : red; }");

    connect(pushButton, SIGNAL(clicked()), this, SLOT(onSelectBase()));
    connect(pushButton_2, SIGNAL(clicked()), this, SLOT(onSelectDiff()));
    connect(lineEdit, SIGNAL(textChanged(const QString &)), this, SLOT(onValidateInputs()));
    connect(lineEdit_2, SIGNAL(textChanged(const QString &)), this, SLOT(onValidateInputs()));
    onValidateInputs();
}

DialogDiffApply::~DialogDiffApply()
{
}

QString DialogDiffApply::selectFile(fileType _f)
{
    QString header = _f == fileType::BaseFile ? "Select base file" : "Select patch file";
    QString fileType = _f == fileType::BaseFile ? "" : "Patch (*.diff *.patch);;";
    fileType += "All files (*.*)";
    QString dir = QFileDialog::getOpenFileName(this, header, _f == fileType::BaseFile ? lineEdit->text(): lineEdit_2->text(), fileType);
    return dir;
}

void DialogDiffApply::onSelectBase()
{
    lineEdit->setText(selectFile(fileType::BaseFile));
}

void DialogDiffApply::onSelectDiff()
{
    lineEdit_2->setText(selectFile(fileType::DiffFile));
}

void DialogDiffApply::onValidateInputs()
{
    QString baseError = "Base file doesn't exist";
    QString diffError = "Patch file doesn't exist";
    bool base = QFileInfo(lineEdit->text()).isFile();
    bool diff = QFileInfo(lineEdit_2->text()).isFile();
    QString error = "";
    if (!base) 
    {
        error = baseError;
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
    buttonBox->button(QDialogButtonBox::Ok)->setEnabled(error=="");
}

QString DialogDiffApply::getBasePath()
{
    return lineEdit->text();
}

QString DialogDiffApply::getDiffPath()
{
    return lineEdit_2->text();
}
