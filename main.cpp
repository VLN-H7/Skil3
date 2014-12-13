#include "ui/computerscientists.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ComputerScientists w;
    w.show();

    return a.exec();
}
