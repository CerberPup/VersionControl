#ifndef DATA_OBJECTS_H
#define DATA_OBJECTS_H

#include <list>

#include <QFontMetrics>
#include <QMetaType>
#include <QString>
#include <QTextLayout>

namespace DT
{

	enum lineStatus
	{
		Added = 0,
		Changed,
		Removed,
		Unchanged,
        Comment,
        Conflicted
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
                        for (size_t i = 0; i < data.size(); i++)
			{
				returnVal += (*std::next(data.begin(),i)).second;
			}
			returnVal.remove(returnVal.size() - 1, 1);
			return returnVal;
		}
		QRect lineTextSize(const QFontMetrics& _metric, QSize _viewSize, int index) {
			QString a = operator[](index).second;
			a.remove(a.size() - 1, 1);
			QRect tmp = _metric.boundingRect(QRect(QPoint(0, 0), _viewSize), Qt::TextWordWrap, a);
			return tmp;
		}
		QSize wholeTextSize(const QFontMetrics& _metric,QSize _viewSize) const {
			QSize tmp = _metric.boundingRect(QRect(QPoint(0, 0), _viewSize), Qt::TextWordWrap, wholeText()).size();
			return tmp;
		}
	};
}

	Q_DECLARE_METATYPE(DT::diffRowData);
#endif // DATA_OBJECTS_H
