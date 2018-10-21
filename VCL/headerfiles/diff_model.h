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
    void dumpBuffors(DT::diffRowData& _removed, DT::diffRowData& _added);
public:
    enum version
    {
        left = 0,
        right,
        leftOnRight,
        RightOnLeft
    };

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

public slots:
    void setVersion(QModelIndex _index, version _how);
};

#endif // !DIFFMODEL_H