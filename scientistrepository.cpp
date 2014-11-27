#include "scientistrepository.h"

ScientistRepository::ScientistRepository()
{
    scientistVector = vector<Scientist>();
    read();
}

void ScientistRepository::add(Scientist s){
    scientistVector.push_back(s);
    ofstream write;
    write.open("database.txt", ios::out | ios::app);
    write << s.firstName << ";" << s.lastName << ";" << s.gender << ";" << s.birthdate << ";" << s.deathdate << "\n";
    write.close();
}

void ScientistRepository::read(){
    ifstream read;
    read.open("database.txt");
    string s;

    while(read >> s){
        scientistVector.push_back(Scientist::fromString(s,';'));
    }
    read.close();
}

vector<Scientist> ScientistRepository::list(ScientistSort::Field field, ScientistSort::Order order){
    vector<Scientist> ret(scientistVector);
    // SELECT * FROM scientists ORDER BY field,order
    switch(field){
        case ScientistSort::FIRST_NAME:
            if(order == ScientistSort::ASC){
                sort(ret.begin(), ret.end(), [](const Scientist &a, const Scientist &b) { return a.firstName < b.firstName; });
            } else {
                sort(ret.begin(), ret.end(), [](const Scientist &a, const Scientist &b) { return a.firstName > b.firstName; });
            }
            break;
        case ScientistSort::LAST_NAME:
            if(order == ScientistSort::ASC){
                sort(ret.begin(), ret.end(), [](const Scientist &a, const Scientist &b) { return a.lastName < b.lastName; });
            } else {
                sort(ret.begin(), ret.end(), [](const Scientist &a, const Scientist &b) { return a.lastName > b.lastName; });
            }
            break;
        case ScientistSort::GENDER:
            if(order == ScientistSort::ASC){
                sort(ret.begin(), ret.end(), [](const Scientist &a, const Scientist &b) { return a.gender < b.gender; });
            } else {
                sort(ret.begin(), ret.end(), [](const Scientist &a, const Scientist &b) { return a.gender > b.gender; });
            }
            break;
        case ScientistSort::BIRTH_DATE:
            if(order == ScientistSort::ASC){
                sort(ret.begin(), ret.end(), [](const Scientist &a, const Scientist &b) { return a.birthdate < b.birthdate; });
            } else {
                sort(ret.begin(), ret.end(), [](const Scientist &a, const Scientist &b) { return a.birthdate > b.birthdate; });
            }
            break;
        case ScientistSort::DEATH_DATE:
            if(order == ScientistSort::ASC){
                sort(ret.begin(), ret.end(), [](const Scientist &a, const Scientist &b) { return a.deathdate < b.deathdate; });
            } else {
                sort(ret.begin(), ret.end(), [](const Scientist &a, const Scientist &b) { return a.deathdate > b.deathdate; });
            }
            break;
        default:
            sort(ret.begin(), ret.end(), [](const Scientist &a, const Scientist &b) { return a.firstName < b.firstName; });
            break;
    }
    return ret;
}

