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

void ScientistService::edit(int index, ScientistSort::Field field, string change){
    scientistRepository.edit(index, field, change);
}

void ScientistService::print(string name){
    scientistRepository.print(name);
}

int ScientistService::whoToEdit(string name){
    return scientistRepository.whoToEdit(name);
}


vector<Scientist> ScientistService::list(ScientistSort::Field field, ScientistSort::Order order){
    return scientistRepository.list(field,order);
}

vector<Scientist> ScientistService::search(ScientistSort::Field field, bool fuzzy, int rows, string query){
    return scientistRepository.search(field, fuzzy, rows, query);
}
