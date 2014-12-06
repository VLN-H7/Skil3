#ifndef SCIENTISTCOMPUTERREPOSITORY_H
#define SCIENTISTCOMPUTERREPOSITORY_H

#include "../sqlconnection.h"
#include "../models/scientist.h"
#include "../models/computer.h"
#include "computerrepository.h"
#include "scientistrepository.h"

class ScientistComputerRepository
{
public:
    ScientistComputerRepository();
    void link(Scientist &s, Computer &c);
    void unlink(Scientist &s, Computer &c);
    vector<Scientist> listScientists(Computer &c);
    vector<Computer> listComputers(Scientist &s);
};

#endif // SCIENTISTCOMPUTERREPOSITORY_H
