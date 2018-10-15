#include "headerfiles/diff_model.h"

#include <algorithm>
#include <fstream>
#include <QApplication>
#include <regex>

namespace
{
	QString replaceTabs(QString input)
	{
		/*if (input.size() != 0)
		{
			int it = 0;

			while (input.at(it) == '\t')
		    {
				it++;
			}
			std::u32string tmp = input.toStdU32String();
			std::u32string tab = U"→→→→";
			tmp.erase(tmp.begin(), tmp.begin() + it);//― → ·
			for (; it > 0; it--)
				tmp = tab + tmp;
			//tmp.insert(tmp.begin(), it * 4, U'·');
			input = QString::fromStdU32String(tmp);
		}*/
		return input;
	}

    void dumpBuffors(DT::diffRowData& _removed, DT::diffRowData& _added , std::list<DT::diffRowData>& _oldContainer, std::list<DT::diffRowData>& _newContainer)
    {
        if (_removed.size() != 0 || _added.size() != 0)
        {
            if (_removed.size() != 0 && _added.size() != 0)
            {
                _newContainer.push_back(_added);
                _oldContainer.push_back(_removed);
            }
            else if (_removed.size() != 0)
            {
                _newContainer.push_back(DT::diffRowData(std::make_pair(DT::lineStatus::Changed, "")));
                _oldContainer.push_back(_removed);
            }
            else if (_added.size() != 0)
            {
                _newContainer.push_back(_added);
                _oldContainer.push_back(DT::diffRowData(std::make_pair(DT::lineStatus::Changed, "")));
            }
            _removed.clear();
            _added.clear();
        }
    }

    class SinglePatch {
        std::list<std::pair<QString,DT::lineStatus>> data;
        //std::list<QString>::iterator cloneFrom;
    public:
        SinglePatch(/*std::list<QString>::iterator& latestCloned*/)/*:cloneFrom(latestCloned)*/ {}

        void addLine(QString _line, DT::lineStatus _status)
        {
            data.push_back(std::make_pair(_line,_status));
        }

        std::list<std::pair<QString, DT::lineStatus>>& getData()
        {
            return data;
        }

        bool apply(std::list<DT::diffRowData>& _oldContainer, std::list<DT::diffRowData>& _newContainer, std::list<QString>& _rawData)
        {
            bool canWork = true;
            std::list<QString>::iterator beginning = _rawData.begin();
            std::list<QString>::iterator last;
            while (canWork)
            {
                beginning = std::find_if(beginning, _rawData.end(), [this](QString row)->bool {return getData().begin()->first == row; });
                if (beginning != _rawData.end())
                {
                    std::list<std::pair<QString, DT::lineStatus>>::iterator dataIt = data.begin();
                    for (std::list<QString>::iterator from = beginning; from != _rawData.end(); from++)
                    {
                        while (dataIt!= data.end() && !(dataIt->second == DT::Unchanged || dataIt->second == DT::Removed))
                        {
                            dataIt = std::next(dataIt, 1);
                        }
                        if (dataIt->first == *from)
                        {
                            dataIt = std::next(dataIt, 1);
                            if (dataIt == data.end())
                            {
                                last = from;
                                canWork = false;
                                break;
                            }
                        }
                        else
                        {
                            beginning = std::next(beginning, 1);
                            break;
                        }
                    }

                }
                else
                {
                    canWork = false;
                }
            }
            if (beginning != _rawData.end())
            {
                //apply patch
                for (std::list<QString>::iterator unchanged = _rawData.begin(); unchanged != beginning; unchanged++)
                {
                    _oldContainer.push_back(DT::diffRowData(std::make_pair(DT::lineStatus::Unchanged, *unchanged)));
                    _newContainer.push_back(DT::diffRowData(std::make_pair(DT::lineStatus::Unchanged, *unchanged)));
                }
                _rawData.erase(_rawData.begin(),std::next(last,1));

                DT::diffRowData buforOld;
                DT::diffRowData buforNew;
                for (auto row: data)
                {
                    switch (row.second)
                    {
                    case DT::lineStatus::Added:
                        buforNew.data.push_back((std::make_pair(DT::lineStatus::Added, row.first)));
                        break;
                    case DT::lineStatus::Removed:
                        buforOld.data.push_back((std::make_pair(DT::lineStatus::Removed, row.first)));
                        break;
                    case DT::lineStatus::Unchanged:
                        dumpBuffors(buforOld, buforNew, _oldContainer, _newContainer);
                        _newContainer.push_back(DT::diffRowData(std::make_pair(DT::lineStatus::Unchanged, row.first)));
                        _oldContainer.push_back(DT::diffRowData(std::make_pair(DT::lineStatus::Unchanged, row.first)));
                        break;
                    default:
                        break;
                    }
                }
                dumpBuffors(buforOld, buforNew, _oldContainer, _newContainer);
                return true;
            }
            else
            {

                return false;
            }
        }
    };

}

