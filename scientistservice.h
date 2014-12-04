#ifndef SCIENTISTSERVICE_H
#define SCIENTISTSERVICE_H
#include <vector>
#include <string>
#include "scientistrepository.h"
#include "scientist.h"

using namespace std;

class ScientistService
{

public:
    ScientistService();
    void add(Scientist s);
    void remove(Scientist s);
    vector<Scientist> list(ScientistFields::Field field, Order order);
    vector<Scientist> search(ScientistFields::Field field, int rows, string query);
    void update(Scientist &s, Scientist &replace);
private:
    ScientistRepository scientistRepository;
};

#endif // SCIENTISTSERVICE_H
