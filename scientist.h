#ifndef SCIENTIST_H
#define SCIENTIST_H

#include <sstream>
#include <QSqlQuery>
#include <QVariant>
#include "date.h"

using namespace std;

class Scientist
{
public:
    Scientist();
    int id;
    string firstName;
    string lastName;
    char gender;
    Date birthdate;
    Date deathdate;
    string nationality;
    friend bool operator ==(const Scientist &a, const Scientist &b);
};

#endif // SCIENTIST_H
