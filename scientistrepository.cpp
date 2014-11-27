#include "scientistrepository.h"

ScientistRepository::ScientistRepository()
{
    scientistVector = vector<Scientist>();
}

void ScientistRepository::add(Scientist s){
    scientistVector.push_back(s);
}
