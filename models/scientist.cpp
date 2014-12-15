#include "scientist.h"

Scientist::Scientist() {
    id = -1;
}

bool operator ==(const Scientist &a, const Scientist &b) {
    if(a.firstName != b.firstName) return false;
    else if (a.lastName != b.lastName) return false;
    else if (a.gender != b.gender) return false;
    else if (a.birthdate != b.birthdate) return false;
    else if (a.deathdate != b.deathdate) return false;
    else if (a.nationality != b.nationality) return false;
    return true;
}

QString ScientistFields::toField(Field f) {
    switch(f) {
        case ID:
            return "id";
        case FIRST_NAME:
            return "first_name";
        case ScientistFields::LAST_NAME:
            return "last_name";
        case ScientistFields::GENDER:
            return "gender";
        case ScientistFields::BIRTH_DATE:
            return "birth_date";
        case ScientistFields::DEATH_DATE:
            return "death_date";
        case ScientistFields::NATIONALITY:
            return "nationality";
        default:
            return "first_name";
    }
}

int Scientist::getID(){
    return id;
}

QString Scientist::getFirstName(){
    return firstName;
}

QString Scientist::getLastName(){
    return lastName;
}

char Scientist::getGender(){
    return gender;
}

Date Scientist::Scientist::getBirthDate(){
    return birthdate;
}

Date Scientist::getDeathDate(){
    return deathdate;
}

QString Scientist::getNationality(){
    return nationality;
}

QString Scientist::getImage(){
    return image;
}

void Scientist::setID(int ID){
    if(id==-1) // Only allow setting the id once, it is database-specific and should not be changed
        id = ID;
}

void Scientist::setFirstName(QString fName){
    firstName = fName;
}

void Scientist::setLastName(QString lName){
    lastName = lName;
}

void Scientist::setGender(char g){
    gender = g;
}

void Scientist::setBirthDate(Date bDate){
    birthdate = bDate;
}

void Scientist::setDeathDate(Date dDate){
    deathdate = dDate;
}

void Scientist::setNationality(QString nation){
    nationality = nation;
}

void Scientist::setImage(QString img){
    image = img;
}
