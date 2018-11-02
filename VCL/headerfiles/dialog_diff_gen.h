#ifndef DIALOG_DIFF_GEN_H
#define DIALOG_DIFF_GEN_H

#include "GeneratedFiles/ui_dialog_diffGen.h"

#include <QDialog>

class DialogDiffGen : public QDialog, public Ui::DialogDiffGen
{
    Q_OBJECT

private:
    enum FileType {
        Any = 0,
        Diff
    };
    QString selectFile(FileType _f,int _row=0);

private slots:
    void onValidateInputs();
    void onSelectOld();
    void onSelectNew();
    void onSelectDiff();

public:
    enum generatorType {
        program = 0,
        system,
        user
    };

    DialogDiffGen(QWidget *parent);
    ~DialogDiffGen();

    generatorType getGenerationType();
    QString getOld();
    QString getNew();
    QString getPatch();
    
    
};

#endif // !DIALOG_DIFF_GEN_H
