#include "headerfiles/diff_generator.h"

#include <fstream>

namespace DiffGenerator
{

    ContextContainer::ContextContainer() :begin(3)
    {
        missed = 0;
        beginning = 1;
    }

    int ContextContainer::getBeginning() const
    {
        return beginning;
    }

    void ContextContainer::setBeginning(const int _beggining)
    {
        beginning = _beggining;
    }

    int ContextContainer::getBefore() const
    {
        int retValue = static_cast<int>(begin.getSize());
        for (rawContainer::const_iterator it = dataElements.begin(); it != dataElements.end(); it++)
        {
            if (it->second == DT::lineStatus::Unchanged || it->second == DT::lineStatus::Removed)
            {
                retValue++;
            }
        }
        return retValue;
    }
    int ContextContainer::getAfter() const
    {
        int retValue = static_cast<int>(begin.getSize());
        for (rawContainer::const_iterator it = dataElements.begin(); it != dataElements.end(); it++)
        {
            if (it->second == DT::lineStatus::Unchanged || it->second == DT::lineStatus::Added)
            {
                retValue++;
            }
        }
        return retValue;
    }

    rawContainer ContextContainer::getData()
    {
        std::list<std::string> tmp;
        while (begin.getSize() != 0)
        {
            tmp.push_back(begin.pop());
        }

        for (std::list<std::string>::reverse_iterator it = tmp.rbegin(); it != tmp.rend(); it++)
        {
            dataElements.push_front(std::make_pair(*it, DT::lineStatus::Unchanged));
        }
        //dataElements.insert(dataElements.begin(),tmp.begin(),tmp.end());
        return dataElements;
    }

    //returns false when new container is needed
    bool ContextContainer::pushBack(std::string _row, DT::lineStatus _status)
    {
        if (dataElements.size() == 0 && _status == DT::lineStatus::Unchanged)
        {
            if (begin.getSize() == 3)
            {
                beginning++;
            }
            begin.push(_row);
            return false;
        }

        if (missed == 3 && _status == DT::lineStatus::Unchanged)
        {
            return true;
        }
        if (_status == DT::lineStatus::Unchanged)
        {
            missed++;
        }
        else
        {
            missed = 0;
        }

        if (_status == DT::lineStatus::Removed)
        {
            rawContainer::reverse_iterator it;
            for (it = dataElements.rbegin(); it != dataElements.rend(); it++)
            {
                if (it->second != DT::lineStatus::Added)
                {
                    break;
                }
            }
            dataElements.insert(it.base(), std::make_pair(_row, _status));
        }
        else
        {
            dataElements.push_back(std::make_pair(_row, _status));
        }
        return false;
    }
    void ContextContainer::pushFront(std::list<std::string>::iterator _begin, std::list<std::string>::iterator _end, DT::lineStatus _status)
    {
        missed = 0;
        for (std::list<std::string>::iterator it = _end; it != _begin;)
        {
            --it;
            dataElements.push_front(std::make_pair(*it, _status));
        }
    }
    void ContextContainer::pushBack(std::list<std::string>::iterator _begin, std::list<std::string>::iterator _end, DT::lineStatus _status)
    {
        missed = 0;
        for (std::list<std::string>::iterator it = _begin; it != _end; it++)
        {
            dataElements.push_back(std::make_pair(*it, _status));
        }
    }


    //////////////////////////////////////////////////////////MAGIC INVOKER/////////////////////////////////////////////////////////
    MagicInvoker::MagicInvoker(std::string _oldFilePath, std::string _newFilePath)
        : oldFilePath(_oldFilePath)
        , newFilePath(_newFilePath)
    {
        std::string bufor;
        std::ifstream oldFile(_oldFilePath, std::ios::in);
        std::ifstream newFile(_newFilePath, std::ios::in);
        ContextList.push_back(ContextContainer());

        if (oldFile.good() && newFile.good())
        {
            while (!oldFile.eof())
            {
                std::getline(oldFile, bufor);
                rawDataOld.push_back(bufor);
            }
            oldFile.close();
            while (!newFile.eof())
            {
                std::getline(newFile, bufor);
                rawDataNew.push_back(bufor);
            }
            newFile.close();
            doDiff();
        }
    }

