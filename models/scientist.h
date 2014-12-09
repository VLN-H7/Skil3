#ifndef SCIENTIST_H
#define SCIENTIST_H

#include <QString>
#include "../date.h"
#include "../sort.h"

using namespace std;

class Scientist {
public:
    Scientist();

    int getID();
    string getFirstName();
    string getLastName();
    char getGender();
    Date getBirthDate();
    Date getDeathDate();
    string getNationality();

    void setID(int ID);
    void setFirstName(string fName);
    void setLastName(string lName);
    void setGender(char g);
    void setBirthDate(Date bDate);
    void setDeathDate(Date dDate);
    void setNationality(string nation);

    friend bool operator ==(const Scientist &a, const Scientist &b);

private:
    int id;
    string firstName;
    string lastName;
    char gender;
    Date birthdate;
    Date deathdate;
    string nationality;
};

namespace ScientistFields {
    enum Field { ID = 0, FIRST_NAME = 1, LAST_NAME = 2, GENDER = 3, BIRTH_DATE = 4, DEATH_DATE = 5, NATIONALITY = 6 };

    QString toField(Field f);
}

#endif // SCIENTIST_H
