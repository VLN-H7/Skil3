#include <QCoreApplication>
#include "consoleui.h"
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    ConsoleUI ui = ConsoleUI();
    ui.start();
    return a.exec();
}
