#include "headerfiles/version_control_system.h"

#ifdef _WIN32
#include <windows.h>
#include <fileapi.h>
#endif

namespace
{
    bool compareRoot(const std::string& root, const std::string& child) {
        if (root.size() >= child.size())
            return false;

        std::string::const_reverse_iterator childIterator = child.crbegin() + child.size()-root.size();
        for (std::string::const_reverse_iterator rootIterator = root.crbegin(); rootIterator < root.crend(); rootIterator++)
        {
            if (*rootIterator!= *childIterator)
                return false;
            childIterator++;
        }
        return true;
    }
}

namespace VersionControllSystem 
{
    VersionControllRoot::VersionControllRoot(QString _path):initialized(false)
    {
        if (QFileInfo::exists(_path + "/.VCS/data.db"))
        {
            sqlite3_open(_path.toUtf8() + "/.VCS/data.db", &connection);
        }
        else 
        {
            //createDB()
        }

       /* const char *sql = "CREATE TABLE Files("  \
            "ID INT PRIMARY KEY     NOT NULL," \
            "Name           TEXT    NOT NULL," \
            "Directory            TEXT     NOT NULL );";
        char *zErrMsg = 0;
        
        //sqlite3_initialize();
        sqlite3_open(name, &con);
        sqlite3_exec(con, sql, callback, 0, &zErrMsg);
        sql = "insert into Files values ('0', 'a', 'b');";
        sqlite3_exec(con, sql, callback, 0, &zErrMsg);*/
        
            //sqlite3_shutdown();
    }

    VersionControllRoot::~VersionControllRoot()
    {
        sqlite3_close(connection);
    }

    bool VersionControllRoot::isInitialized()
    {
        return initialized;
    }

//-------------------------------------------------------------

    VersionControllManager::VersionControllManager()
    {
    }

    VersionControllManager::~VersionControllManager()
    {
    }

    VersionControllManager & VersionControllManager::getInstance()
    {
        static VersionControllManager Instance;
        return Instance;
    }

    QString VersionControllManager::getVersionControlRoot(QString _path)
    {
        QDir directory(_path);
        do {
            if (QFileInfo::exists(directory.path() + "/.VCS/data.db"))
                return directory.path();
        } while (directory.cdUp());
        return "";
    }
    
    std::shared_ptr<VersionControllRoot> VersionControllManager::findRoot(QString _dir)
    {
        Roots_t::iterator it = rootObjects.find(_dir);
        if (it != rootObjects.end())
        {
            return it->second;
        }
        else
        {
            std::string _dirSTR = _dir.toUtf8();
            std::unordered_set<std::string>::iterator cacheIterator = cache.find(_dirSTR);
            if (cacheIterator != cache.end())
            {
                return nullptr;
            }
            QString rootDir = getVersionControlRoot(_dir);
            if (rootDir == "")
            {
                cache.insert(_dirSTR);
                return nullptr;
            }
            Roots_t::iterator it = rootObjects.find(rootDir);
            if (it != rootObjects.end())
            {
                rootObjects[_dir] = rootObjects[rootDir];
                return it->second;
            }
            else
            {
                rootObjects[rootDir] = std::make_shared<VersionControllRoot>(rootDir);
                return rootObjects[rootDir];
            }
        }
    }
    bool VersionControllManager::initVersionControl(QString _path)
    {
        bool success = true;
        QDir directory(_path);
        success &= directory.mkdir(".VCS");
#ifdef _WIN32
        success &= SetFileAttributesA(_path.toUtf8() + "/.VCS", FILE_ATTRIBUTE_HIDDEN) != 0;
#endif
        std::shared_ptr<VersionControllRoot> newObject = std::make_shared<VersionControllRoot>(_path);
        rootObjects[_path] = std::make_shared<VersionControllRoot>(_path);
        //success &= createDataFile(_path + "/.VCS/FileData");
        std::string _pathSTR = _path.toUtf8();
        if (success) {
            for (std::unordered_set<std::string>::iterator i = cache.begin(); i != cache.end(); i++)
            {
                if (compareRoot(_pathSTR, *i))
                {

                }
            }
        }
        return success;
    }
}