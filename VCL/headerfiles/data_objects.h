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

    //container for single row of data
	struct diffRowData 
    {
		std::list<std::pair<lineStatus, QString>> data; //internal container
		diffRowData() {}
		diffRowData(std::pair<lineStatus, QString> line) :data(std::list<std::pair<lineStatus, QString>>({ line })) {}
		diffRowData(std::list<std::pair<lineStatus, QString>> _data) :data(std::list<std::pair<lineStatus, QString>>(_data)) {}
		void clear() { data.clear(); }

        //Unify type for each item in data
        void setAll(lineStatus _status) {
            for (auto it = data.begin(); it != data.end(); it++)
            {
                *it = std::make_pair(_status, it->second);
            }
        }

		size_t size() { return data.size(); }
        
        //add new data to data container
        diffRowData& operator+=(const diffRowData& right)
        {
            data.insert(data.end(), right.data.cbegin(), right.data.cend());
            return *this;
        }

		std::pair<lineStatus, QString>& operator[](int i) { return *std::next(data.begin(),i); }

        //concatenate data container
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
        //rectangle needed to display single element inside _viewSize
		QRect lineTextSize(const QFontMetrics& _metric, QSize _viewSize, int index) {
			QString a = operator[](index).second;
			a.remove(a.size() - 1, 1); //remove \n
			QRect tmp = _metric.boundingRect(QRect(QPoint(0, 0), _viewSize), Qt::TextWordWrap, a);
			return tmp;
		}

        //calculate how much space is needed to display whole text inside _viewSize
		QSize wholeTextSize(const QFontMetrics& _metric,QSize _viewSize) const {
			QSize tmp = _metric.boundingRect(QRect(QPoint(0, 0), _viewSize), Qt::TextWordWrap, wholeText()).size();
			return tmp;
		}
	};
}

	Q_DECLARE_METATYPE(DT::diffRowData);
#endif // DATA_OBJECTS_H
