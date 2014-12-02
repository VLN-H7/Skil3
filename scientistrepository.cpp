#include "scientistrepository.h"

char delim  = ';';

ScientistRepository::ScientistRepository(){
    scientistVector = vector<Scientist>();
    read();
}

void ScientistRepository::add(Scientist s){
    scientistVector.push_back(s);
    ofstream write;
    write.open("database.txt", ios::out | ios::app);
    write << s.firstName << delim << s.lastName << delim << s.gender << delim << s.birthdate << delim << s.deathdate << delim << s.country << "\n";
    write.close();
}

void ScientistRepository::remove(string name, int& found){

    //Searches for the name and removes it from the vector.
    for(unsigned int i = 0; i < scientistVector.size() ; i++){
        if(scientistVector[i].firstName == name || scientistVector[i].lastName == name){
            found = i;

            for(unsigned int i = found; i < (scientistVector.size() - 1) ; i++){
                scientistVector[i].firstName = scientistVector[i+1].firstName;
                scientistVector[i].lastName = scientistVector[i+1].lastName;
                scientistVector[i].gender = scientistVector[i+1].gender;
                scientistVector[i].birthdate = scientistVector[i+1].birthdate;
                scientistVector[i].deathdate = scientistVector[i+1].deathdate;
                scientistVector[i].country = scientistVector[i+1].country;
            }
        scientistVector.pop_back();
        }
    }

    //Overwrites the database.txt with the new vector.
    ofstream write;
    write.open("database.txt", ios::out);

    for(unsigned int i = 0; i < scientistVector.size() ; i++){
        write << scientistVector[i].firstName << delim
              << scientistVector[i].lastName << delim
              << scientistVector[i].gender << delim
              << scientistVector[i].birthdate << delim
              << scientistVector[i].deathdate << delim
              << scientistVector[i].country << "\n";
    }

    write.close();
}

void ScientistRepository::read(){
    ifstream read;
    read.open("database.txt");
    string s;

    while(read >> s){
        scientistVector.push_back(Scientist::fromString(s,delim));
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

        case ScientistSort::COUNTRY:
            if(order == ScientistSort::ASC){
                sort(ret.begin(), ret.end(), [](const Scientist &a, const Scientist &b) { return a.country < b.country; });
            } else {
                sort(ret.begin(), ret.end(), [](const Scientist &a, const Scientist &b) { return a.country > b.country; });
            }
            break;

        default:
            sort(ret.begin(), ret.end(), [](const Scientist &a, const Scientist &b) { return a.firstName < b.firstName; });
            break;
    }
    return ret;
}


vector<Scientist> ScientistRepository::search(ScientistSort::Field field, int rows, string query){

    vector<Scientist> ret;

    for(auto it = scientistVector.begin(); it != scientistVector.end(); it++){
        switch(field){

            case ScientistSort::FIRST_NAME:
                if((*it).firstName == query)
                    ret.push_back((*it));
                break;

            case ScientistSort::LAST_NAME:
                if((*it).lastName == query)
                    ret.push_back((*it));
                break;

            case ScientistSort::GENDER:
                if((*it).gender == query[0])
                    ret.push_back((*it));
                break;

            case ScientistSort::BIRTH_DATE:
                if((*it).birthdate == Date::fromString(query))
                    ret.push_back((*it));
                break;

            case ScientistSort::DEATH_DATE:
                if((*it).deathdate == Date::fromString(query))
                    ret.push_back((*it));
                break;

            case ScientistSort::COUNTRY:
                if((*it).country == query)
                    ret.push_back((*it));
                break;

            default:
                if((*it).firstName == query)
                    ret.push_back((*it));
                break;
        }
        if(ret.size() > rows)
            break;
    }
    return ret;
}

