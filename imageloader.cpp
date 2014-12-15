#include "imageloader.h"

ImageLoader* ImageLoader::_instance = NULL;
ImageLoader* ImageLoader::getInstance() {
    if (_instance == NULL)
    {
        _instance = new ImageLoader;
    }
    return _instance;
}

ImageLoader::ImageLoader(QObject *parent):
    QObject(parent)
{
    networkMgr = new QNetworkAccessManager(this);
    connect(networkMgr, SIGNAL(finished(QNetworkReply*)), this, SLOT(loadFinished(QNetworkReply*)));

}

ImageLoader::~ImageLoader(){
    delete networkMgr;
}

void ImageLoader::load(QUrl url, QLabel* label){
    dict.insert(url, label);
    QNetworkRequest request(url);
    networkMgr->get(request);
}

void ImageLoader::loadFinished(QNetworkReply *reply){
    if(!dict.contains(reply->url()))
        return;
    auto label = dict[reply->url()];
    dict.remove(reply->url());

    QVariant statusCodeV = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute);

    // Or the target URL if it was a redirect:
    QVariant redirectionTargetUrl = reply->attribute(QNetworkRequest::RedirectionTargetAttribute);

    // no error received?
    if (reply->error() == QNetworkReply::NoError)
    {
        // read data from QNetworkReply here
        QByteArray bytes = reply->readAll();  // bytes
        QPixmap pixmap;
        pixmap.loadFromData(bytes);
        label->setPixmap(pixmap);
    }
    // Some http error received
    else
    {
        // handle errors here
    }

    // We receive ownership of the reply object
    // and therefore need to handle deletion.
    delete reply;
}
