#ifndef DIFFMODEL_H
#define DIFFMODEL_H

#include "data_objects.h"

#include <list>

#include <QAbstractListModel>
#include <QFontMetrics>
#include <QMetaType>

class DiffModel : public QAbstractListModel
{
	Q_OBJECT
private:
    QString m_sourceFileName;
    int m_numberWidth;
    void endResetModel();
	QFontMetrics m_FontMetrics;
	std::list<DT::diffRowData> m_oldFileData;
	std::list<DT::diffRowData> m_newFileData;
	QSize m_oldFileViewSize;
	QSize m_newFileViewSize;
public:
	DiffModel(QObject *parent);
	~DiffModel();
    QString getSourceFileName();
    void setFontMetrics(QFontMetrics _FontMetrics);
    std::list<QString> getOutputFileData();
	int rowCount(const QModelIndex &parent = QModelIndex()) const;
	int columnCount(const QModelIndex &parent = QModelIndex()) const;
	bool loadFileAndDiff(std::string File, std::string DiffFile);
	QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
	void setOldFileViewSize(QSize _size);
	void setNewFileViewSize(QSize _size);
};

#endif // !DIFFMODEL_H