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
    auto cmp = [ ]( const Scientist& lhs, const Scientist& rhs )
    {
       return lhs.firstName < rhs.firstName;
    };
    switch(field){
        case FIRST_NAME:

        case LAST_NAME:

        case GENDER:
        case BIRTHDATE:
        case DEATHDATE:
    }

    sort(ret.begin(), ret.end(), cmp);
    return ret;
}
