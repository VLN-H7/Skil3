#include <QCoreApplication>
#include <consoleui.h>
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    ConsoleUI ui = ConsoleUI();
    do{
        ui.start();
    } while(1);
    return a.exec();
}
