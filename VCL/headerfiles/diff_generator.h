#ifndef DIFFGENERATOR_H
#define DIFFGENERATOR_H

#include "headerfiles/data_objects.h"

#include <string>
#include <list>
#include <queue>

#include <QTextStream>


namespace DiffGenerator
{
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

    typedef std::pair<std::string, DT::lineStatus> data_t;
    typedef std::list<data_t> rawContainer;

    class ContextContainer
    {
        FifoContainer<std::string> begin;
        rawContainer dataElements;
        short missed;
        int beginning;
    public:
        ContextContainer();

        int getBeginning() const;
        void setBeginning(const int _beggining);
        int getBefore() const;
        int getAfter() const;
        rawContainer getData();
        bool pushBack(std::string _row, DT::lineStatus _status);
        void pushFront(std::list<std::string>::iterator _begin, std::list<std::string>::iterator _end, DT::lineStatus _status);
        void pushBack(std::list<std::string>::iterator _begin, std::list<std::string>::iterator _end, DT::lineStatus _status);
    };

    class MagicInvoker
    {
        std::string oldFilePath;
        std::string newFilePath;
        std::list<std::string> rawDataOld;
        std::list<std::string> rawDataNew;
        std::vector<ContextContainer> ContextList;

        void doDiff();

    public:
        MagicInvoker(std::string _oldFilePath, std::string _newFilePath);
        void save(QTextStream& stream);
    };
}

#endif// DIFFGENERATOR_H