#ifndef DATA_OBJECTS_H
#define DATA_OBJECTS_H

#include <list>
#include <QMetaType>
#include <QString>
#include <QFontMetrics>

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
		void clear() { data.clear(); }
		size_t size() { return data.size(); }
		std::pair<lineStatus, QString>& operator[](int i) { return *std::next(data.begin(),i); }
		QString wholeText() const
		{
			QString returnVal;
			for each (std::pair<lineStatus, QString> var in data)
			{
				returnVal += var.second;
			}
			returnVal.remove(returnVal.size() - 1, 1);
			return returnVal;
		}
		QRect lineTextSize(const QFontMetrics& _metric, QSize _viewSize, int index) {
			QString a = operator[](index).second;
			a.remove(a.size() - 1, 1);
			QRect tmp = _metric.boundingRect(QRect(QPoint(0, 0), _viewSize), Qt::TextWordWrap, a);
			//tmp.adjust(0, 0, 0, -3);
			return tmp;
		}
		QSize wholeTextSize(const QFontMetrics& _metric,QSize _viewSize) const {
			QSize tmp = _metric.boundingRect(QRect(QPoint(0, 0), _viewSize), Qt::TextWordWrap, wholeText()).size();
			//tmp.setHeight(tmp.height()-data.size()*3);
			return tmp;
		}
	};

	Q_DECLARE_METATYPE(diffRowData);


}
#endif // DATA_OBJECTS_H