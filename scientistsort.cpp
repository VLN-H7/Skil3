#include "scientistsort.h"

//Comparer function that sorts Scientists
bool ScientistSort::Comparer::operator()(const Scientist &a, const Scientist &b){
    switch(field){

        case FIRST_NAME:
            if(order == ASC){
                return a.firstName.compare(b.firstName) < 0;
            } else {
                return a.firstName.compare(b.firstName) > 0;
            }
            break;

        case LAST_NAME:
            if(order == ASC){
                return a.lastName.compare(b.lastName) < 0;
            } else {
                return a.lastName.compare(b.lastName) > 0;
            }
            break;

        case GENDER:
            if(order == ASC){
                return a.gender < b.gender;
            } else {
                return a.gender > b.gender;
            }
            break;

        case BIRTH_DATE:
            if(order == ASC){
                return a.birthdate < b.birthdate;
            } else {
                return a.birthdate > b.birthdate;
            }
            break;

        case DEATH_DATE:
            if(order == ASC){
                return a.deathdate < b.deathdate;
            } else {
                return a.deathdate > b.deathdate;
            }
            break;

        case NATIONALITY:
            if(order == ASC){
                return a.nationality.compare(b.nationality) < 0;
            } else {
                return a.nationality.compare(b.nationality) > 0;
            }
            break;

        default:
            return true;
            break;
    }
}
