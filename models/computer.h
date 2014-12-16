#ifndef COMPUTER_H
#define COMPUTER_H

#include <string>
#include <QString>
#include <QUrl>

#include "type.h"
#include "../sort.h"

using namespace std;

class Computer {
public:
    Computer();

    int getID();
    QString getName();
    Type getType();
    int getBuildYear();
    bool getBuilt();
    QUrl getImage();

    void setID(int ID);
    void setName(QString cName);
    void setType(Type cType);
    void setBuildYear(int year);
    void setBuilt(bool b);
    void setImage(QUrl img);

    friend bool operator == (const Computer &a, const Computer &b);
private:
    int id;
    QString name;
    Type type;
    int buildyear;
    bool built;
    QUrl image;
};

namespace ComputerFields {
    enum Field {
        ID = 0, NAME = 1, TYPE = 2, BUILD_YEAR = 3, BUILT = 4
    };

    QString toField(Field f);
}

#endif // COMPUTER_H
