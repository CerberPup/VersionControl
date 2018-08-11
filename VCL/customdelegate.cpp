#include "customdelegate.h"
#include "diffmodel.h"
#include "dataObjects.h"

CustomDelegate::CustomDelegate(QObject *parent, QListView* _w1, QListView* _w2)
	: QStyledItemDelegate(parent)
{
	w1 = _w1;
	w2 = _w2;
}

CustomDelegate::~CustomDelegate()
{
}

QSize CustomDelegate::sizeHint(const QStyleOptionViewItem &/*option*/, const QModelIndex &index) const
{
	return index.data(Qt::SizeHintRole).toSize();
}

void CustomDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
	painter->save();
	painter->setClipping(false);
	painter->setFont(QFont("Arial"));
	DT::diffRowData data = index.data().value<DT::diffRowData>();
	painter->setPen(Qt::NoPen);
	if (option.state & QStyle::State_Selected)
	{
		painter->setBrush(Qt::lightGray);
	}
	else
	{
		painter->setBrush(Qt::white);
	}
	if (option.state & QStyle::StateFlag::State_MouseOver)
	{
		painter->setBrush(Qt::white);
	}
	else
	{
		painter->setBrush(Qt::lightGray);
	}
	painter->drawRect(option.rect);
	QRect re = option.rect;
	re.setRight(5000);
	if (data[0].first==DT::lineStatus::Added)
	{
		painter->setBrush(QColor(255, 255, 200));
		painter->drawRect(option.rect);
		painter->setPen(QColor(25, 60, 25));
		painter->drawText(option.rect, data[0].second);
	}
	else
	{
		painter->setPen(Qt::black);
			
		painter->drawText(option.rect, data[0].second);
	}

	painter->restore();
}