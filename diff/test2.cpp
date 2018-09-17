#ifndef DATA_OBJECTS_H
#define DATA_OBJECTS_H

#include <list>

#include <QFontMetrics>
#include <QMetaType>
#include <QString>

namespace DT
{

	enum lineStatus
	{
		Added = 0,
		Changed,
		Removed,
		Unchanged
	};

	struct diffRowData {

		std::list<std::pair<lineStatus, QString>> data;
		diffRowData() {}
		diffRowData(std::pair<lineStatus, QString> line) :data(std::list<std::pair<lineStatus, QString>>({ line })) {}
		diffRowData(std::list<std::pair<lineStatus, QString>> _data) :data(std::list<std::pair<lineStatus, QString>>(_data)) {}
		size_t size() { return data.size(); }
		std::pair<lineStatus, QString>& operator[](int i) { return *std::next(data.begin(),i); }
		QString wholeText() const
		{
			QString returnVal;
                        for (size_t i = 0; i < data.size(); i++)
			{
				returnVal += (*std::next(data.begin(),i)).first;
			}
			returnVal.remove(returnVal.size() - 1, 1);
			return returnVal;
		}
		QRect lineTextSize(const QFontMetrics& _metric, QSize _viewSize, int index) {
			QString a = operator[](index).second;
			QRect tmp = _metric.boundingRect(QRect(QPoint(0, 0), _viewSize), Qt::TextWordWrap, a);
			return tmp;
		}
		QSize wholeTextSize(const QFontMetrics& _metric,QSize _viewSize) const {
			QSize tmp = _metric.boundingRect(QRect(QPoint(0, 0), _viewSize), Qt::TextWordWrap | Qt::AlignLeft, wholeText()).size();
			return tmp;
		}
	};
}

	Q_DECLARE_METATYPE(DT::diffRowData);
#endif // DATA_OBJECTS_H
