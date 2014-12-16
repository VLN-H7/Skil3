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

void ScientistService::update(Scientist &s, Scientist &replace) {
    scientistRepository.update(s, replace);
}

vector<Scientist> ScientistService::list(ScientistFields::Field field, Order order) {
    return scientistRepository.list(field,order);
}

vector<Scientist> ScientistService::search(ScientistFields::Field field, int rows, QString query) {
    if(field == ScientistFields::BIRTH_DATE || field == ScientistFields::DEATH_DATE){
        QStringList split = query.split(".");
        std::reverse(std::begin(split),std::end(split));
        query = split.join("-");
    }
    return scientistRepository.search(field, rows, query);
}

vector<Scientist> ScientistService::byComputer(Computer &c) {
    return scientistRepository.byComputer(c);
}

vector<Scientist> ScientistService::notByComputer(Computer &c) {
    return scientistRepository.notByComputer(c);
}
