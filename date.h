#ifndef DATE_H
#define DATE_H

#include <fstream>
#include <iostream>
#include <QDate>
#include <QString>

using namespace std;

class Date : public QDate
{
public:
    Date();
    Date(const QDate& D);
    static Date fromString(string date);
    static Date now();
    friend istream &operator>>( istream  &input, Date &D );
    friend ostream &operator<<( ostream &output, const Date &D );
};

#endif // DATE_H
