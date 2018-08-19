#ifndef VERSION_CONTROLL_SYSTEM_H
#define VERSION_CONTROLL_SYSTEM_H

#include "sqlite\sqlite3.h"

#include <unordered_set>

#include <QDir>
#include <QString>


namespace VersionControllSystem
{
    class VersionControllRoot
    {

    public:
        VersionControllRoot(QString);
        ~VersionControllRoot();

        bool isInitialized();

    private:
        sqlite3* connection;
        bool initialized;
    };

    typedef std::map<QString, std::shared_ptr<VersionControllRoot>> Roots_t;

    class VersionControllManager
    {

    public:
        VersionControllManager(VersionControllManager const&) = delete;
        void operator=(VersionControllManager const&) = delete;
        static VersionControllManager& getInstance();
        std::shared_ptr<VersionControllRoot> findRoot(QString dir);
        bool initVersionControl(QString path);
    private:
        VersionControllManager();
        ~VersionControllManager();
        QString getVersionControlRoot(QString path);
        
        Roots_t rootObjects;
        std::unordered_set<std::string> cache;
    };

    /*
	static bool createDataFile(QString path) 
	{
		QFile file(path);
		bool value = file.open(QIODevice::OpenModeFlag::NewOnly);
		file.close();
		return value;
	}

	static bool initVersionControl(QString path)
	{
		
	}

	static QString getVersionControlRoot(QString path)
	{
		QDir directory(path);
		do {
			if (QFileInfo::exists(directory.path() + "/.VCS/FileData"))
				return directory.path() + "/.VCS/";
		} while (directory.cdUp());
		return "";
	}*/
} // ControlManager

#endif // !VERSION_CONTROLL_SYSTEM_H
