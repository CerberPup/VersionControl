#ifndef SETTINGS_MODEL_H
#define SETTINGS_MODEL_H

#include <QStandardItemModel>
#include <QMetaType>

class SettingsModel : public QStandardItemModel
{
    Q_OBJECT

public:
    SettingsModel(QObject *parent);
    ~SettingsModel();
    enum keyType
    {
        Color = 0,
        Font,
        DiffGenerator
    };

private:
    void initialize();
    void addTreeItem(QString key, keyType type);

};

Q_DECLARE_METATYPE(SettingsModel::keyType);
#endif // SETTINGS_MODEL_H