#include "headerfiles/dialog_diff_gen.h"

#include <QFileDialog>




DialogDiffGen::DialogDiffGen(QWidget *parent)
    : QDialog(parent)
{
    setupUi(this);
    setWindowTitle("Generate patch");
    label_error->setStyleSheet("QLabel { color : red; }");

    connect(pushButton  , SIGNAL(clicked()), this, SLOT(onSelectOld()));
    connect(pushButton_2, SIGNAL(clicked()), this, SLOT(onSelectNew()));
    connect(pushButton_3, SIGNAL(clicked()), this, SLOT(onSelectDiff()));
    connect(lineEdit  , SIGNAL(textChanged(const QString &)), this, SLOT(onValidateInputs()));
    connect(lineEdit_2, SIGNAL(textChanged(const QString &)), this, SLOT(onValidateInputs()));
    connect(lineEdit_3, SIGNAL(textChanged(const QString &)), this, SLOT(onValidateInputs()));

    onValidateInputs();
}

DialogDiffGen::~DialogDiffGen()
{
}

bool DialogDiffGen::getGenerationType()
{
    return radioButton->isChecked();
}

QString DialogDiffGen::getOld()
{
    return lineEdit->text();
}

QString DialogDiffGen::getNew()
{
    return lineEdit_2->text();
}

QString DialogDiffGen::getPatch()
{
    return lineEdit_3->text();
}

void DialogDiffGen::onSelectOld()
{
    lineEdit->setText(selectFile(FileType::Any,0));
}

void DialogDiffGen::onSelectNew()
{
    lineEdit_2->setText(selectFile(FileType::Any,1));
}

void DialogDiffGen::onSelectDiff()
{
    lineEdit_3->setText(selectFile(FileType::Diff));
}

QString DialogDiffGen::selectFile(FileType _f ,int _row)
{
    QString header = _f == FileType::Any ? "Select file" : "Select patch file";
    QString FileType = _f == FileType::Any ? "" : "Patch (*.diff *.patch);;";
    FileType += "All files (*.*)";
    QString dir = "";
    if (_f==FileType::Any)
    {
        dir = QFileDialog::getOpenFileName(this, header, _row == 0 ? lineEdit->text() : lineEdit_2->text(), FileType);

    }
    else
    {
        dir = QFileDialog::getSaveFileName(this, "",lineEdit_3->text(), FileType);
    }
    
    return dir;
}

void DialogDiffGen::onValidateInputs()
{
    QString oldError = "Old file doesn't exist";
    QString diffError = "New file doesn't exist";
    bool fileOld = QFileInfo(lineEdit->text()).isFile();
    bool fileNew = QFileInfo(lineEdit_2->text()).isFile();
    bool fileDiff = lineEdit_3->text()!="";

    
    QString error = "";
    if (!fileOld)
    {
        error = oldError;
        if (!fileNew)
        {
            error.append(", ");
            error.append(diffError);
        }
    }
    else
    {
        if (!fileNew)
        {
            error = diffError;
        }
    }
    if (!fileDiff) {
        if (!fileOld || !fileNew)
        {
            error.append(", ");
        }
        error.append("Output is empty");
    }
    if (!fileOld || !fileNew || !fileDiff)
        error.append(".");
    label_error->setText(error);
    buttonBox->button(QDialogButtonBox::Ok)->setEnabled(error == "");
}