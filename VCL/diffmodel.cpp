#include "diffmodel.h"
#include <fstream>
#include <regex>
#include <algorithm>
#include <QApplication>

namespace
{
	QString replaceTabs(QString input)
	{
		if (input.size() != 0)
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
		}
		return input;
	}
}

DiffModel::DiffModel(QObject *parent)
	: QAbstractListModel(parent)
	, m_FontMetrics(QFont("Arial"))
	, m_newFileViewSize(0,0)
	, m_oldFileViewSize(0,0)
{
	
}

DiffModel::~DiffModel()
{
}

int DiffModel::rowCount(const QModelIndex&) const
{
	return static_cast<int>(m_oldFileData.size() < m_newFileData.size() ? m_oldFileData.size() : m_newFileData.size());
}

int DiffModel::columnCount(const QModelIndex&) const
{
	return 2;
}

bool DiffModel::loadFiles(std::string Old, std::string New)
{
	/*changeData.clear();
	std::ifstream reader;
	std::string bufor;
	reader.open(Old);
	if (reader.good())
	{
		while (!reader.eof())
		{
			std::getline(reader, bufor);
			QString qstring(bufor.c_str());
			replaceTabs(qstring);
			fileOldData.push_back(qstring);
		}
	}
	reader.close();
	reader.open(New);
	if (reader.good())
	{
		while (!reader.eof())
		{
			std::getline(reader, bufor);
			fileNewData.push_back(QString(bufor.c_str()));
		}
	}
	reader.close();*/
	return true;
}

bool DiffModel::loadFileAndDiff(std::string File, std::string DiffFile)
{
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
		while (!reader.eof())
		{
			if (!afterSection)
				std::getline(reader, bufor);
			if (bufor[0] == '@' && bufor[1] == '@') {
				std::regex pattern("\\d+");
				std::sregex_iterator next(bufor.begin(), bufor.end(), pattern);
				oldStartPrev = oldStart;
				oldNumberPrev = oldNumber;
				oldStart = atoi((*next).str().c_str());
				oldNumber = atoi((*++next).str().c_str());
				newStart = atoi((*++next).str().c_str());
				newNumber = atoi((*++next).str().c_str());
				for (int i = oldStartPrev+ oldNumberPrev; i < oldStart-1; i++)
				{
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
						if(oldRow.size()!=0 || newRow.size() != 0)
						{
							if (oldRow.size() != 0 && newRow.size() != 0) 
							{
								m_oldFileData.push_back(oldRow);
								m_newFileData.push_back(newRow);
							}
							else if(oldRow.size() != 0)
							{ 
								m_newFileData.push_back(DT::diffRowData(std::make_pair(DT::lineStatus::Changed, "")));
								m_oldFileData.push_back(oldRow);
							}
							else if (newRow.size() != 0)
							{
								m_newFileData.push_back(newRow);
								m_oldFileData.push_back(DT::diffRowData(std::make_pair(DT::lineStatus::Changed, "")));
							}
							oldRow.clear();
							newRow.clear();
						}
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
					default:
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
	}
	reader.close();
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
		QSize newSize = std::next(m_newFileData.begin(), index.row())->wholeTextSize(m_FontMetrics, m_newFileViewSize);
		QSize oldSize = std::next(m_oldFileData.begin(), index.row())->wholeTextSize(m_FontMetrics, m_oldFileViewSize);

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
