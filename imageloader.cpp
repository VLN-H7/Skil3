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

void ImageLoader::cancel(QLabel* label){
    foreach(QUrl url, dict.keys()){
        if(dict[url] == label){
            dict.remove(url);
        };
    }
}

void ImageLoader::load(QUrl url, QLabel* label){
    if(!url.isValid())
        return;
    if(url.scheme() == "file"){
        loadLabel(label, QPixmap(url.toLocalFile() ));
        return;
    }
    dict.insert(url, label);
    QNetworkRequest request(url);
    networkMgr->get(request);
}

//some code from here: http://www.qtcentre.org/threads/1483-Qt4-How-to-load-Url-image-into-QImage
void ImageLoader::loadFinished(QNetworkReply *reply){
    if(!dict.contains(reply->url()))
        return;
    auto label = dict[reply->url()];
    dict.remove(reply->url());



    QVariant statusCodeV = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute);

    // Or the target URL if it was a redirect:
    QVariant redirectionTargetUrl = reply->attribute(QNetworkRequest::RedirectionTargetAttribute);

    if (reply->error() == QNetworkReply::NoError)
    {
        QByteArray bytes = reply->readAll();
        QPixmap pixmap;
        pixmap.loadFromData(bytes);
        loadLabel(label, pixmap);
    }
    else
    {
        qDebug() << reply->errorString();
    }

    delete reply;
}

void ImageLoader::loadLabel(QLabel* label, QPixmap pixmap){
    int imageLabelWidth = label->width();
    if(pixmap.width() > imageLabelWidth){
        QPixmap scaledPixMap = pixmap.scaledToWidth(imageLabelWidth);
        label->setPixmap(scaledPixMap);
    } else {
        label->setPixmap(pixmap);
    }
}
