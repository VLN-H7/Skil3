#include "scientistrepository.h"

ScientistRepository::ScientistRepository()
{
    scientistVector = vector<Scientist>();
}

void ScientistRepository::add(Scientist s){
    scientistVector.push_back(s);
    ofstream write;
    write.open("database.txt");
    write << s.firstName << ";" << s.lastName << ";" << s.gender << ";" << s.birthday << ";" << s.deathday << ";\n";
    write.close();
}
