#include "computerservice.h"

ComputerService::ComputerService()
{
    computerRepository = ComputerRepository();
}

void ComputerService::add(Computer &s) {
    computerRepository.add(s);
}

void ComputerService::remove(Computer &s) {
    computerRepository.remove(s);
}

void ComputerService::update(Computer &s, Computer &replace) {
    computerRepository.update(s, replace);
}

vector<Computer> ComputerService::list(ComputerFields::Field field, Order order) {
    return computerRepository.list(field,order);
}

vector<Computer> ComputerService::search(ComputerFields::Field field, int rows, QString query) {
    return computerRepository.search(field, rows, query);
}

vector<Computer> ComputerService::byScientist(Scientist &s) {
    return computerRepository.byScientist(s);
}

vector<Computer> ComputerService::notByScientist(Scientist &s) {
    return computerRepository.notByScientist(s);
}

void ComputerService::link(Computer &c, Scientist &s) {
    computerRepository.link(c,s);
}

void ComputerService::unlink(Computer &c, Scientist &s) {
    computerRepository.unlink(c,s);
}

vector<Type> ComputerService::listTypes(){
    return computerRepository.listTypes();
}

void ComputerService::addType(Type &t){
    computerRepository.addType(t);
}

void ComputerService::removeType(Type &t){
    computerRepository.removeType(t);
}
