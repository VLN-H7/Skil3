#ifndef SCIENTISTSERVICE_H
#define SCIENTISTSERVICE_H

#include "scientistrepository.h"
#include "scientist.h"

class ScientistService
{

public:
    ScientistService();
    void add(Scientist s);
private:
    ScientistRepository scientistRepository;
};

#endif // SCIENTISTSERVICE_H
