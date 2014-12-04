#include "scientistrepository.h"


//Constructor that makes a new vector of Scientists and reads into it from a file
ScientistRepository::ScientistRepository(){
}

Scientist ScientistRepository::getScientist(const QSqlQuery* query){
    Scientist sci;
    sci.id = query->value("id").toInt();
    sci.firstName = query->value("first_name").toString().toStdString();
    sci.lastName = query->value("last_name").toString().toStdString();
    sci.gender = query->value("gender").toString().toStdString()[0];
    sci.birthdate = query->value("birth_date").toDate();
    sci.deathdate = query->value("death_date").toDate();
    sci.nationality = query->value("nationality").toString().toStdString();
    return sci;
}

//Adds an instance of scientist to the vector and writes it to a file
void ScientistRepository::add(Scientist s){
    //scientistVector.push_back(s);
    auto query = SQLConnection::getInstance()->getQuery();
    query->prepare("insert into scientists (first_name, last_name, gender, birth_date, death_date, nationality) values (?,?,?,?,?,?)");
    query->addBindValue(QString::fromStdString(s.firstName));
    query->addBindValue(QString::fromStdString(s.lastName));
    query->addBindValue(QString() + s.gender);
    query->addBindValue(s.birthdate);
    query->addBindValue(s.deathdate);
    query->addBindValue(QString::fromStdString(s.nationality));
    query->exec();
}


void ScientistRepository::update(Scientist &s, Scientist &replace){
    //Searches for the name and removes it from the vector.
    // UPDATE scientists SET ...
    auto query = SQLConnection::getInstance()->getQuery();
    query->prepare("update scientists set first_name = ?, last_name = ?, gender = ?, birth_date = ?, death_date = ?, nationality = ? where id = ?");
    query->addBindValue(QString::fromStdString(replace.firstName));
    query->addBindValue(QString::fromStdString(replace.lastName));
    query->addBindValue(QString() + replace.gender);
    query->addBindValue(replace.birthdate);
    query->addBindValue(replace.deathdate);
    query->addBindValue(QString::fromStdString(replace.nationality));
    query->addBindValue(s.id);
    query->exec();
}

//Removes one instance of scientist from the vector
void ScientistRepository::remove(Scientist &s){
    // DELETE FROM ... WHERE

    auto connection = SQLConnection::getInstance();
    auto query = connection->getQuery();
    query->prepare("delete from scientists where id = ?");
    query->addBindValue(s.id);
    query->exec();
}

//Sorts Scientists by selected field and order
vector<Scientist> ScientistRepository::list(ScientistSort::Field field, ScientistSort::Order order){
    vector<Scientist> ret;
    // SELECT * FROM scientists ORDER BY field,order
    auto query = SQLConnection::getInstance()->getQuery();
    QString sort_field = ScientistSort::toField(field), order_by;

    if(order == ScientistSort::ASC){
        order_by = "asc";
    } else {
        order_by = "desc";
    }
    if(!query->exec("SELECT * FROM scientists ORDER BY " + sort_field + " " + order_by))
        cout << query->lastError().text().toStdString();
    while(query->next()){
        ret.push_back(getScientist(query));
    }
    return ret;
}

//Searches for default amount of Scientists (1)
vector<Scientist> ScientistRepository::search(ScientistSort::Field field, bool fuzzy, string query){
    return search(field, fuzzy, 1, query);
}

//Searches for Scientists after the parameters selected
//If fuzzy is true then it finds everything that is within 2 Levenshtein distance from the original query
vector<Scientist> ScientistRepository::search(ScientistSort::Field field, bool fuzzy, size_t rows, string search){
    vector<Scientist> ret;
    auto query = SQLConnection::getInstance()->getQuery();
    QString search_field = ScientistSort::toField(field);
    query->prepare("SELECT * FROM scientists WHERE " + search_field + " = ? LIMIT " + rows);
    query->addBindValue(QString::fromStdString(search));
    if(!query->exec())
        cout << query->lastError().text().toStdString();

    while(query->next()){
        ret.push_back(getScientist(query));
    }
    return ret;
}

