#include "scientistrepository.h"

Scientist ScientistRepository::getScientist(const unique_ptr<QSqlQuery> &query) {
    Scientist sci;
    sci.setID(query->value("id").toInt());
    sci.setFirstName(query->value("first_name").toString());
    sci.setLastName(query->value("last_name").toString());
    sci.setGender(query->value("gender").toString().toStdString()[0]);
    sci.setBirthDate(query->value("birth_date").toDate());
    sci.setDeathDate(query->value("death_date").toDate());
    sci.setNationality(query->value("nationality").toString());
    sci.setImage(query->value("image").toUrl());
    sci.setWikipedia(query->value("wiki").toUrl());
    return sci;
}

ScientistRepository::ScientistRepository() {
}



//Adds an instance of scientist to the vector and writes it to a file
void ScientistRepository::add(Scientist &s) {
    auto query = SQLConnection::getInstance()->getQuery();
    query->prepare("INSERT INTO scientists (first_name, last_name, gender, birth_date, death_date, nationality, image, wiki) "
                   "VALUES (?,?,?,?,?,?,?,?)");
    query->addBindValue(s.getFirstName());
    query->addBindValue(s.getLastName());
    query->addBindValue(QString() + s.getGender());
    query->addBindValue(s.getBirthDate());
    query->addBindValue(s.getDeathDate());
    query->addBindValue(s.getNationality());
    query->addBindValue(s.getImage().toString());
    query->addBindValue(s.getWikipedia().toString());
    if(!query->exec())
        throw std::runtime_error(query->lastError().text().toStdString());
}


void ScientistRepository::update(Scientist &s, Scientist &replace) {
    auto query = SQLConnection::getInstance()->getQuery();
    query->prepare("UPDATE scientists "
                   "SET first_name = ?, last_name = ?, gender = ?, birth_date = ?, death_date = ?, nationality = ?, image = ?, wiki = ? "
                   "WHERE id = ?");
    query->addBindValue(replace.getFirstName());
    query->addBindValue(replace.getLastName());
    query->addBindValue(QString() + replace.getGender());
    query->addBindValue(replace.getBirthDate());
    query->addBindValue(replace.getDeathDate());
    query->addBindValue(replace.getNationality());
    query->addBindValue(replace.getImage().toString());
    query->addBindValue(replace.getWikipedia().toString());
    query->addBindValue(s.getID());
    if(!query->exec())
        throw std::runtime_error(query->lastError().text().toStdString());
}

//Removes one instance of scientist from the vector
void ScientistRepository::remove(Scientist &s) {
    // DELETE FROM ... WHERE

    auto query = SQLConnection::getInstance()->getQuery();

    // Clean all relations to other computers
    query->prepare("DELETE FROM scientist_computer WHERE scientist_id = ?");
    query->addBindValue(s.getID());
    if(!query->exec())
        throw std::runtime_error(query->lastError().text().toStdString());

    query->clear();

    query->prepare("DELETE FROM scientists WHERE id = ?");
    query->addBindValue(s.getID());
    if(!query->exec())
        throw std::runtime_error(query->lastError().text().toStdString());
}

//Sorts Scientists by selected field and order
vector<Scientist> ScientistRepository::list(ScientistFields::Field field, Order order) {
    vector<Scientist> ret;
    // SELECT * FROM scientists ORDER BY field,order
    auto query = SQLConnection::getInstance()->getQuery();
    QString sort_field = ScientistFields::toField(field), order_by;

    if(order == ASC) {
        order_by = "asc";
    } else {
        order_by = "desc";
    }
    if(!query->exec("SELECT * FROM scientists ORDER BY " + sort_field + " " + order_by))
        throw std::runtime_error(query->lastError().text().toStdString());
    while(query->next()) {
        ret.push_back(getScientist(query));
    }
    return ret;
}

//Searches for default amount of Scientists (1)
vector<Scientist> ScientistRepository::search(ScientistFields::Field field, QString query) {
    return search(field, 1, query);
}

//Searches for Scientists after the parameters selected
vector<Scientist> ScientistRepository::search(ScientistFields::Field field, size_t rows, QString search) {
    vector<Scientist> ret;
    auto query = SQLConnection::getInstance()->getQuery();
    QString search_field = ScientistFields::toField(field);
    query->prepare("SELECT * FROM scientists WHERE " + search_field + "  LIKE '%'|| ? ||'%'" + (rows > 0 ? "LIMIT " + QString::number(rows) : ""));
    query->addBindValue(search);
    if(!query->exec())
        throw std::runtime_error(query->lastError().text().toStdString());

    while(query->next()) {
        ret.push_back(getScientist(query));
    }
    return ret;
}

vector<Scientist> ScientistRepository::byComputer(Computer &c) {
    vector<Scientist> ret;
    auto query = SQLConnection::getInstance()->getQuery();
    query->prepare("SELECT scientists.* FROM scientist_computer "
                   "INNER JOIN scientists ON scientists.id = scientist_computer.scientist_id "
                   "WHERE computer_id = ?");
    query->addBindValue(c.getID());
    if(!query->exec())
        throw std::runtime_error(query->lastError().text().toStdString());

    while(query->next()) {
        ret.push_back(getScientist(query));
    }
    return ret;
}

vector<Scientist> ScientistRepository::notByComputer(Computer &c) {
    vector<Scientist> ret;
    auto query = SQLConnection::getInstance()->getQuery();
    query->prepare("SELECT * FROM scientists "
                   "WHERE scientists.id NOT IN (SELECT scientist_id FROM scientist_computer WHERE computer_id = ? )");
    query->addBindValue(c.getID());
    if(!query->exec())
        throw std::runtime_error(query->lastError().text().toStdString());

    while(query->next()) {
        ret.push_back(getScientist(query));
    }
    return ret;
}

