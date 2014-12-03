#include "scientist.h"

Scientist::Scientist()
{
}

//Reads scientist from a delimited string
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
                sci.nationality = item;
                break;
            default:
                break;

        }
        i++;
    }
    return sci;
}

Scientist Scientist::fromQuery(const QSqlQuery query){
    Scientist sci;
    for(int i = 0; i < 7; i++) {
        switch(i){
            case 0:
                sci.id = query.value(i).toInt();
                break;
            case 1:
                sci.firstName = query.value(i).toString().toStdString();
                break;
            case 2:
                sci.lastName = query.value(i).toString().toStdString();
                break;
            case 3:
                sci.gender = query.value(i).toString().toStdString()[0];
                break;
            case 4:
                sci.birthdate = query.value(i).toDate();
                break;
            case 5:
                sci.deathdate = query.value(i).toDate();
                break;
            case 6:
                sci.nationality = query.value(i).toString().toStdString();
                break;
            default:
                break;

        }
    }
    return sci;
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
