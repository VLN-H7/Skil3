#include "scientistcomputerservice.h"

ScientistComputerService::ScientistComputerService()
{
}

void ScientistComputerService::link(Scientist &s, Computer &c){
    scientistComputerRepository.link(s,c);
}

void ScientistComputerService::unlink(Scientist &s, Computer &c){
    scientistComputerRepository.unlink(s,c);
}


vector<Scientist> ScientistComputerService::listScientists(Computer &c){
    return scientistComputerRepository.listScientists(c);
}

vector<Computer> ScientistComputerService::listComputers(Scientist &s){
    return scientistComputerRepository.listComputers(s);
}
