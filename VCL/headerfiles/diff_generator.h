#ifndef DIFFGENERATOR_H
#define DIFFGENERATOR_H

#include "headerfiles/data_objects.h"

#include <string>
#include <list>
#include <queue>

#include <QTextStream>


namespace DiffGenerator
{
    //simple fifo container.
    template <class T> class FifoContainer
    {
        std::queue<T> m_data;
        size_t m_size;
    public:
        FifoContainer(size_t _size) :m_size(_size) {}

        void push(T _element)
        {
            if (m_data.size() == m_size)
                m_data.pop();
            m_data.push(_element);
        }

        T pop()
        {
            T tmp = m_data.front();
            m_data.pop();
            return tmp;
        }
        std::queue<T> getData() { return m_data; }
        size_t getSize() const { return m_data.size(); }
    };

    typedef std::pair<QString, DT::lineStatus> data_t;
    typedef std::list<data_t> rawContainer;

    //conteiner containing single context block (hunk)
    class ContextContainer
    {
        FifoContainer<QString> begin; //container for beggining of context
        rawContainer dataElements;
        short missed; //counts unchanged lines after change
        int beginning; //oldest remembered line number
        bool forgottenData; //loaded over 3 items to begin variable
    public:
        ContextContainer();

        bool hasForgottenData() const; //forgottenData getter

        bool hasData() const;
        //context wherabouts for diff hunk header
        int getBeginning() const;
        void setBeginning(const int _beggining);
        int getBefore() const;
        int getAfter() const;
        //get dataElements
        rawContainer getData();
        //add data
        bool pushBack(QString _row, DT::lineStatus _status);
        bool pushBack(rawContainer& _newData);
        void pushFront(std::list<QString>::iterator _begin, std::list<QString>::iterator _end, DT::lineStatus _status);
        void pushBack(std::list<QString>::iterator _begin, std::list<QString>::iterator _end, DT::lineStatus _status);
    };

    //responsible for making diff
    class MagicInvoker
    {
        bool hasNewLineAtEndInOldFile;
        bool hasNewLineAtEndInNewFile;

        std::string oldFilePath;
        std::string newFilePath;
        std::list<QString> rawDataOld;
        std::list<QString> rawDataNew;
        std::vector<ContextContainer> ContextList;

        void doDiff();

    public:
        MagicInvoker(std::string _oldFilePath, std::string _newFilePath);//here magic happens
        void save(QTextStream& stream);
    };
}

#endif// DIFFGENERATOR_H