#include "computerrepository.h"



Computer ComputerRepository::getComputer(const unique_ptr<QSqlQuery> &query) {
    Computer comp;
    Type type;
    type.setID(query->value("type_id").toInt());
    type.setType(query->value("type").toString());
    comp.setID(query->value("id").toInt());
    comp.setName(query->value("name").toString());
    comp.setType(type);
    comp.setBuildYear(query->value("build_year").toInt());
    comp.setBuilt(query->value("built").toBool());
    comp.setImage(query->value("image").toUrl());
    return comp;
}

ComputerRepository::ComputerRepository() {
}


void ComputerRepository::add(Computer &comp) {
    auto query = SQLConnection::getInstance()->getQuery();
    query->prepare("INSERT INTO computers (name, type_id, build_year, built, image) VALUES (?,?,?,?,?)");
    query->addBindValue(comp.getName());
    query->addBindValue(comp.getType().getID());
    query->addBindValue(comp.getBuildYear());
    query->addBindValue(comp.getBuilt());
    query->addBindValue(comp.getImage().toString());
    if(!query->exec())
        throw std::runtime_error(query->lastError().text().toStdString());
}


void ComputerRepository::update(Computer &comp, Computer &replace) {
    auto query = SQLConnection::getInstance()->getQuery();
    query->prepare("UPDATE computers SET name = ?, type_id = ?, build_year = ?, built = ?, image = ? WHERE id = ?");
    query->addBindValue(replace.getName());
    query->addBindValue(replace.getType().getID());
    query->addBindValue(replace.getBuildYear());
    query->addBindValue(replace.getBuilt());
    query->addBindValue(replace.getImage().toString());
    query->addBindValue(comp.getID());
    if(!query->exec())
        throw std::runtime_error(query->lastError().text().toStdString());
}


void ComputerRepository::remove(Computer &comp) {

    auto query = SQLConnection::getInstance()->getQuery();

    // clean all relations to other scientists
    query->prepare("DELETE FROM scientist_computer WHERE computer_id = ?");
    query->addBindValue(comp.getID());
    if(!query->exec())
        throw std::runtime_error(query->lastError().text().toStdString());

    query->clear();
    query->prepare("DELETE FROM computers WHERE id = ?");
    query->addBindValue(comp.getID());
    if(!query->exec())
        throw std::runtime_error(query->lastError().text().toStdString());
}

//Sorts Computers by selected field and order
vector<Computer> ComputerRepository::list(ComputerFields::Field field, Order order) {
    vector<Computer> ret;
    // SELECT * FROM Computers ORDER BY field,order
    auto query = SQLConnection::getInstance()->getQuery();
    QString sort_field = ComputerFields::toField(field), order_by;

    if(order == ASC) {
        order_by = "asc";
    } else {
        order_by = "desc";
    }
    if(!query->exec("SELECT computers.*, types.type FROM computers "
                    "LEFT JOIN types ON computers.type_id = types.id "
                    "ORDER BY " + sort_field + " " + order_by))
        throw std::runtime_error(query->lastError().text().toStdString());
    while(query->next()) {
        ret.push_back(getComputer(query));
    }
    return ret;
}

//Searches for default amount of Computers (1)
vector<Computer> ComputerRepository::search(ComputerFields::Field field, QString query) {
    return search(field, 1, query);
}

//Searches for Computers after the parameters selected
vector<Computer> ComputerRepository::search(ComputerFields::Field field, size_t rows, QString search) {
    vector<Computer> ret;
    auto query = SQLConnection::getInstance()->getQuery();
    QString search_field = ComputerFields::toField(field);
    query->prepare("SELECT computers.*, types.type FROM computers "
                   "LEFT JOIN types ON computers.type_id = types.id "
                   "WHERE " + search_field + "  LIKE '%'|| ? ||'%'" + (rows > 0 ? "LIMIT " + QString::number(rows) : ""));
    query->addBindValue(search);
    if(!query->exec())
        throw std::runtime_error(query->lastError().text().toStdString());
    while(query->next()) {
        ret.push_back(getComputer(query));
    }
    return ret;
}

vector<Computer> ComputerRepository::byScientist(Scientist &s) {
    vector<Computer> ret;
    auto query = SQLConnection::getInstance()->getQuery();
    // Select just the scientists.* to not get id conflicts.
    query->prepare("SELECT computers.*, types.type FROM scientist_computer "
                   "INNER JOIN computers ON computers.id = scientist_computer.computer_id "
                   "LEFT JOIN types ON computers.type_id = types.id "
                   "WHERE scientist_id = ?");
    query->addBindValue(s.getID());
    if(!query->exec())
        throw std::runtime_error(query->lastError().text().toStdString());

    while(query->next()) {
        ret.push_back(getComputer(query));
    }
    return ret;
}

vector<Computer> ComputerRepository::notByScientist(Scientist &s) {
    vector<Computer> ret;
    auto query = SQLConnection::getInstance()->getQuery();
    // Select just the scientists.* to not get id conflicts.
    query->prepare("SELECT computers.*, types.type FROM computers "
                   "LEFT JOIN types ON computers.type_id = types.id "
                   "WHERE computers.id NOT IN (SELECT computer_id FROM scientist_computer WHERE scientist_id = ? )");
    query->addBindValue(s.getID());
    if(!query->exec())
        throw std::runtime_error(query->lastError().text().toStdString());

    while(query->next()) {
        ret.push_back(getComputer(query));
    }
    return ret;
}

void ComputerRepository::link(Computer &c, Scientist &s) {
    auto query = SQLConnection::getInstance()->getQuery();
    query->prepare("INSERT INTO scientist_computer (scientist_id, computer_id) VALUES (?,?)");
    query->addBindValue(s.getID());
    query->addBindValue(c.getID());
    if(!query->exec())
        throw std::runtime_error(query->lastError().text().toStdString());
}

void ComputerRepository::unlink(Computer &c, Scientist &s) {
    auto query = SQLConnection::getInstance()->getQuery();
    query->prepare("DELETE FROM scientist_computer WHERE scientist_id = ? AND computer_id = ?");
    query->addBindValue(s.getID());
    query->addBindValue(c.getID());
    if(!query->exec())
        throw std::runtime_error(query->lastError().text().toStdString());
}

vector<Type> ComputerRepository::listTypes(){
    auto query = SQLConnection::getInstance()->getQuery();
    query->prepare("SELECT * FROM types");
    if(!query->exec())
        throw std::runtime_error(query->lastError().text().toStdString());
    vector<Type> ret;
    while(query->next()) {
        Type type;
        type.setID(query->value("id").toInt());
        type.setType(query->value("type").toString());
        ret.push_back(type);
    }
    return ret;
}

void ComputerRepository::addType(Type &t){
    auto query = SQLConnection::getInstance()->getQuery();
    query->prepare("INSERT INTO types (type) VALUES ( ? )");
    query->addBindValue(t.getType());
    if(!query->exec())
        throw std::runtime_error(query->lastError().text().toStdString());
}

void ComputerRepository::removeType(Type &t){
    auto query = SQLConnection::getInstance()->getQuery();
    query->prepare("UPDATE computers SET type_id = NULL WHERE type_id = ?");
    query->addBindValue(t.getID());
    if(!query->exec())
        throw std::runtime_error(query->lastError().text().toStdString());

    query->clear();

    query->prepare("DELETE FROM types WHERE id = ?");
    query->addBindValue(t.getID());
    if(!query->exec())
        throw std::runtime_error(query->lastError().text().toStdString());
}
