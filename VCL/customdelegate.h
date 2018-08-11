#ifndef CUSTOM_DELEGATE_H
#define CUSTOM_DELEGATE_H

#include <QStyledItemDelegate>
#include <QPainter>
#include <QListView>

class CustomDelegate : public QStyledItemDelegate
{
	Q_OBJECT
private:
	QFontMetrics m_fontMetrics;
	QFont m_font;
public:
	CustomDelegate(QObject *parent);
	~CustomDelegate();
	QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const;
	void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
};

#endif // !CUSTOM_DELEGATE_H