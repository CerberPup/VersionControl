#ifndef DIALOG_SETTINGS_H
#define DIALOG_SETTINGS_H

#include "GeneratedFiles/ui_dialog_settings.h"
#include "GeneratedFiles/ui_dialog_settings_color.h" 
#include "GeneratedFiles/ui_dialog_settings_command.h" 
#include "headerfiles/settings_model.h"

#include <QDialog>
#include <QLineEdit>

//////////////////////////Containers/////////////////////////////////
class CommandPickingWidget :public QWidget, public Ui::DialogSettingsCommand
{
    Q_OBJECT

private:
    QString m_key;
    Ui::DialogSettingsCommand* ui;

private slots:
    void onSelectExe();
    void onApply();

public:
    CommandPickingWidget(QString label, QString key, QWidget* parrent);
    ~CommandPickingWidget();

};

class FontPickingWidget :public QWidget
{
    Q_OBJECT

private:
    QString m_key;
    QLabel* m_fontLabel;

private slots:
    void onFontChoose();

public:
    FontPickingWidget(QString label, QString key, QWidget* parrent);

signals:
    void fontChanged();

};

class ColorPickingWidget :public QWidget
{
    Q_OBJECT

public:
    ColorPickingWidget(QString label, QString key, QWidget* parrent);

private:
    QString m_key;
    QLabel* m_colorLabel;

private slots:
    void onColorChoose();
};

/////////////////////////////////////////////////////////////////////

class DialogSettings : public QDialog, public Ui::DialogSettings
{
    Q_OBJECT

private:
    SettingsModel m_model;
    Ui::DialogSettingsColor* wdg;
    QList<QHBoxLayout*> m_rows;

    void createRow(QString label, QString key, SettingsModel::keyType type);

private slots:
    void onSelectedItem(const QModelIndex &index);
public:
    DialogSettings(QWidget *parent);
    ~DialogSettings();

signals:
    void fontChanged();
};

#endif // !DIALOG_SETTINGS_H
