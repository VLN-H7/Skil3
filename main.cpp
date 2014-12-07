#include <QCoreApplication>
#include "ui/consoleui.h"

int main(int argc, char *argv[])
{
    //QCoreApplication a(argc, argv); // Is this neccessary?
    ConsoleUI ui = ConsoleUI();
    ui.start();
    //return a.exec();
    return 0;
}
