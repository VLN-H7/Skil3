#include "scientistsort.h"

QString ScientistSort::toField(Field f){
    switch(f){
        case FIRST_NAME:
            return "first_name";
        case ScientistSort::LAST_NAME:
            return "last_name";
        case ScientistSort::GENDER:
            return "gender";
        case ScientistSort::BIRTH_DATE:
            return "birth_date";
        case ScientistSort::DEATH_DATE:
            return "death_date";
        case ScientistSort::NATIONALITY:
            return "nationality";
        default:
            return "first_name";
    }
}
