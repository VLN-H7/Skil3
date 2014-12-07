#include "scientistservice.h"

ScientistService::ScientistService()
{
    scientistRepository = ScientistRepository();
}

void ScientistService::add(Scientist &s) {
    scientistRepository.add(s);
}

void ScientistService::remove(Scientist &s) {
    scientistRepository.remove(s);
}

void ScientistService::update(Scientist& s, Scientist& replace) {
    scientistRepository.update(s, replace);
}

vector<Scientist> ScientistService::list(ScientistFields::Field field, Order order) {
    return scientistRepository.list(field,order);
}

vector<Scientist> ScientistService::search(ScientistFields::Field field, int rows, string query) {
    return scientistRepository.search(field, rows, query);
}

vector<Scientist> ScientistService::byComputer(Computer &c) {
    return scientistRepository.byComputer(c);
}
