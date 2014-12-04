#ifndef COMPUTERSERVICE_H
#define COMPUTERSERVICE_H

#include <vector>
#include <string>
#include "computerrepository.h"
#include "computer.h"

using namespace std;

class ComputerService
{

public:
    ComputerService();
    void add(Computer s);
    void remove(Computer s);
    vector<Computer> list(ComputerFields::Field field, Order order);
    vector<Computer> search(ComputerFields::Field field, int rows, string query);
    void update(Computer &s, Computer &replace);
private:
    ComputerRepository computerRepository;
};


#endif // COMPUTERSERVICE_H
