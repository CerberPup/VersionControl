#include "headerfiles/main_window.h"

#include <iostream>
#include <locale> 
#include <QApplication>
#include <QMessageBox>
#include <QDebug>
#ifdef _WIN32
#include <windows.h>
#endif

std::string createHelpString()
{
    return "Help:\n\
-NoGui - Runs app without gui\n\
-Input <dir> - Passes base file\n\
-Second <dir> - Passes second file\n\
-Output <dir> - Passes output file\n\
-Generate <Program|System|User> - Generates new diff file form -input and -second\n\
-Apply - Apply Second on Input *Don't use with -NoGui\n\
-Dump <dir> - saves applyed patch to argument\n\
-D - Display arguments\n\
";
}

int main(int argc, char *argv[])
{
    bool nogui = false;
    bool displayHelp = false;
    for (int i = 1; i < argc; i++)
    {
        std::string tmp = argv[i];
        for (auto & c : tmp) c = toupper(c);
        if (tmp == "-NOGUI")
        {
            nogui = true;
        }
        if (tmp == "-HELP" || tmp == "-H")
        {
            displayHelp = true;
        }if (tmp == "-D")
        {
#ifdef _WIN32
            std::string message;
            for (int j = 0; j < argc; j++)
            {
                message += argv[j];
            }
            MessageBoxW(NULL, std::wstring(message.begin(), message.end()).c_str(), L"Help", NULL);
#endif
        }
    }
    if (displayHelp)
    {
#ifdef _WIN32
        std::string message(createHelpString());
        MessageBoxW(NULL, std::wstring(message.begin(), message.end()).c_str(), L"Help", NULL);
#else
        qWarning() << createHelpString();
#endif
        return EXIT_SUCCESS;
    }

    QApplication application(argc, argv);
    MainWindow mainWindow(0);
    if (!nogui)
    {
        mainWindow.show();
    }
    try
    {
        mainWindow.parseArguments(argc, argv);
    }
    catch (const std::invalid_argument& t)
    {
#ifdef _WIN32
        std::string message(createHelpString() + "\nError: " + std::string( t.what()));
        MessageBoxW(NULL, std::wstring(message.begin(), message.end()).c_str() , L"Error", NULL);
#else
        qWarning() << createHelpString() << "\nError: " << t.what();
#endif
        return EXIT_FAILURE;
    }

    

    if (!nogui)
    {
        return application.exec();
    }

    return EXIT_SUCCESS;
}