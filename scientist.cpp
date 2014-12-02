#include "scientist.h"

Scientist::Scientist()
{
}

Scientist Scientist::fromString(string s, char delim){
    stringstream ss(s), dateStream;
    string item;
    int i = 0;
    Scientist sci;
    while (getline(ss, item, delim)) {
        switch(i){
            case 0:
                sci.firstName = item;
                break;
            case 1:
                sci.lastName = item;
                break;
            case 2:
                sci.gender = item[0];
                break;
            case 3:
                sci.birthdate = Date::fromString(item);
                break;
            case 4:
                sci.deathdate = Date::fromString(item);
                break;
            case 5:
                sci.country = item;
                break;
            default:
                break;

        }
        i++;
    }
    return sci;
}
bool operator ==(const Scientist &a, const Scientist &b){
    if(a.firstName != b.firstName) return false;
    else if (a.lastName != b.lastName) return false;
    else if (a.gender != b.gender) return false;
    else if (a.birthdate != b.birthdate) return false;
    else if (a.deathdate != b.deathdate) return false;
    else if (a.country != b.country) return false;
    return true;
}