/*void DiffModel::dumpBuffors(DT::diffRowData& _removed, DT::diffRowData& _added)
{
    if (_removed.size() != 0 || _added.size() != 0)
    {
        if (_removed.size() != 0 && _added.size() != 0)
        {
            m_oldFileData.push_back(_removed);
            m_newFileData.push_back(_added);
        }
        else if (_removed.size() != 0)
        {
            m_newFileData.push_back(DT::diffRowData(std::make_pair(DT::lineStatus::Changed, "")));
            m_oldFileData.push_back(_removed);
        }
        else if (_added.size() != 0)
        {
            m_newFileData.push_back(_added);
            m_oldFileData.push_back(DT::diffRowData(std::make_pair(DT::lineStatus::Changed, "")));
        }
        _removed.clear();
        _added.clear();
    }
}*/

DiffModel::DiffModel(QObject *parent, CustomDelegate *_delegate)
	: QAbstractListModel(parent)
	, m_newFileViewSize(0,0)
	, m_oldFileViewSize(0,0)
    , m_del(_delegate)
    , m_sourceFileName("")
{
	
}

DiffModel::~DiffModel()
{
}

QString DiffModel::getSourceFileName()
{
    return m_sourceFileName;
}

std::list<QString> DiffModel::getOutputFileData()
{
    std::list<QString> a;
    for (size_t i = 0; i < m_newFileData.size(); i++)
    {
        DT::diffRowData item = *std::next(m_newFileData.begin(),i);
        QString text = item.wholeText();
        if (text =="")
        {
            if (std::next(m_oldFileData.begin(), i)->wholeText()=="")
            {
                a.push_back(text);
            }
        }
        else
        {
            a.push_back(text);
        }
    }

    return a;
}

int DiffModel::rowCount(const QModelIndex&) const
{
	return static_cast<int>(m_oldFileData.size() < m_newFileData.size() ? m_oldFileData.size() : m_newFileData.size());
}

