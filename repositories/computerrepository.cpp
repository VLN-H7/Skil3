#include "computerrepository.h"



Computer ComputerRepository::getComputer(const unique_ptr<QSqlQuery> &query){
    Computer comp;
    comp.id = query->value("id").toInt();
    comp.name = query->value("name").toString().toStdString();
    comp.type = query->value("type").toString().toStdString();
    comp.buildyear = query->value("build_year").toInt();
    comp.built = query->value("built").toBool();
    return comp;
}

ComputerRepository::ComputerRepository(){
}


void ComputerRepository::add(Computer comp){
    auto query = SQLConnection::getInstance()->getQuery();
    query->prepare("INSERT INTO computers (name, type, build_year, built) VALUES (?,?,?,?)");
    query->addBindValue(QString::fromStdString(comp.name));
    query->addBindValue(QString::fromStdString(comp.type));
    query->addBindValue(comp.buildyear);
    query->addBindValue(comp.built);
    if(!query->exec())
        throw std::runtime_error(query->lastError().text().toStdString());
}


void ComputerRepository::update(Computer &comp, Computer &replace){
    auto query = SQLConnection::getInstance()->getQuery();
    query->prepare("UPDATE computers SET name = ?, type = ?, build_year = ?, built = ? WHERE id = ?");
    query->addBindValue(QString::fromStdString(replace.name));
    query->addBindValue(QString::fromStdString(replace.type));
    query->addBindValue(replace.buildyear);
    query->addBindValue(replace.built);
    query->addBindValue(comp.id);
    if(!query->exec())
        throw std::runtime_error(query->lastError().text().toStdString());
}


void ComputerRepository::remove(Computer &comp){

    auto query = SQLConnection::getInstance()->getQuery();
    query->prepare("DELETE FROM computers WHERE id = ?");
    query->addBindValue(comp.id);
    if(!query->exec())
        throw std::runtime_error(query->lastError().text().toStdString());

    query->clear();

    // Also clean all relations to other computers
    query->prepare("DELETE FROM scientist_computer WHERE computer_id = ?");
    query->addBindValue(comp.id);
    if(!query->exec())
        throw std::runtime_error(query->lastError().text().toStdString());
}

//Sorts Computers by selected field and order
vector<Computer> ComputerRepository::list(ComputerFields::Field field, Order order){
    vector<Computer> ret;
    // SELECT * FROM Computers ORDER BY field,order
    auto query = SQLConnection::getInstance()->getQuery();
    QString sort_field = ComputerFields::toField(field), order_by;

    if(order == ASC){
        order_by = "asc";
    } else {
        order_by = "desc";
    }
    if(!query->exec("SELECT * FROM computers ORDER BY " + sort_field + " " + order_by))
        throw std::runtime_error(query->lastError().text().toStdString());
    while(query->next()){
        ret.push_back(getComputer(query));
    }
    return ret;
}

//Searches for default amount of Computers (1)
vector<Computer> ComputerRepository::search(ComputerFields::Field field, string query){
    return search(field, 1, query);
}

//Searches for Computers after the parameters selected
vector<Computer> ComputerRepository::search(ComputerFields::Field field, size_t rows, string search){
    vector<Computer> ret;
    auto query = SQLConnection::getInstance()->getQuery();
    QString search_field = ComputerFields::toField(field);
    // TODO: figure out why appending rows straight to the query does not work
    query->prepare("SELECT * FROM computers WHERE " + search_field + "= ? LIMIT " + QString::fromStdString(to_string(rows)));
    query->addBindValue(QString::fromStdString(search));
    if(!query->exec())
        throw std::runtime_error(query->lastError().text().toStdString());
    while(query->next()){
        ret.push_back(getComputer(query));
    }
    return ret;
}

vector<Computer> ComputerRepository::byScientist(Scientist &s){
    vector<Computer> ret;
    auto query = SQLConnection::getInstance()->getQuery();
    query->prepare("SELECT * FROM scientist_computer "
                   "INNER JOIN computers ON computers.id = scientist_computer.computer_id "
                   "WHERE scientist_id = ?");
    query->addBindValue(s.id);
    if(!query->exec())
        throw std::runtime_error(query->lastError().text().toStdString());

    while(query->next()){
        ret.push_back(getComputer(query)); // TODO: fix this, the id has the possibility of being incorrect
    }
    return ret;
}

void ComputerRepository::link(Computer &c, Scientist &s){
    auto query = SQLConnection::getInstance()->getQuery();
    query->prepare("INSERT INTO scientist_computer (scientist_id, computer_id) VALUES (?,?)");
    query->addBindValue(s.id);
    query->addBindValue(c.id);
    if(!query->exec())
        throw std::runtime_error(query->lastError().text().toStdString());
}

void ComputerRepository::unlink(Computer &c, Scientist &s){
    auto query = SQLConnection::getInstance()->getQuery();
    query->prepare("DELETE FROM scientist_computer WHERE scientist_id = ? AND computer_id = ?");
    query->addBindValue(s.id);
    query->addBindValue(c.id);
    if(!query->exec())
        throw std::runtime_error(query->lastError().text().toStdString());
}
