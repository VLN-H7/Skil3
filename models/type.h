#ifndef TYPE_H
#define TYPE_H

#include <QString>

class Type
{
public:
    Type();
    int getID();
    QString getType();
    void setID(int cID);
    void setType(QString cType);

    friend bool operator ==(const Type &a, const Type &b);
private:
    QString type;
    int id;
};

#endif // TYPE_H
