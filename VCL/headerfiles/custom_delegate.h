#ifndef CUSTOM_DELEGATE_H
#define CUSTOM_DELEGATE_H

#include <QListView>
#include <QPainter>
#include <QStyledItemDelegate>

class CustomDelegate : public QStyledItemDelegate
{
	Q_OBJECT
private:
    void paintNumber(QPainter * painter, const QStyleOptionViewItem & option, const QModelIndex & index) const;

	QFontMetrics m_fontMetrics;
	QFont m_font;
    //10, 17, 24, 31 - based on maximum row number width
    int numberWidth = 0;
public:
	CustomDelegate(QObject *parent);
	~CustomDelegate();

	QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const;
	void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    void setNumberWidth(int maxRow);
};

#endif // !CUSTOM_DELEGATE_H