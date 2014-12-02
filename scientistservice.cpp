#include "scientistservice.h"

ScientistService::ScientistService()
{
    scientistRepository = ScientistRepository();
}

void ScientistService::add(Scientist s) {
    scientistRepository.add(s);
}

void ScientistService::remove(Scientist s){
    scientistRepository.remove(s);
}

vector<Scientist> ScientistService::list(ScientistSort::Field field, ScientistSort::Order order){
    return scientistRepository.list(field,order);
}

vector<Scientist> ScientistService::search(ScientistSort::Field field, int rows, string query){
    return scientistRepository.search(field, rows, query);
}
