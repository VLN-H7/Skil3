#ifndef SCIENTISTREPOSITORY_H
#define SCIENTISTREPOSITORY_H

#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <algorithm>
#include "scientist.h"
#include "scientistsort.h"

using namespace std;

class ScientistRepository
{
public:
    ScientistRepository();
    void add(Scientist s);
    vector<Scientist> list(ScientistSort::Field field, ScientistSort::Order order);
    vector<Scientist> search(ScientistSort::Field field, int rows, string query);
private:
    vector<Scientist> scientistVector;

    void read();
};

#endif // SCIENTISTREPOSITORY_H
