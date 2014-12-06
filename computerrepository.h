#ifndef COMPUTERREPOSITORY_H
#define COMPUTERREPOSITORY_H

#include <iostream>
#include <vector>
#include <memory>
#include "computer.h"

#include "sqlconnection.h"

using namespace std;

class ComputerRepository
{
public:
    ComputerRepository();

    static Computer getComputer(const unique_ptr<QSqlQuery> &query);

    void add(Computer s);
    void remove(Computer &s);
    vector<Computer> list(ComputerFields::Field field, Order order);
    vector<Computer> search(ComputerFields::Field field, size_t rows, string query);
    vector<Computer> search(ComputerFields::Field field, string query);
    void update(Computer &s, Computer &replace);
};

#endif // COMPUTERREPOSITORY_H
