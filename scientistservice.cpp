#include "scientistservice.h"

ScientistService::ScientistService()
{
    scientistRepository = ScientistRepository();
}

void ScientistService::add(Scientist s) {
    scientistRepository.add(s);
}

vector<Scientist> ScientistService::list(ScientistSort::Field field, ScientistSort::Order order){
    return scientistRepository.list(field,order);
}
