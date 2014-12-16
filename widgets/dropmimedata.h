#ifndef DROPMIMEDATA_H
#define DROPMIMEDATA_H
#include <QMimeData>
#include <QByteArray>
class DropMimeData : public QMimeData
{
    Q_OBJECT

public:
    int type;
    QMimeData* realData;
};
#endif // DROPMIMEDATA_H
