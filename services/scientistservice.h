#ifndef SCIENTISTSERVICE_H
#define SCIENTISTSERVICE_H
#include <vector>
#include <string>
#include "../repositories/scientistrepository.h"
#include "../models/scientist.h"

using namespace std;

class ScientistService
{

public:
    ScientistService();
    void add(Scientist &s);
    void remove(Scientist &s);
    vector<Scientist> list(ScientistFields::Field field, Order order);
    vector<Scientist> search(ScientistFields::Field field, int rows, string query);
    void update(Scientist &s, Scientist &replace);
    vector<Scientist> byComputer(Computer &c);
private:
    ScientistRepository scientistRepository;
};

#endif // SCIENTISTSERVICE_H
