#ifndef SCIENTISTCOMPUTERSERVICE_H
#define SCIENTISTCOMPUTERSERVICE_H

#include "../models/scientist.h"
#include "../models/computer.h"
#include "../repositories/scientistcomputerrepository.h"

class ScientistComputerService
{
public:
    ScientistComputerService();
    void link(Scientist &s, Computer &c);
    void unlink(Scientist &s, Computer &c);
    vector<Scientist> listScientists(Computer &c);
    vector<Computer> listComputers(Scientist &s);
private:
    ScientistComputerRepository scientistComputerRepository;
};

#endif // SCIENTISTCOMPUTERSERVICE_H
