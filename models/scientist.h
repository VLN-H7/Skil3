#ifndef SCIENTIST_H
#define SCIENTIST_H

#include <QString>
#include <QUrl>
#include "../date.h"
#include "../sort.h"

using namespace std;

class Scientist {
public:
    Scientist();

    int getID();
    QString getFirstName();
    QString getLastName();
    char getGender();
    Date getBirthDate();
    Date getDeathDate();
    QString getNationality();
    QUrl getImage();

    void setID(int ID);
    void setFirstName(QString fName);
    void setLastName(QString lName);
    void setGender(char g);
    void setBirthDate(Date bDate);
    void setDeathDate(Date dDate);
    void setNationality(QString nation);
    void setImage(QUrl img);

    friend bool operator ==(const Scientist &a, const Scientist &b);

private:
    int id;
    QString firstName;
    QString lastName;
    char gender;
    Date birthdate;
    Date deathdate;
    QString nationality;
    QUrl image;
};

namespace ScientistFields {
    enum Field { ID = 0, FIRST_NAME = 1, LAST_NAME = 2, GENDER = 3, BIRTH_DATE = 4, DEATH_DATE = 5, NATIONALITY = 6 };

    QString toField(Field f);
}

#endif // SCIENTIST_H
