#ifndef CONTROL_MANAGER_H
#define CONTROL_MANAGER_H

#ifdef _WIN32
#include <windows.h>
#include <fileapi.h>
#endif

#include <QString>
#include "ControlManager.h"
#include <Qdir>

namespace ControlManager
{
	static bool createDataFile(QString path) 
	{
		QFile file(path);
		bool value = file.open(QIODevice::OpenModeFlag::NewOnly);
		file.close();
		return value;
	}

	static bool initVersionControl(QString path)
	{
		bool success = true;
		QDir directory(path);
		success &= directory.mkdir(".VCS");
#ifdef _WIN32
		success &= SetFileAttributesA(path.toUtf8() + "/.VCS", FILE_ATTRIBUTE_HIDDEN) != 0;
#endif
		
		success &= createDataFile(path + "/.VCS/FileData");
		return success;
	}

	static QString getVersionControlRoot(QString path)
	{
		QDir directory(path);
		do {
			if (QFileInfo::exists(directory.path() + "/.VCS/FileData"))
				return directory.path() + "/.VCS/";
		} while (directory.cdUp());
		return "";
	}
} // ControlManager

#endif // !CONTROL_MANAGER_H
