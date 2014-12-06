#include "scientist.h"

Scientist::Scientist()
{
}

bool operator ==(const Scientist &a, const Scientist &b){
    if(a.firstName != b.firstName) return false;
    else if (a.lastName != b.lastName) return false;
    else if (a.gender != b.gender) return false;
    else if (a.birthdate != b.birthdate) return false;
    else if (a.deathdate != b.deathdate) return false;
    else if (a.nationality != b.nationality) return false;
    return true;
}

QString ScientistFields::toField(Field f){
    switch(f){
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