int DiffModel::columnCount(const QModelIndex&) const
{
	return 2;
}
/*
bool DiffModel::loadFileAndDiff(std::string File, std::string DiffFile)
{
    beginResetModel();
	std::list<QString>rawData;
	m_oldFileData.clear();
	m_newFileData.clear();
	std::ifstream reader;
	std::string bufor;
	reader.open(File);
	if (reader.good())
	{
		while (!reader.eof())
		{
			std::getline(reader, bufor);
			bufor.insert(bufor.end(), '\n');
			QString tmp = replaceTabs(QString(bufor.c_str()));
			rawData.push_back(tmp);
		}
	}
	reader.close();
	reader.open(DiffFile);
	if (reader.good())
	{
		int oldStartPrev = 0;
		int oldNumberPrev = 0;
		int oldStart = 0;
		int oldNumber = 0;
		int newStart = 0;
		int newNumber = 0;
		int linesAdded = 0;
		bool afterSection = false;

        std::getline(reader, bufor);

        std::regex pattern("^--- (.*)\\t");
        std::smatch pieces_match;
        std::regex_search(bufor, pieces_match, pattern);
        m_sourceFileName = QString(pieces_match[1].str().c_str());
		while (!reader.eof())
		{
			if (!afterSection)
				std::getline(reader, bufor);
			if (bufor[0] == '@' && bufor[1] == '@') 
            {
				std::regex pattern("\\d+");
				std::sregex_iterator next(bufor.begin(), bufor.end(), pattern);
				oldStartPrev = oldStart;
				oldNumberPrev = oldNumber;
				oldStart = atoi((*next).str().c_str());
				oldNumber = atoi((*++next).str().c_str());
				newStart = atoi((*++next).str().c_str());
				newNumber = atoi((*++next).str().c_str());
                int i = oldStartPrev + oldNumberPrev;
                i = i < 1 ? 0 : i-1;
				for (; i < oldStart-1; i++)
				{
                    if (i>=rawData.size())
                    {
                        return false;
                    }
					m_newFileData.push_back(DT::diffRowData(std::make_pair(DT::lineStatus::Unchanged, *std::next(rawData.begin(),i))));
					m_oldFileData.push_back(DT::diffRowData(std::make_pair(DT::lineStatus::Unchanged, *std::next(rawData.begin(),i))));
				}
				bool nextSection = false;
				DT::diffRowData oldRow;
				DT::diffRowData newRow;
				while (!reader.eof() && !nextSection)
				{

					std::getline(reader, bufor);
					bufor.insert(bufor.end(), '\n');
					switch (bufor[0])
					{
					case ' ':
					{
						bufor.erase(bufor.begin());
						QString qstring = replaceTabs(QString(bufor.c_str()));
                        dumpBuffors(oldRow,newRow);
						m_newFileData.push_back(DT::diffRowData(std::make_pair(DT::lineStatus::Unchanged, qstring)));
						m_oldFileData.push_back(DT::diffRowData(std::make_pair(DT::lineStatus::Unchanged, qstring)));
						break;
					}
					case '-':
					{
						bufor.erase(bufor.begin());
						QString qstring = replaceTabs(QString(bufor.c_str()));
						oldRow.data.push_back((std::make_pair(DT::lineStatus::Removed, qstring)));
						break;
					}
					
					case '+':
					{
						bufor.erase(bufor.begin());
						QString qstring = replaceTabs(QString(bufor.c_str()));
						newRow.data.push_back((std::make_pair(DT::lineStatus::Added, qstring)));
						break;
					}
                    case '\\':
                    {
                        linesAdded--;
                        break;
                    }
					default:
                        dumpBuffors(oldRow, newRow);
						nextSection = true;
						break;
					}
					linesAdded++;
				}
				afterSection = true;
				continue;
			}
			afterSection = false;
		}
        int i = oldStart + oldNumber;
        i = i < 1 ? 0 : i - 1;
        for (; i < static_cast<int>(rawData.size()); i++)
        {
            m_newFileData.push_back(DT::diffRowData(std::make_pair(DT::lineStatus::Unchanged, *std::next(rawData.begin(), i))));
            m_oldFileData.push_back(DT::diffRowData(std::make_pair(DT::lineStatus::Unchanged, *std::next(rawData.begin(), i))));
        }
	}
	reader.close();
    endResetModel();
	return true;
}*/

