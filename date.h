#ifndef DATE_H
#define DATE_H

#include <fstream>
#include <iostream>

using namespace std;

class Date
{
public:
    Date();
    Date(unsigned int d, unsigned int m, int y);
    bool validate();
    friend istream &operator>>( istream  &input, Date &D );
    friend ostream &operator<<( ostream &output, const Date &D );
    friend bool operator<(const Date &d1, const Date &d2);
    friend bool operator==(const Date &d1, const Date &d2);
private:
    unsigned int day;
    unsigned int month;
    int year;

};

#endif // DATE_H
