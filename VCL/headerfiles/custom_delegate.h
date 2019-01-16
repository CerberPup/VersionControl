#ifndef CUSTOM_DELEGATE_H
#define CUSTOM_DELEGATE_H

#include <QListView>
#include <QPainter>
#include <QStyledItemDelegate>

class CustomDelegate : public QStyledItemDelegate
{
	Q_OBJECT
private:
    //prints number adjoining to line
    void paintNumber(QPainter * painter, const QStyleOptionViewItem & option, const QModelIndex & index) const;
    //number of loaded rows.
    int maxRow;
    //widest line number
    QSize maxLineNumberSize;

public slots:
    void onFontChanged();
public:
	CustomDelegate(QObject *parent);
	~CustomDelegate();

	QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const;
    //paints line with linenumber
	void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    //sets maxLineNumberSize variable
    void maxNumber(int maxRow);
    //getter for maxLineNumberSize
    QSize getLineNumberSize() const;
};

#endif // !CUSTOM_DELEGATE_H