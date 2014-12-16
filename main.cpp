#include "ui/computerscientists.h"
#include <QApplication>
#include <QSplashScreen>
#include <QTimer>
#include <QtPlugin>
#include <QDebug>
#include <QImageWriter>


//Q_IMPORT_PLUGIN(qjpeg) //error: undefined reference to `qt_static_plugin_qjpeg()'

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QString sDir = QCoreApplication::applicationDirPath();
    app.addLibraryPath(sDir+"/plugins");
    qDebug() << QImageWriter::supportedImageFormats();
    QSplashScreen *splash = new QSplashScreen;
    splash->setPixmap(QPixmap(":/pictures/pictures/welcomescreen.jpg"));
    splash->show();
    ComputerScientists window;
    QTimer::singleShot(1000,splash,SLOT(close()));
    QTimer::singleShot(1000,&window,SLOT(show()));

    return app.exec();

}
