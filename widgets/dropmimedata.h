#ifndef DROPMIMEDATA_H
#define DROPMIMEDATA_H
#include <QMimeData>
#include <QByteArray>
class DropMimeData : public QMimeData
{
    Q_OBJECT

public:
    DropMimeData():
        QMimeData()
    {
        type = -1;
    }

    int type;
};
#endif // DROPMIMEDATA_H