    void MagicInvoker::doDiff()
    {
        int currentrow = 1;
        std::list<std::string>::iterator it;
        std::string currentStr;
        for (size_t i = 0; i < rawDataOld.size(); i++)
        {
            currentStr = *rawDataOld.begin();
            it = std::find(rawDataNew.begin(), rawDataNew.end(), currentStr);
            if (it != rawDataNew.end())
            {
                ContextList[0].pushFront(rawDataNew.begin(), it, DT::lineStatus::Added);
                rawDataNew.erase(rawDataNew.begin(), it);
                break;
            }
            else
            {
                rawDataOld.pop_front();
                ContextList[ContextList.size() - 1].pushBack(currentStr, DT::lineStatus::Removed);
            }
            currentrow++;
        }
        while (!rawDataOld.empty() && !rawDataNew.empty())
        {
            if (*rawDataOld.begin() == *rawDataNew.begin())
            {
                currentrow++;
                if (ContextList[ContextList.size() - 1].pushBack(*rawDataOld.begin(), DT::lineStatus::Unchanged))\
                {
                    ContextList.push_back(ContextContainer());
                    ContextList[ContextList.size() - 1].setBeginning(currentrow);
                }
                rawDataOld.pop_front();
                rawDataNew.pop_front();
            }
            else
            {
                //old[0] == itNew
                std::list<std::string>::iterator itNew = std::find(rawDataNew.begin(), rawDataNew.end(), *rawDataOld.begin());
                //new[0] == itOld
                std::list<std::string>::iterator itOld = std::find(rawDataOld.begin(), rawDataOld.end(), *rawDataNew.begin());
                if (itNew == rawDataNew.end() && itOld == rawDataOld.end()) // Nie znaleziono nic
                {
                    ContextList[ContextList.size() - 1].pushBack(rawDataOld.front(), DT::lineStatus::Removed);
                    ContextList[ContextList.size() - 1].pushBack(rawDataNew.front(), DT::lineStatus::Added);
                    rawDataOld.pop_front();
                    rawDataNew.pop_front();
                }
                else
                {
                    if (itNew != rawDataNew.end() && itOld != rawDataOld.end())
                    {
                        if (std::distance(rawDataOld.begin(), itOld) < std::distance(rawDataNew.begin(), itNew))
                        {
                            itNew = std::find(rawDataNew.begin(), rawDataNew.end(), *itOld);
                        }
                        else
                        {
                            itOld = std::find(rawDataOld.begin(), rawDataOld.end(), *itNew);
                        }
                    }
                    else {
                        if (itNew != rawDataNew.end()) //znaleziono inNew === old[0] == itNew -> ++ itNew til itOld
                        {
                            itOld = std::find(rawDataOld.begin(), rawDataOld.end(), *itNew);
                        }
                        else //itOld != rawDataOld.end() === new[0] == itOld -> -- itOld til itNew
                        {
                            itNew = std::find(rawDataNew.begin(), rawDataNew.end(), *itOld);
                        }
                    }
                    currentrow += std::distance(rawDataOld.begin(), itOld);
                    ContextList[ContextList.size() - 1].pushBack(rawDataOld.begin(), itOld, DT::lineStatus::Removed);
                    rawDataOld.erase(rawDataOld.begin(), itOld);
                    ContextList[ContextList.size() - 1].pushBack(rawDataNew.begin(), itNew, DT::lineStatus::Added);
                    rawDataNew.erase(rawDataNew.begin(), itNew);
                }

            }
        }
        if (!rawDataOld.empty())//Coœ zosta³o w old
        {
            ContextList[ContextList.size() - 1].pushBack(rawDataOld.begin(), rawDataOld.end(), DT::lineStatus::Removed);
            rawDataOld.erase(rawDataOld.begin(), rawDataOld.end());
        }
        else if (!rawDataNew.empty())//Coœ zosta³o w new
        {
            ContextList[ContextList.size() - 1].pushBack(rawDataNew.begin(), rawDataNew.end(), DT::lineStatus::Added);
            rawDataNew.erase(rawDataNew.begin(), rawDataNew.end());
        }
    }
    
    void MagicInvoker::save(QTextStream& stream)
    {
        int diffrence = 0;
        int before;
        int after;
        for (ContextContainer cont : ContextList)
        {
            //@@ -row,after +(row+diffrencebefore),after @@
            before = cont.getBefore();
            after = cont.getAfter();
            stream << "@@ -" << cont.getBeginning() << ',' << before << " +" << (cont.getBeginning() + diffrence) << ',' << after << " @@" << endl;
            for (std::pair<std::string, DT::lineStatus> row : cont.getData())
            {
                switch (row.second)
                {
                case DT::Unchanged:
                    stream << ' ';
                    break;
                case DT::Removed:
                    stream << '-';
                    break;
                case DT::Added:
                    stream << '+';
                    break;
                default:
                    break;
                }
                stream << row.first.c_str() << endl;
            }
            diffrence += after - before;
        }
    }

}//DIFF GENERATOR