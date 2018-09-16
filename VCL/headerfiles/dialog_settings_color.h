#ifndef DIALOG_SETTINGS_COLOR_H
#define DIALOG_SETTINGS_COLOR_H

#include "GeneratedFiles/ui_dialog_settings_color.h"

#include <QDialog>

class DialogSettings : public QDialog, public Ui::DialogSettingsColor
{
    Q_OBJECT

private:

public:
    DialogSettings(QWidget *parent);
    ~DialogSettings();

};

#endif // !DIALOG_SETTINGS_H