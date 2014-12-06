#include "scientistcomputerrepository.h"

ScientistComputerRepository::ScientistComputerRepository()
{
}

void ScientistComputerRepository::link(Scientist &s, Computer &c){
    auto query = SQLConnection::getInstance()->getQuery();
    query->prepare("INSERT INTO scientist_computer (scientist_id, computer_id) VALUES (?,?)");
    query->addBindValue(s.id);
    query->addBindValue(c.id);
    if(!query->exec());
}

void ScientistComputerRepository::unlink(Scientist &s, Computer &c){
    auto query = SQLConnection::getInstance()->getQuery();
    query->prepare("DELETE FROM scientist_computer WHERE scientist_id = ? AND computer_id = ?");
    query->addBindValue(s.id);
    query->addBindValue(c.id);
    if(!query->exec());
}

vector<Scientist> ScientistComputerRepository::listScientists(Computer &c){
    vector<Scientist> ret;
    auto query = SQLConnection::getInstance()->getQuery();
    query->prepare("SELECT * FROM scientist_computer JOIN scientists ON scientists.id = scientist_computer.scientist_id WHERE computer_id = ?");
    query->addBindValue(c.id);
    if(!query->exec())
        cout << query->lastError().text().toStdString();

    while(query->next()){
        ret.push_back(ScientistRepository::getScientist(query));
    }
    return ret;
}

vector<Computer> ScientistComputerRepository::listComputers(Scientist &s){
    vector<Computer> ret;
    auto query = SQLConnection::getInstance()->getQuery();
    query->prepare("SELECT * FROM scientist_computer JOIN computers ON computers.id = scientist_computer.computer_id WHERE scientist_id = ?");
    query->addBindValue(s.id);
    if(!query->exec())
        cout << query->lastError().text().toStdString();

    while(query->next()){
        ret.push_back(ComputerRepository::getComputer(query));
    }
    return ret;
}
