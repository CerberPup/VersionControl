#include "customdelegate.h"
#include "diffmodel.h"
#include "dataObjects.h"

CustomDelegate::CustomDelegate(QObject *parent)
	: QStyledItemDelegate(parent)
	, m_font (QFont("Arial"))
	, m_fontMetrics(QFontMetrics(QFont("Arial")))
{

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
	painter->setFont(m_font);
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
		painter->setBrush(Qt::lightGray);
	}
	else
	{
		painter->setBrush(Qt::white);
	}
	if(data[0].first!= DT::lineStatus::Unchanged|| data.size()>1)
		painter->setBrush(QColor(220,220,220));
	if (option.state & QStyle::StateFlag::State_MouseOver)
	{
		painter->setBrush(Qt::lightGray);
	}
	painter->drawRect(option.rect);
	QRect paintArea = option.rect;
	paintArea.adjust(2, 0, 0, 0);
	QRect prev(paintArea.topLeft(),QSize(0,0));
	QSize viewSize = index.data(Qt::UserRole).toSize();
	for (size_t i = 0; i < data.size(); i++)
	{
		QRect tmp = data.lineTextSize(m_fontMetrics, viewSize, i);
		paintArea = QRect(paintArea.left(), paintArea.top() + prev.height(), tmp.width(), tmp.height());
		prev = tmp;
		prev.adjust(0, 0, 0, 0);
		std::pair<DT::lineStatus, QString> var = data[i];
		QString toDisplay = var.second;
		if (var.first == DT::lineStatus::Added)
		{
			painter->setPen(QColor(50, 150, 50));
			painter->drawText(paintArea, toDisplay);
		}
		else if (var.first == DT::lineStatus::Removed)
		{
			painter->setPen(QColor(150, 50, 50));
			painter->drawText(paintArea, toDisplay);
		}
		else
		{
			painter->setPen(Qt::black);
			painter->drawText(paintArea, toDisplay);
		}
	}

	painter->restore();
}