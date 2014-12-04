#ifndef COMPUTER_H
#define COMPUTER_H

#include <string>
#include <sstream>
#include <iostream>
#include <QSqlQuery>
#include <QVariant>
#include <QChar>

using namespace std;

class Computer

{
public:
    Computer();
    int id;
    string name;
    string type;
    int buildyear;
    bool built;

    static Computer fromQuery(const QSqlQuery* query);
    friend bool operator == (const Computer &a, const Computer &b);
};

