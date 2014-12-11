#include "welcomescreen.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    Welcomescreen window;
    window.show();

    return app.exec();
}
