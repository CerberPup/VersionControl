#ifndef SETTINGS_MODEL_H
#define SETTINGS_MODEL_H

#include <QStandardItemModel>

class SettingsModel : public QStandardItemModel
{
    Q_OBJECT

private:
    void initialize();
    void addTreeItem(QString key);
public:
    SettingsModel(QObject *parent);
    ~SettingsModel();
};

#endif // SETTINGS_MODEL_H