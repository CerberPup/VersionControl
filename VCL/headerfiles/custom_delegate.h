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
    int maxRow;
    QSize maxLineNumberSize;

public slots:
    void onFontChanged();
public:
	CustomDelegate(QObject *parent);
	~CustomDelegate();

	QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const;
	void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    void maxNumber(int maxRow);
    QSize getLineNumberSize() const;
};

#endif // !CUSTOM_DELEGATE_H