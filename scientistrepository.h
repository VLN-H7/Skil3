#ifndef SCIENTISTREPOSITORY_H
#define SCIENTISTREPOSITORY_H

#include <vector>
#include "scientist.h"

using namespace std;

class ScientistRepository
{
public:
    ScientistRepository();
    void add(Scientist s);
private:
    vector<Scientist> scientistVector;

};

#endif // SCIENTISTREPOSITORY_H
