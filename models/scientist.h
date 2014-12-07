#ifndef SCIENTIST_H
#define SCIENTIST_H

#include <QString>
#include "date.h"
#include "sort.h"

using namespace std;

class Scientist {
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

namespace ScientistFields {
    enum Field { ID = 0, FIRST_NAME = 1, LAST_NAME = 2, GENDER = 3, BIRTH_DATE = 4, DEATH_DATE = 5, NATIONALITY = 6 };

    QString toField(Field f);
}

#endif // SCIENTIST_H
