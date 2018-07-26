#ifndef MODIFIED_FILE_SYSTEM_MODEL_H
#define MODIFIED_FILE_SYSTEM_MODEL_H

#include <QFileSystemModel>

class ModifiedFileSystemModel : public QFileSystemModel
{
	Q_OBJECT

public:
	QVariant data(const QModelIndex& index, int role) const;
	ModifiedFileSystemModel(QObject *parent);
	~ModifiedFileSystemModel();
};
#endif