bool DiffModel::loadFileAndDiff(std::string File, std::string DiffFile)
{
    beginResetModel();
    std::list<QString>rawData;
    m_oldFileData.clear();
    m_newFileData.clear();
    std::ifstream reader;
    std::string bufor;
    reader.open(File);
    if (reader.good())
    {
        while (!reader.eof())
        {
            std::getline(reader, bufor);
            bufor.insert(bufor.end(), '\n');
            QString tmp = replaceTabs(QString(bufor.c_str()));
            rawData.push_back(tmp);
        }
    }
    reader.close();
    reader.open(DiffFile);
    std::list<QString>::iterator latestCloned = rawData.begin();
    if (reader.good())
    {
        bool afterSection = false;

        std::getline(reader, bufor);

        std::regex pattern("^--- (.*)\\t");
        std::smatch pieces_match;
        std::regex_search(bufor, pieces_match, pattern);
        m_sourceFileName = QString(pieces_match[1].str().c_str());
        while (!reader.eof())
        {
            if (!afterSection)
                std::getline(reader, bufor);
            if (bufor[0] == '@' && bufor[1] == '@')
            {
                SinglePatch patch;
                bool nextSection = false;
                while (!reader.eof() && !nextSection)
                {

                    std::getline(reader, bufor);
                    bufor.insert(bufor.end(), '\n');
                    switch (bufor[0])
                    {
                    case ' ':
                    {
                        bufor.erase(bufor.begin());
                        patch.addLine(bufor.c_str(), DT::lineStatus::Unchanged);
                        break;
                    }
                    case '-':
                    {
                        bufor.erase(bufor.begin());
                        patch.addLine(bufor.c_str(), DT::lineStatus::Removed);
                        break;
                    }

                    case '+':
                    {
                        bufor.erase(bufor.begin());
                        patch.addLine(bufor.c_str(), DT::lineStatus::Added);
                        break;
                    }
                    case '\\':
                    {
                        break;
                    }
                    default:
                        patch.apply(m_oldFileData, m_newFileData, rawData);
                        nextSection = true;
                        break;
                    }
                }
                afterSection = true;
                continue;
            }
            afterSection = false;
        }
    }
    reader.close();
    while (rawData.size()!=0)
    {
        m_newFileData.push_back(DT::diffRowData(std::make_pair(DT::lineStatus::Unchanged, rawData.front())));
        m_oldFileData.push_back(DT::diffRowData(std::make_pair(DT::lineStatus::Unchanged, rawData.front())));
        rawData.pop_front();
    }
    endResetModel();
    return true;
}

QVariant DiffModel::data(const QModelIndex & index, int role) const
{
	//QString a(std::next(changeData.begin(), index.row())->wholeText());
	
	switch (role)
	{
	case Qt::DisplayRole:
		if (index.column() == 0)
		{
			return QVariant::fromValue(*std::next(m_newFileData.begin(), index.row()));
		}
		else if (index.column() == 1)
		{
			return QVariant::fromValue(*std::next(m_oldFileData.begin(), index.row()));
		}
		break;
	case Qt::SizeHintRole:
	{
        QSize newSize = m_newFileViewSize;
        QSize oldSize = m_oldFileViewSize;
        newSize.setWidth(m_newFileViewSize.width() - m_del->getLineNumberSize().width());
        oldSize.setWidth(m_oldFileViewSize.width() - m_del->getLineNumberSize().width());
		newSize = std::next(m_newFileData.begin(), index.row())->wholeTextSize(QApplication::fontMetrics(), newSize);
		oldSize = std::next(m_oldFileData.begin(), index.row())->wholeTextSize(QApplication::fontMetrics(), oldSize);

		return QSize(index.column() == 0? newSize.width() : oldSize.width(), newSize.height() > oldSize.height() ? newSize.height() : oldSize.height());
		break;
	}
	case Qt::UserRole:
	{
		if (index.column() == 0)
		{
			return m_newFileViewSize;
		}
		else if (index.column() == 1)
		{
			return m_oldFileViewSize;
		}
		break;
	}
	default:
		break;
	}
	return QVariant();
}

void DiffModel::setOldFileViewSize(QSize _size)
{
	m_oldFileViewSize = _size;
}

void DiffModel::setNewFileViewSize(QSize _size)
{
	beginResetModel();
	m_newFileViewSize = _size;
	endResetModel();
}
