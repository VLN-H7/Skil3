#include "scientistrepository.h"

const char delim  = ';';
const char* DATABASE = "database.txt";

ScientistRepository::ScientistRepository(){
    scientistVector = vector<Scientist>();
    read();
}

void ScientistRepository::write(Scientist s){
    ofstream write;
    write.open(DATABASE, ios::out | ios::app);
    write << s.firstName << delim
          << s.lastName << delim
          << s.gender << delim
          << s.birthdate << delim
          << s.deathdate << delim
          << s.country << endl;
    write.close();
}

void ScientistRepository::save(){
    ofstream write;
    write.open(DATABASE, ios::out);

    for(unsigned int i = 0; i < scientistVector.size() ; i++){
        write << scientistVector[i].firstName << delim
              << scientistVector[i].lastName << delim
              << scientistVector[i].gender << delim
              << scientistVector[i].birthdate << delim
              << scientistVector[i].deathdate << delim
              << scientistVector[i].country << endl;
    }

    write.close();

}

void ScientistRepository::add(Scientist s){
    scientistVector.push_back(s);
    write(s);
}

void ScientistRepository::edit(int index, ScientistSort::Field field, string change){
switch(field){
    case ScientistSort::FIRST_NAME:
        scientistVector[index].firstName = change;
        break;

    case ScientistSort::LAST_NAME:
        scientistVector[index].lastName = change;
        break;

    case ScientistSort::GENDER:

        break;

    case ScientistSort::BIRTH_DATE:

        break;

    case ScientistSort::DEATH_DATE:

        break;

    case ScientistSort::COUNTRY:

        break;

    default:

        break;

}
//        if(element == "first name")
//            scientistVector[index].firstName = change;
//        if(element == "last name")
//            scientistVector[index].lastName = change;
//    //    if(element == "gender"){
//    //        if(scientistVector[index].gender == 'M' || scientistVector[index].gender == 'm')
//    //            scientistVector[index].gender = 'F';
//    //        if(scientistVector[index].gender == 'F' || scientistVector[index].gender == 'f')
//    //            scientistVector[index].gender = 'M';
//    //    }
//    //    if(element == "birthdate")
//    //        scientistVector[index].birthdate = change;
//    //    if(element == "deathdate")
//    //        scientistVector[index].deathdate = change;
//    //    if(element == "country")
//    //        scientistVector[index].country = change;


    //Overwrites the database.txt with the new vector.
    save();
}

int ScientistRepository::whoToEdit(string name){
    int count = 0;
    int ret = -1;

    for(unsigned int i = 0; i < scientistVector.size() ; i++){
        if(scientistVector[i].firstName == name || scientistVector[i].lastName == name){
            ret = i;
            count ++;
        }
    }

    if(count == 0)
        return -1;

    if(count >= 2)
        return -2;

    if(count == 1)
        return ret;

    return 0;
}

void ScientistRepository::print(string name){
    int numb;
    for(unsigned int i = 0; i < scientistVector.size() ; i++){
        if(scientistVector[i].firstName == name || scientistVector[i].lastName == name)
        cout << " ("<< numb ++ << ") "<< scientistVector[i].firstName << " "
             << scientistVector[i].lastName << " "
             << scientistVector[i].gender << " "
             << scientistVector[i].birthdate << " "
             << scientistVector[i].deathdate << " "
             << scientistVector[i].country << endl;
            }
}

void ScientistRepository::remove(string name, int& found){

    //Searches for the name and removes it from the vector.
    for(unsigned int i = 0; i < scientistVector.size() ; i++){
        if(scientistVector[i].firstName == name || scientistVector[i].lastName == name){
            found = i;

            scientistVector.erase(scientistVector.begin() + i);
        }
    }

    //Overwrites the database.txt with the new vector.
    save();
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
    auto cmp = ScientistSort::Comparer(field, order);
    sort(ret.begin(), ret.end(), cmp);
    return ret;
}
vector<Scientist> ScientistRepository::search(ScientistSort::Field field, string query){
    return search(field, 1, query);
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

