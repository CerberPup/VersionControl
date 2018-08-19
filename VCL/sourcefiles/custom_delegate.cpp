#include "headerfiles/custom_delegate.h"

#include "headerfiles/data_objects.h"
#include "headerfiles/diff_model.h"

CustomDelegate::CustomDelegate(QObject *parent)
	: QStyledItemDelegate(parent)
	, m_font (QFont("Roboto"))
	, m_fontMetrics(QFontMetrics(QFont("Roboto")))
{

}

CustomDelegate::~CustomDelegate()
{
}

QSize CustomDelegate::sizeHint(const QStyleOptionViewItem &/*option*/, const QModelIndex &index) const
{
	return index.data(Qt::SizeHintRole).toSize();
}

void CustomDelegate::paintNumber(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    painter->save();

    painter->setBrush(index.row()%2==0? QColor(120, 120, 120): QColor(150, 150, 150));
    QRect numberArea(option.rect.topLeft(), QSize(numberWidth, option.rect.height()));
    painter->drawRect(numberArea);
    painter->setPen(QColor(255, 255, 255));
    QString str(std::string("" + std::to_string(index.row()) + ':').c_str());
    painter->drawText(numberArea,str, QTextOption(Qt::AlignmentFlag::AlignRight));
    painter->restore();
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
    paintNumber(painter, option, index);
    QRect paintArea = option.rect;
	paintArea.adjust(numberWidth, 0, -numberWidth, 0);
	QRect prev(paintArea.topLeft(),QSize(0,0));
	QSize viewSize = index.data(Qt::UserRole).toSize();
    viewSize.setWidth(viewSize.width() - numberWidth - 20/*scrollbar width*/);
	for (int i = 0; i < data.size(); i++)
	{
		QRect tmp = data.lineTextSize(m_fontMetrics, viewSize, i);
        //tmp.setWidth(tmp.width()- numberWidth);
		paintArea = QRect(paintArea.left(), paintArea.top() + prev.height(), tmp.width(), tmp.height());
		prev = tmp;
		prev.adjust(0, 0, 0, 0);
		std::pair<DT::lineStatus, QString> var = data[i];
		QString toDisplay = var.second;
        if (*toDisplay.rbegin() == '\n')
            toDisplay.remove(toDisplay.size() - 1, 1);
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

void CustomDelegate::setNumberWidth(int maxRow)
{
    if (maxRow < 10)
    {
        numberWidth = 10;
    }else if (maxRow < 100)
    {
        numberWidth = 17;
    }else if (maxRow < 1000)
    {
        numberWidth = 24;
    }else
    {
        numberWidth = 31;
    }
}
