#ifndef SCIENTISTSERVICE_H
#define SCIENTISTSERVICE_H
#include <vector>
#include <string>
#include "scientistrepository.h"
#include "scientist.h"
#include "scientistsort.h"

using namespace std;

class ScientistService
{

public:
    ScientistService();
    void add(Scientist s);
    void remove(Scientist s);
    vector<Scientist> list(ScientistSort::Field field, ScientistSort::Order order);
    vector<Scientist> search(ScientistSort::Field field, bool fuzzy, int rows, string query);
    void update(Scientist &s, Scientist &replace);
private:
    ScientistRepository scientistRepository;
};

#endif // SCIENTISTSERVICE_H
