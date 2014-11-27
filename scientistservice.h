#ifndef SCIENTISTSERVICE_H
#define SCIENTISTSERVICE_H
#include <algorithm>
#include <vector>
#include "scientistrepository.h"
#include "scientist.h"
#include "scientistsort.h"

using namespace std;

class ScientistService
{

public:
    ScientistService();
    void add(Scientist s);
private:
    ScientistRepository scientistRepository;
};

#endif // SCIENTISTSERVICE_H
