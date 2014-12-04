#include "sqlconnection.h"
#include <iostream>
using namespace std;
const char* SQL_DATABASE = "database.sqlite3";

SQLConnection* SQLConnection::_instance = 0;
SQLConnection* SQLConnection::getInstance() {
    if (_instance == 0)
    {
        _instance = new SQLConnection;
    }
    return _instance;
}

SQLConnection::~SQLConnection() {
    disconnect();
}

SQLConnection::SQLConnection() {
   db = QSqlDatabase::addDatabase("QSQLITE");
   bool db_exists = exists();
   db.setDatabaseName(SQL_DATABASE);
   connect();

   if (!db_exists)
   {
       setup();
   }
}

QSqlQuery* SQLConnection::getQuery(){
    return new QSqlQuery(db);
}

bool SQLConnection::connect() {
    return db.open() && db.isOpen();
}


bool SQLConnection::disconnect() {
    db.close();
    return !db.isOpen();
}


bool SQLConnection::exists() {
    return QFile::exists(SQL_DATABASE);
}

bool SQLConnection::drop() {
    return QFile::remove(SQL_DATABASE);
}


bool SQLConnection::setup() {
    cout << "stuff" << endl;
    if (!db.isOpen()) return false;
    QSqlQuery query;
    QFile file("tables.sql");
    file.open(QFile::ReadOnly|QFile::Text);
    if(!query.exec(file.readAll()))
        return false;
    return true;
}

bool SQLConnection::connected() {
   return db.isOpen();
}

