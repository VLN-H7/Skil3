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

Scientist Scientist::fromQuery(const QSqlQuery* query){
    Scientist sci;
    sci.id = query->value("id").toInt();
    sci.firstName = query->value("first_name").toString().toStdString();
    sci.lastName = query->value("last_name").toString().toStdString();
    sci.gender = query->value("gender").toString().toStdString()[0];
    sci.birthdate = query->value("birth_date").toDate();
    sci.deathdate = query->value("death_date").toDate();
    sci.nationality = query->value("nationality").toString().toStdString();
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
