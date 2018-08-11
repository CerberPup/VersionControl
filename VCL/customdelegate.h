#ifndef CUSTOM_DELEGATE_H
#define CUSTOM_DELEGATE_H

#include <QStyledItemDelegate>
#include <QPainter>
#include <QListView>

class CustomDelegate : public QStyledItemDelegate
{
	Q_OBJECT
private:
	QListView * w1;
	QListView * w2;
public:
	CustomDelegate(QObject *parent, QListView* w1, QListView* w2);
	~CustomDelegate();
	QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const;
	void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
};

#endif // !CUSTOM_DELEGATE_H