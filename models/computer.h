#ifndef COMPUTER_H
#define COMPUTER_H

#include <string>
#include <QString>

#include "../sort.h"

using namespace std;

class Computer {
public:
    Computer();

    int getID();
    string getName();
    string getType();
    int getBuildYear();
    bool getBuilt();

    void setID(int ID);
    void setName(string cName);
    void setType(string cType);
    void setBuildYear(int year);
    void setBuilt(bool b);

    friend bool operator == (const Computer &a, const Computer &b);
private:
    int id;
    string name;
    string type;
    int buildyear;
    bool built;
};

namespace ComputerFields {
    enum Field {
        ID = 0, NAME = 1, TYPE = 2, BUILD_YEAR = 3, BUILT = 4
    };

    QString toField(Field f);
}

#endif // COMPUTER_H
