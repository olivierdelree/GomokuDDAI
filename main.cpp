#include "MainWindow.h"
#include <QApplication>
#include <QtGui>

// Source: https://stackoverflow.com/a/20733453
void console()
{
    AllocConsole();
    FILE* pFileCon = nullptr;
    pFileCon = freopen("CONOUT$", "w", stdout);

    COORD coordInfo;
    coordInfo.X = 100;
    coordInfo.Y = 200;

    SetConsoleScreenBufferSize(GetStdHandle(STD_OUTPUT_HANDLE), coordInfo);
    SetConsoleMode(GetStdHandle(STD_OUTPUT_HANDLE), ENABLE_QUICK_EDIT_MODE | ENABLE_EXTENDED_FLAGS);
}

int main(int argc, char* argv[])
{
    console(); // Enable printing to the console

    QApplication application(argc, argv);

    MainWindow main_window;
    main_window.show();

    return QApplication::exec();
}
