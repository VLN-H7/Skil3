#include "ui/computerscientists.h"
#include <QApplication>
#include <QSplashScreen>
#include <QTimer>



int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QSplashScreen *splash = new QSplashScreen;
    splash->setPixmap(QPixmap(":/pictures/pictures/welcomescreen.jpg"));
    splash->show();
    ComputerScientists window;
    QTimer::singleShot(1000,splash,SLOT(close()));
    QTimer::singleShot(1000,&window,SLOT(show()));
    return app.exec();
}
