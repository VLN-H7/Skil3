#ifndef DATE_H
#define DATE_H

class Date
{
public:
    Date();
    Date(unsigned int d, unsigned int m, int y);
    bool validate();
private:
    unsigned int day;
    unsigned int month;
    int year;

};

#endif // DATE_H
