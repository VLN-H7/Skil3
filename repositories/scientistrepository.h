#ifndef SCIENTISTREPOSITORY_H
#define SCIENTISTREPOSITORY_H

#include <iostream>
#include <vector>
#include <memory>
#include "../models/scientist.h"
#include "../utils.h"

#include "sqlconnection.h"

using namespace std;

class ScientistRepository
{
public:
    ScientistRepository();

    static Scientist getScientist(const unique_ptr<QSqlQuery> &query);

    void add(Scientist s);
    void remove(Scientist &s);
    vector<Scientist> list(ScientistFields::Field field, Order order);
    vector<Scientist> search(ScientistFields::Field field, size_t rows, string query);
    vector<Scientist> search(ScientistFields::Field field, string query);
    void update(Scientist &s, Scientist &replace);
};

#endif // SCIENTISTREPOSITORY_H
