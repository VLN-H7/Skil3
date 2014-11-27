#include "scientistrepository.h"

ScientistRepository::ScientistRepository()
{
    scientistVector = vector<Scientist>();
}

void ScientistRepository::add(Scientist s){
    scientistVector.push_back(s);
    ofstream write;
    write.open("database.txt");
    write << s.firstName << ";" << s.lastName << ";" << s.gender << ";" << s.birthday << ";" << s.deathday << "\n";
    write.close();
}

void ScientistRepository::read(){
    ifstream read;
    read.open("database.txt");
    string s;
    while(read >> s){

    }
}

vector<Scientist> ScientistRepository::list(SortField field, SortOrder order){
    vector<Scientist> ret = scientistVector;
    switch(field){
        case FIRST_NAME:
            if(order == ASC){
                sort(ret.begin(), ret.end(), [](const Scientist& a, const Scientist &b) { return a.firstName < b.firstName; });
            } else {
                sort(ret.begin(), ret.end(), [](const Scientist& a, const Scientist &b) { return a.firstName > b.firstName; });
            }
            break;
        case LAST_NAME:
            if(order == ASC){
                sort(ret.begin(), ret.end(), [](const Scientist& a, const Scientist &b) { return a.lastName < b.lastName; });
            } else {
                sort(ret.begin(), ret.end(), [](const Scientist& a, const Scientist &b) { return a.lastName > b.lastName; });
            }
            break;
        case GENDER:
            if(order == ASC){
                sort(ret.begin(), ret.end(), [](const Scientist& a, const Scientist &b) { return a.gender < b.gender; });
            } else {
                sort(ret.begin(), ret.end(), [](const Scientist& a, const Scientist &b) { return a.gender > b.gender; });
            }
            break;
        case BIRTHDATE:
            if(order == ASC){
                sort(ret.begin(), ret.end(), [](const Scientist& a, const Scientist &b) { return a.birthday < b.birthday; });
            } else {
                sort(ret.begin(), ret.end(), [](const Scientist& a, const Scientist &b) { return a.birthday > b.birthday; });
            }
            break;
        case DEATHDATE:
            if(order == ASC){
                sort(ret.begin(), ret.end(), [](const Scientist& a, const Scientist &b) { return a.deathday < b.deathday; });
            } else {
                sort(ret.begin(), ret.end(), [](const Scientist& a, const Scientist &b) { return a.deathday > b.deathday; });
            }
            break;
        default:
            sort(ret.begin(), ret.end(), [](const Scientist& a, const Scientist &b) { return a.firstName < b.firstName; });
            break;
    }
    return ret;
}
