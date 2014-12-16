#ifndef COMPUTERREPOSITORY_H
#define COMPUTERREPOSITORY_H

#include <vector>
#include <memory>
#include <stdexcept>
#include "../models/computer.h"
#include "../models/scientist.h"
#include "../sqlconnection.h"

using namespace std;

class ComputerRepository {
public:
    ComputerRepository();



    void add(Computer &s);
    void remove(Computer &s);
    vector<Computer> list(ComputerFields::Field field, Order order);
    vector<Computer> search(ComputerFields::Field field, size_t rows, QString query);
    vector<Computer> search(ComputerFields::Field field, QString query);
    void update(Computer &s, Computer &replace);
    vector<Computer> byScientist(Scientist &s);

    void link(Computer &c, Scientist &s);
    void unlink(Computer &c, Scientist &s);
    vector<Computer> notByScientist(Scientist &s);
    vector<Type> listTypes();
    void addType(Type &t);
    void deleteType(Type &t);
private:
    static Computer getComputer(const unique_ptr<QSqlQuery> &query);
};

#endif // COMPUTERREPOSITORY_H
