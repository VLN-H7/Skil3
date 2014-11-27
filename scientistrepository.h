#ifndef SCIENTISTREPOSITORY_H
#define SCIENTISTREPOSITORY_H

#include <vector>
#include "scientist.h"

using namespace std;

class ScientistRepository
{
public:
    ScientistRepository();
private:
    vector<Scientist> scientistVector;

};

#endif // SCIENTISTREPOSITORY_H
