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
