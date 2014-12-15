#ifndef IMAGELOADER_H
#define IMAGELOADER_H

#include <QNetworkAccessManager>
#include <QHash>
#include <QLabel>
#include <QUrl>
#include <QNetworkRequest>
#include <QNetworkReply>


class ImageLoader: private QObject
{
    Q_OBJECT
private:
    static ImageLoader* _instance;

protected:
    ImageLoader(QObject *parent = 0);
    ~ImageLoader();

public:
    static ImageLoader* getInstance();
    void load(QUrl url, QLabel* label);

private slots:
    void loadFinished(QNetworkReply *reply);

private:
    QNetworkAccessManager* networkMgr;
    QHash<QUrl,QLabel*> dict;

    void loadLabel(QLabel *label, QPixmap pixmap);
};

#endif // IMAGELOADER_H
