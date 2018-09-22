#ifndef DIFFMODEL_H
#define DIFFMODEL_H

#include "data_objects.h"
#include "custom_delegate.h"

#include <list>

#include <QAbstractListModel>
#include <QFontMetrics>
#include <QMetaType>

class DiffModel : public QAbstractListModel
{
	Q_OBJECT
private:
    QString m_sourceFileName;
	std::list<DT::diffRowData> m_oldFileData;
	std::list<DT::diffRowData> m_newFileData;
	QSize m_oldFileViewSize;
	QSize m_newFileViewSize;
    const CustomDelegate* m_del;
public:
	DiffModel(QObject *parent, CustomDelegate *_delegate);
	~DiffModel();
    QString getSourceFileName();
    std::list<QString> getOutputFileData();
	int rowCount(const QModelIndex &parent = QModelIndex()) const;
	int columnCount(const QModelIndex &parent = QModelIndex()) const;
	bool loadFileAndDiff(std::string File, std::string DiffFile);
	QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
	void setOldFileViewSize(QSize _size);
	void setNewFileViewSize(QSize _size);
};

#endif // !DIFFMODEL_H