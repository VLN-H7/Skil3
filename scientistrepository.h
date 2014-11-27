#ifndef SCIENTISTREPOSITORY_H
#define SCIENTISTREPOSITORY_H

#include <iostream>
#include <fstream>
#include <vector>
#include "scientist.h"

using namespace std;

class ScientistRepository
{
public:
    ScientistRepository();
    void add(Scientist s);
    vector<Scientist> list(SortField field, SortOrder order);
private:
    vector<Scientist> scientistVector;

    void read();
};

#endif // SCIENTISTREPOSITORY_H
