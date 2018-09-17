#include "headerfiles/custom_delegate.h"

#include "headerfiles/config_manager.h"
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

    painter->setBrush(
        index.row()%2==0
        ? ConfigManager::getInstance().getQColor(ConfigKeys::Colors::DiffWindow_lineNumberEvenBackground) 
        : ConfigManager::getInstance().getQColor(ConfigKeys::Colors::DiffWindow_lineNumberOddBackground));
    QRect numberArea(option.rect.topLeft(), QSize(numberWidth, option.rect.height()));
    painter->drawRect(numberArea);
    painter->setPen(
        index.row() % 2 == 0
        ? ConfigManager::getInstance().getQColor(ConfigKeys::Colors::DiffWindow_lineNumberEvenForeground)
        : ConfigManager::getInstance().getQColor(ConfigKeys::Colors::DiffWindow_lineNumberOddForeground));
    QString str(std::string("" + std::to_string(index.row()+1) + ':').c_str());
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
    std::map<DT::lineStatus, QColor> status2BackGroundColor;
    std::map<DT::lineStatus, QColor> status2ForeGroundColor;
    if (option.state & QStyle::State_Selected || option.state & QStyle::StateFlag::State_MouseOver)
    {
        status2BackGroundColor[DT::lineStatus::Added] = ConfigManager::getInstance().getQColor(ConfigKeys::Colors::DiffWindow_mouseHover);
        status2BackGroundColor[DT::lineStatus::Changed] = status2BackGroundColor[DT::lineStatus::Added];
        status2BackGroundColor[DT::lineStatus::Unchanged] = status2BackGroundColor[DT::lineStatus::Added];
        status2BackGroundColor[DT::lineStatus::Removed] = status2BackGroundColor[DT::lineStatus::Added];
    }
    else
    {
        status2BackGroundColor[DT::lineStatus::Added] = ConfigManager::getInstance().getQColor(ConfigKeys::Colors::DiffWindow_addedTextBackGround);
        status2BackGroundColor[DT::lineStatus::Changed] = ConfigManager::getInstance().getQColor(ConfigKeys::Colors::DiffWindow_changedTextBackGround);
        status2BackGroundColor[DT::lineStatus::Unchanged] = ConfigManager::getInstance().getQColor(ConfigKeys::Colors::DiffWindow_unchangedTextBackGround);
        status2BackGroundColor[DT::lineStatus::Removed] = ConfigManager::getInstance().getQColor(ConfigKeys::Colors::DiffWindow_removedTextBackGround);
    }

    status2ForeGroundColor[DT::lineStatus::Added] = ConfigManager::getInstance().getQColor(ConfigKeys::Colors::DiffWindow_addedTextForeground);
    status2ForeGroundColor[DT::lineStatus::Changed] = ConfigManager::getInstance().getQColor(ConfigKeys::Colors::DiffWindow_changedTextForeground);
    status2ForeGroundColor[DT::lineStatus::Unchanged] = ConfigManager::getInstance().getQColor(ConfigKeys::Colors::DiffWindow_unchangedTextForeground);
    status2ForeGroundColor[DT::lineStatus::Removed] = ConfigManager::getInstance().getQColor(ConfigKeys::Colors::DiffWindow_removedTextForeground);

    if (option.state & QStyle::State_Selected || option.state & QStyle::StateFlag::State_MouseOver)
    {
        painter->setBrush(status2BackGroundColor[DT::lineStatus::Unchanged]);
        painter->drawRect(option.rect);
    }
    paintNumber(painter, option, index);
    QRect paintArea = option.rect;
	paintArea.adjust(numberWidth, 0, -numberWidth, 0);
	QRect prev(paintArea.topLeft(),QSize(0,0));
	QSize viewSize = index.data(Qt::UserRole).toSize();
    viewSize.setWidth(viewSize.width() - numberWidth - 20/*scrollbar width*/);
	for (int i = 0; i < data.size(); i++)
	{
		QRect tmp = data.lineTextSize(m_fontMetrics, viewSize, i);
		paintArea = QRect(paintArea.left(), paintArea.top() + prev.height(), tmp.width(), tmp.height());
		prev = tmp;
		prev.adjust(0, 0, 0, 0);
		std::pair<DT::lineStatus, QString> var = data[i];
		QString toDisplay = var.second;
        if (*toDisplay.rbegin() == '\n')
            toDisplay.remove(toDisplay.size() - 1, 1);

        painter->save();
        painter->setBrush(status2BackGroundColor[var.first]);
        painter->drawRect(paintArea);
        painter->restore();
		painter->setPen(status2ForeGroundColor[var.first]);
		painter->drawText(paintArea, toDisplay);

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
