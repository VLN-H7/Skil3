#ifndef DATE_H
#define DATE_H

#include <fstream>
#include <iostream>
#include <QDate>
#include <QString>
#include <string>

using namespace std;

class Date : public QDate
{
public:
    Date();
    Date(const QDate& D);
    static Date fromString(string date);
    static Date now();
    friend ostream &operator<<( ostream &output, const Date &D );
    string toDateString() const;
};

#endif // DATE_H
