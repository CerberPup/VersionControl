#include "diffmodel.h"
#include <fstream>
#include <regex>
#include <algorithm>
#include <QApplication>

namespace
{
	void replaceTabs(QString& input)
	{
		if (input.size() != 0)
		{
			int it = 0;

			while (input.at(it) == '\t')
			{
				it++;
			}
			std::u32string tmp = input.toStdU32String();
			std::u32string tab = U"   →";
			tmp.erase(tmp.begin(), tmp.begin() + it);//― → ·
			for (; it > 0; it--)
				tmp = tab + tmp;
			//tmp.insert(tmp.begin(), it * 4, U'·');
			input = QString::fromStdU32String(tmp);
		}
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
	return static_cast<int>(m_oldFileData.size());
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
			QString qstring(bufor.c_str());
			replaceTabs(qstring);
			m_oldFileData.push_back(DT::diffRowData(std::make_pair(DT::lineStatus::Unchanged, qstring)));
			m_newFileData.push_back(DT::diffRowData(std::make_pair(DT::lineStatus::Unchanged,qstring)));
		}
	}
	reader.close();
	/*reader.open(DiffFile);
	if (reader.good())
	{
		int oldStartPrev = 0;
		int oldStart = 0;
		int oldNumber = 0;
		int newStart = 0;
		int newNumber = 0;
		int linesAdded = 0;
		while (!reader.eof())
		{
			std::getline(reader, bufor);
			if (bufor[0] == '@' && bufor[1] == '@') {
				std::regex pattern("\\d+");
				std::sregex_iterator next(bufor.begin(), bufor.end(), pattern);
				oldStartPrev = oldStart;
				oldStart = atoi((*next).str().c_str());
				oldNumber = atoi((*++next).str().c_str());
				newStart = atoi((*++next).str().c_str());
				newNumber = atoi((*++next).str().c_str());
				//fileNewData.insert(fileNewData.end(), std::next(oldFileData.begin(), linesAdded + oldStartPrev), std::next(oldFileData.begin(), linesAdded + oldStart - oldStartPrev));
				std::getline(reader, bufor);
			}
		}
	}
	//*std::next(fileOldData.begin(), 10) = "test\nmulti\nline";
	reader.close();*/
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
			return QVariant::fromValue(*std::next(m_oldFileData.begin(), index.row()));
		}
		else if (index.column() == 1)
		{
			return QVariant::fromValue(*std::next(m_oldFileData.begin(), index.row()));
		}
		break;
	case Qt::SizeHintRole:
	{
		if (index.column() == 0)
		{
			return std::next(m_oldFileData.begin(), index.row())->lineSize(m_FontMetrics, m_oldFileViewSize);
		}
		else if (index.column() == 1)
		{
			return std::next(m_oldFileData.begin(), index.row())->lineSize(m_FontMetrics, m_newFileViewSize);
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
