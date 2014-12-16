#ifndef COMPUTERSERVICE_H
#define COMPUTERSERVICE_H

#include <vector>
#include <string>
#include "../repositories/computerrepository.h"
#include "../models/computer.h"

using namespace std;

class ComputerService {

public:
    ComputerService();
    void add(Computer &s);
    void remove(Computer &s);
    vector<Computer> list(ComputerFields::Field field, Order order);
    vector<Computer> search(ComputerFields::Field field, int rows, QString query);
    void update(Computer &s, Computer &replace);
    vector<Computer> byScientist(Scientist &s);
    void unlink(Computer &c, Scientist &s);
    void link(Computer &c, Scientist &s);
    vector<Computer> notByScientist(Scientist &s);
    vector<Type> listTypes();
    void addType(Type &t);
    void removeType(Type &t);
private:
    ComputerRepository computerRepository;
};


#endif // COMPUTERSERVICE_H
