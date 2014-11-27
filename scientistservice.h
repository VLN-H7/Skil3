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
    vector<Scientist> list(ScientistSort::SortField field, ScientistSort::SortOrder order);
private:
    ScientistRepository scientistRepository;
};

#endif // SCIENTISTSERVICE_H
