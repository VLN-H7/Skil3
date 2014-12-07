#ifndef COMPUTER_H
#define COMPUTER_H

#include <string>
#include <QString>

#include "sort.h"

using namespace std;

class Computer {
public:
    Computer();
    int id;
    string name;
    string type;
    int buildyear;
    bool built;

    friend bool operator == (const Computer &a, const Computer &b);
};

namespace ComputerFields {
    enum Field {
        ID = 0, NAME = 1, TYPE = 2, BUILD_YEAR = 3, BUILT = 4
    };

    QString toField(Field f);
}

#endif // COMPUTER_H
