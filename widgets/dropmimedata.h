#ifndef DROPMIMEDATA_H
#define DROPMIMEDATA_H
#include <QMimeData>
#include <QByteArray>

// Just a subclass of QMimeData to pass the type between tables
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
