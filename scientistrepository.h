#ifndef SCIENTISTREPOSITORY_H
#define SCIENTISTREPOSITORY_H

#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <algorithm>
#include "scientist.h"
#include "scientistsort.h"
#include "utils.h"

using namespace std;

class ScientistRepository
{
public:
    ScientistRepository();
    void add(Scientist s);
    void remove(Scientist s);
    vector<Scientist> list(ScientistSort::Field field, ScientistSort::Order order);
    vector<Scientist> search(ScientistSort::Field field, bool fuzzy, size_t rows, string query);
    vector<Scientist> search(ScientistSort::Field field, bool fuzzy, string query);
    void save();
    void write(Scientist s);
private:
    vector<Scientist> scientistVector;
    void read();

};

#endif // SCIENTISTREPOSITORY_H
