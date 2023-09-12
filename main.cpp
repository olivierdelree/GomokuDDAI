#include "MainWindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication application(argc, argv);

    MainWindow main_window;
    main_window.show();

    return QApplication::exec();
}
