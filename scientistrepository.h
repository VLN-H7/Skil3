#ifndef SCIENTISTREPOSITORY_H
#define SCIENTISTREPOSITORY_H

#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include "scientist.h"
#include "scientistsort.h"

using namespace std;

class ScientistRepository
{
public:
    ScientistRepository();
    void add(Scientist s);
    vector<Scientist> list(ScientistSort::SortField field, ScientistSort::SortOrder order);
private:
    vector<Scientist> scientistVector;

    void read();
};

#endif // SCIENTISTREPOSITORY_H
