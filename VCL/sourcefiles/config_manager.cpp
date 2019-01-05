#include "../headerfiles/config_manager.h"
#include "QtWidgets/QApplication"

std::map<ConfigKeys::Colors, QString> ConfigKeys::colorsKeys = {
    { DiffWindow_addedTextForeground ,"DiffWindow/Added Text/Foreground" },//
    { DiffWindow_addedTextBackGround ,"DiffWindow/Added Text/Background" },//
    { DiffWindow_unchangedTextForeground ,"DiffWindow/Unchanged Text/Foreground" },//
    { DiffWindow_unchangedTextBackGround ,"DiffWindow/Unchanged Text/Background" },//
    { DiffWindow_changedTextForeground ,"DiffWindow/Changed Text/Foreground" },//
    { DiffWindow_changedTextBackGround ,"DiffWindow/Changed Text/Background" },//
    { DiffWindow_removedTextForeground ,"DiffWindow/Removed Text/Foreground" },//
    { DiffWindow_removedTextBackGround ,"DiffWindow/Removed Text/Background" },//
    { DiffWindow_conflictedTextForeground ,"DiffWindow/Conflicted Text/Foreground" },//
    { DiffWindow_conflictedTextBackGround ,"DiffWindow/Conflicted Text/Background" },//
    { DiffWindow_lineNumberOddForeground ,"DiffWindow/Line Number/Odd/Foreground" },//
    { DiffWindow_lineNumberOddBackground ,"DiffWindow/Line Number/Odd/Background" },//
    { DiffWindow_lineNumberEvenForeground ,"DiffWindow/Line Number/Even/Foreground" },//
    { DiffWindow_lineNumberEvenBackground ,"DiffWindow/Line Number/Even/Background" },//
    { DiffWindow_mouseHover ,"DiffWindow/MouseHover" },
};

std::map<ConfigKeys::Colors, QColor> ConfigKeys::colorsDefaults = {
    { DiffWindow_addedTextForeground ,QColor(0,180,0) },
    { DiffWindow_addedTextBackGround ,QColor(255,255,155) },
    { DiffWindow_unchangedTextForeground ,QColor(0,0,0) },
    { DiffWindow_unchangedTextBackGround ,QColor(255,255,255) },
    { DiffWindow_changedTextForeground ,QColor(0,155,255) },
    { DiffWindow_changedTextBackGround ,QColor(255,255,255) },
    { DiffWindow_removedTextForeground ,QColor(255,0,0) },
    { DiffWindow_removedTextBackGround ,QColor(255,255,155) },
    { DiffWindow_conflictedTextForeground ,QColor(255,200,0) },
    { DiffWindow_conflictedTextBackGround ,QColor(227,78,28) },
    { DiffWindow_lineNumberOddForeground ,QColor(160,160,160) },
    { DiffWindow_lineNumberOddBackground ,QColor(60,60,60) },
    { DiffWindow_lineNumberEvenForeground ,QColor(60,60,60) },
    { DiffWindow_lineNumberEvenBackground ,QColor(160,160,160) },
    { DiffWindow_mouseHover ,QColor(200,200,200) }
};

const QString ConfigKeys::FontKey = "Application/Font";
const QString ConfigKeys::GeneratorKey = "Application/Diff Generator";
const QString ConfigKeys::TimerKey = "Application/Execution Time";

ConfigManager::ConfigManager()
{
}


ConfigManager::~ConfigManager()
{
}

void ConfigManager::generate() 
{
    for (int i = 0; i < ConfigKeys::Colors::COUNT; i++)
    {
        QString key = ConfigKeys::getColorKey(static_cast<ConfigKeys::Colors>(i));
        if (!settings->contains(key))
            setQColor(static_cast<ConfigKeys::Colors>(i), ConfigKeys::getColorDefault(static_cast<ConfigKeys::Colors>(i)));
    }
}

ConfigManager& ConfigManager::getInstance()
{
    static ConfigManager Instance;
    return Instance;
}

void ConfigManager::initialize(QString directory)
{
    configDirectory = directory + "/config.ini";
    settings = new QSettings(configDirectory, QSettings::IniFormat);
    generate();
}

QColor ConfigManager::getQColor(const ConfigKeys::Colors key)
{
    return settings->value(ConfigKeys::getColorKey(key), ConfigKeys::getColorDefault(key)).value<QColor>();
}

QColor ConfigManager::getQColor(const QString key)
{
    return settings->value(key, ConfigKeys::getColorDefault(ConfigKeys::keyToColorEnum(key))).value<QColor>();
}

void ConfigManager::setQColor(const QString key, const QColor color)
{
    settings->setValue(key, color);
}

void ConfigManager::setQColor(const ConfigKeys::Colors key, const QColor color)
{
    settings->setValue(ConfigKeys::getColorKey(key), color);
}

QFont ConfigManager::getQFont(const QString key)
{
    return settings->value(key, QApplication::font()).value<QFont>();
}

void ConfigManager::setQFont(const QString key, const QFont font)
{
    settings->setValue(key, font);
}

QString ConfigManager::getQString(const QString key)
{
    return settings->value(key, "").toString();
}

void ConfigManager::setQString(const QString key, const QString str)
{
    settings->setValue(key, str);
}

bool ConfigManager::getBool(const QString key)
{
    return settings->value(key, false).toBool();
}

void ConfigManager::setBool(const QString key, const bool value)
{
    settings->setValue(key, value);
}
