#include "headerfiles/settings_model.h"
#include "headerfiles/config_manager.h"
SettingsModel::SettingsModel(QObject *parent)
    : QStandardItemModel(parent)
{
    setHorizontalHeaderItem(0, new QStandardItem(QString("Key")));
    initialize();
}

SettingsModel::~SettingsModel()
{
}

void SettingsModel::addTreeItem(QString key)
{
    QStringList sub = key.split('/');
    QString parrent = sub.takeFirst();
    QStandardItem *rootItem = invisibleRootItem();
    for (int i = 0; i < rootItem->rowCount();)
    {
        if (rootItem->child(i)->text()==parrent)
        {
            rootItem = rootItem->child(i);
            parrent = sub.takeFirst();
            i = 0;
            continue;
        }
        i++;
    }
    while (parrent !="Foreground" && parrent != "Background")
    {
        QStandardItem *item = new QStandardItem(parrent);
        item->setSelectable(false);
        item->setEditable(false);
        rootItem->appendRow(item);
        rootItem = item;
        if (sub.isEmpty())
            break;
        parrent = sub.takeFirst();
    }
    rootItem->setSelectable(true);
    QStringList keys = rootItem->data(Qt::UserRole).toStringList();
    keys.append(key);
    rootItem->setData(keys, Qt::UserRole);
    //static_cast<SettingsModelItem*>(rootItem)->addKey(key);
}

void SettingsModel::initialize() 
{
    for (int i = 0; i < static_cast<int>(ConfigKeys::Colors::COUNT); i++)
    {
        QString key = ConfigKeys::getColorKey(static_cast<ConfigKeys::Colors>(i));
        addTreeItem(key);
    }

}