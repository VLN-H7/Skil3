#ifndef SCIENTIST_H
#define SCIENTIST_H

#include <string>
#include <QDate>

using namespace std;

class Scientist
{
public:
    Scientist();
    string firstName;
    string lastName;
    char gender;
    QDate birthday;
    QDate deathday;
};

#endif // SCIENTIST_H
