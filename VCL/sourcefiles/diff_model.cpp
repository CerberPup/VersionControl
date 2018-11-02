#include "headerfiles/diff_model.h"

#include <algorithm>
#include <fstream>
#include <QApplication>
#include <regex>

namespace
{
    struct location {
        std::list<QString>::iterator begin;
        std::list<QString>::iterator end;
        bool conflict;
        location(std::list<QString>::iterator _begin, std::list<QString>::iterator _end, bool _conflict):begin(_begin),end(_end),conflict(_conflict) {}
    };

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
        std::vector<location> possibleLocations;

        std::list<DT::diffRowData>m_localNewRowData;
        std::list<DT::diffRowData>m_localOldRowData;

    public:
        SinglePatch(/*std::list<QString>::iterator& latestCloned*/)/*:cloneFrom(latestCloned)*/ {}

        std::vector<location> getPossibleLocations()
        {
            return possibleLocations;
        }
        size_t getNumberOfPossibleLocations()
        {
            return possibleLocations.size();
        }

        void addLine(QString _line, DT::lineStatus _status)
        {
            data.push_back(std::make_pair(_line,_status));
        }

        std::list<std::pair<QString, DT::lineStatus>>& getData()
        {
            return data;
        }

        void updateLocations(std::list<QString>& _rawData)
        {
            bool canWork = true;
            std::list<QString>::iterator beginning = _rawData.begin();
            possibleLocations.clear();
            while (canWork)
            {
                bool conflicted = false;
                beginning = std::find_if(beginning, _rawData.end(), [this](QString row)->bool {return getData().begin()->first == row; });
                if (beginning != _rawData.end())
                {
                    std::list<std::pair<QString, DT::lineStatus>>::iterator dataIt = data.begin();
                    for (std::list<QString>::iterator from = beginning; from != _rawData.end(); from++)
                    {
                        while (dataIt != data.end() && dataIt->second == DT::Added)
                        {
                            dataIt = std::next(dataIt, 1);
                        }
                        if (dataIt->first == *from)
                        {
                            dataIt = std::next(dataIt, 1);
                            if (dataIt == data.end())
                            {
                                possibleLocations.push_back(location(beginning, from, conflicted));
                                beginning = from;
                                break;
                            }
                        }
                        else
                        {
                            auto tmp = std::find_if(from, _rawData.end(), [dataIt](QString row)->bool {return dataIt->first == row; });
                            if (tmp != _rawData.end())
                            {
                                conflicted = true;
                                from = std::prev( tmp,1);
                            }
                            else
                            {
                                beginning = std::next(beginning, 1);
                                break;
                            }
                        }
                    }

                }
                else
                {
                    canWork = false;
                }
            }
        }

