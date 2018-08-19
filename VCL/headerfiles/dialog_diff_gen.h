#ifndef DIALOG_DIFF_GEN_H
#define DIALOG_DIFF_GEN_H

#include "ui_dialog_diffGen.h"

#include <QDialog>

class DialogDiffGen : public QDialog, public Ui::DialogDiffGen
{
    Q_OBJECT

private slots:
    void onValidateInputs();

public:
    DialogDiffGen(QWidget *parent);
    ~DialogDiffGen();
};

#endif // !DIALOG_DIFF_GEN_H