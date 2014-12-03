#include <QCoreApplication>
#include "consoleui.h"
#include "sqlconnection.h"
int main(int argc, char *argv[])
{
    SQLConnection::getInstance();
    QCoreApplication a(argc, argv);
    ConsoleUI ui = ConsoleUI();
    ui.start();
    return a.exec();
}