        bool applyLocal(std::list<QString>& _rawData)
        {
            //_rawData.erase(_rawData.begin(), std::next(possibleLocations[0].second, 1));
            if (possibleLocations[0].conflict)
            {
                //conflicted. represent both versions
                DT::diffRowData buforOld;
                DT::diffRowData buforNew;
                std::list<QString>::iterator movingIterator = possibleLocations[0].begin;
                while (!data.empty())
                {
                    if (data.front().second == DT::Unchanged && data.front().first == *movingIterator)
                    {
                        dumpBuffors(buforOld, buforNew, m_localOldRowData, m_localNewRowData);
                        m_localNewRowData.push_back(DT::diffRowData(std::make_pair(DT::lineStatus::Unchanged, *movingIterator)));
                        m_localOldRowData.push_back(DT::diffRowData(std::make_pair(DT::lineStatus::Unchanged, *movingIterator)));
                        movingIterator = std::next(movingIterator, 1);
                        data.pop_front();
                    }
                    else
                    {
                        if (data.front().second == DT::Unchanged || data.front().second == DT::lineStatus::Removed)
                        {
                            QString toFind = data.front().first;
                            auto searchIt = std::find_if(movingIterator, std::next(possibleLocations[0].end,1), [toFind](QString &element)->bool {return element == toFind; });

                            if (searchIt != std::next(possibleLocations[0].end, 1))
                            {
                                //old is conflicted
                                if (movingIterator != searchIt)
                                {
                                    dumpBuffors(buforOld, buforNew, m_localOldRowData, m_localNewRowData);
                                    for (auto it = movingIterator; it != searchIt; it++)
                                    {
                                        buforOld.data.push_back((std::make_pair(DT::lineStatus::Conflicted, *it)));
                                        buforNew.data.push_back((std::make_pair(DT::lineStatus::Conflicted, "")));
                                    }
                                    dumpBuffors(buforOld, buforNew, m_localOldRowData, m_localNewRowData);
                                }
                                if (data.front().second == DT::lineStatus::Unchanged)
                                {
                                    dumpBuffors(buforOld, buforNew, m_localOldRowData, m_localNewRowData);
                                    m_localOldRowData.push_back(DT::diffRowData(std::make_pair(DT::lineStatus::Unchanged, *searchIt)));
                                    m_localNewRowData.push_back(DT::diffRowData(std::make_pair(DT::lineStatus::Unchanged, *searchIt)));
                                }
                                else
                                {
                                    buforOld.data.push_back((std::make_pair(DT::lineStatus::Removed, *searchIt)));
                                }
                                movingIterator = std::next(searchIt, 1);
                                data.pop_front();
                            }
                            else
                            {
                                auto serachIt = std::find_if(data.begin(), data.end(), [movingIterator](std::pair<QString, DT::lineStatus> &element)->bool {return element.first == *movingIterator; });
                                if (serachIt != data.end())
                                {
                                    //new is conflicted;
                                    auto it = data.begin();
                                    if (it != serachIt)
                                    {
                                        dumpBuffors(buforOld, buforNew, m_localOldRowData, m_localNewRowData);
                                        while (it != serachIt)
                                        {
                                            buforOld.data.push_back((std::make_pair(DT::lineStatus::Conflicted, "")));
                                            buforNew.data.push_back((std::make_pair(DT::lineStatus::Conflicted, it->first)));
                                            data.pop_front();
                                        }
                                        dumpBuffors(buforOld, buforNew, m_localOldRowData, m_localNewRowData);
                                    }
                                    if (data.front().second == DT::lineStatus::Unchanged)
                                    {
                                        dumpBuffors(buforOld, buforNew, m_localOldRowData, m_localNewRowData);
                                        m_localOldRowData.push_back(DT::diffRowData(std::make_pair(DT::lineStatus::Unchanged, serachIt->first)));
                                        m_localNewRowData.push_back(DT::diffRowData(std::make_pair(DT::lineStatus::Unchanged, serachIt->first)));
                                    }
                                    else
                                    {
                                        buforOld.data.push_back((std::make_pair(DT::lineStatus::Removed, serachIt->first)));
                                    }
                                    movingIterator = std::next(movingIterator, 1);
                                }
                                else
                                {
                                    //both are conflicted
                                    buforOld.data.push_back((std::make_pair(DT::lineStatus::Conflicted, *movingIterator)));
                                    buforNew.data.push_back((std::make_pair(DT::lineStatus::Conflicted, data.front().first)));
                                    movingIterator = std::next(movingIterator, 1);
                                    data.pop_front();
                                }
                            }

                        }
                        else
                        {
                            if (data.front().second == DT::lineStatus::Added)
                            {
                                buforNew.data.push_back((std::make_pair(DT::lineStatus::Added, data.front().first)));
                            }
                            data.pop_front();
                        }

                    }
                }
                dumpBuffors(buforOld, buforNew, m_localOldRowData, m_localNewRowData);
                _rawData.erase(possibleLocations[0].begin, std::next(possibleLocations[0].end, 1));
                return true;
            }
            else
            {
#pragma region Merge
                //Mergable
                updateLocations(_rawData);
                if (possibleLocations.size() == 1)
                {
                    for (std::list<QString>::iterator unchanged = _rawData.begin(); unchanged != possibleLocations[0].begin; unchanged++)
                    {
                        m_localOldRowData.push_back(DT::diffRowData(std::make_pair(DT::lineStatus::Unchanged, *unchanged)));
                        m_localNewRowData.push_back(DT::diffRowData(std::make_pair(DT::lineStatus::Unchanged, *unchanged)));
                    }
                    _rawData.erase(_rawData.begin(), std::next(possibleLocations[0].end, 1));

                    DT::diffRowData buforOld;
                    DT::diffRowData buforNew;
                    for (auto row : data)
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
                            dumpBuffors(buforOld, buforNew, m_localOldRowData, m_localNewRowData);
                            m_localNewRowData.push_back(DT::diffRowData(std::make_pair(DT::lineStatus::Unchanged, row.first)));
                            m_localOldRowData.push_back(DT::diffRowData(std::make_pair(DT::lineStatus::Unchanged, row.first)));
                            break;
                        default:
                            break;
                        }
                    }
                    dumpBuffors(buforOld, buforNew, m_localOldRowData, m_localNewRowData);
                    return true;
                }
                else
                {
                    return false;
                }
#pragma endregion
            }
        }

        bool apply(std::list<DT::diffRowData>& _oldContainer, std::list<DT::diffRowData>& _newContainer/*, std::list<QString>& _rawData*/)
        {
            std::move(m_localOldRowData.begin(),m_localOldRowData.end(),std::back_inserter(_oldContainer));
            std::move(m_localNewRowData.begin(),m_localNewRowData.end(),std::back_inserter(_newContainer));
            return true;
        }
    };

}

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
    std::vector<SinglePatch> patches;
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
                        patch.updateLocations(rawData);
                        patches.push_back(patch);
                        //patch.apply(m_oldFileData, m_newFileData, rawData);
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
    //Reslove conflicts
    for(SinglePatch patch: patches)
    {
        if (patch.getNumberOfPossibleLocations()==1)
        {
            auto loc = patch.getPossibleLocations();
            for (auto it = rawData.begin(); it != loc[0].begin; it++)
            {
                m_newFileData.push_back(DT::diffRowData(std::make_pair(DT::lineStatus::Unchanged, *it)));
                m_oldFileData.push_back(DT::diffRowData(std::make_pair(DT::lineStatus::Unchanged, *it)));
            }
            rawData.erase(rawData.begin(), loc[0].begin);
            patch.applyLocal(rawData);
            patch.apply(m_oldFileData, m_newFileData);
        }
        else
        {

        }
    }

    //Save leftovers
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

void DiffModel::setVersion(QModelIndex _index, version _how)
{
    switch (_how)
    {
    case DiffModel::left:
        std::next(m_oldFileData.begin(), _index.row())->setAll(DT::lineStatus::Unchanged);
        *std::next(m_newFileData.begin(), _index.row()) = *std::next(m_oldFileData.begin(), _index.row());
        break;
    case DiffModel::right:
        std::next(m_newFileData.begin(), _index.row())->setAll(DT::lineStatus::Unchanged);
        *std::next(m_oldFileData.begin(), _index.row()) = *std::next(m_newFileData.begin(), _index.row());
        break;
    case DiffModel::leftOnRight:
        std::next(m_oldFileData.begin(), _index.row())->setAll(DT::lineStatus::Unchanged);
        std::next(m_newFileData.begin(), _index.row())->setAll(DT::lineStatus::Unchanged);

        break;
    case DiffModel::RightOnLeft:
        std::next(m_oldFileData.begin(), _index.row())->setAll(DT::lineStatus::Unchanged);
        std::next(m_newFileData.begin(), _index.row())->setAll(DT::lineStatus::Unchanged);

        break;
    default:
        break;
    }
    beginResetModel();
    endResetModel();
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
