#include "sqlconnection.h"
const char* SQL_DATABASE = "database.sqlite3";

// Future note: this is not thread safe at all -.-
SQLConnection* SQLConnection::_instance = NULL;
SQLConnection* SQLConnection::getInstance() {
    if (_instance == NULL)
    {
        _instance = new SQLConnection(SQL_DATABASE);
    }
    return _instance;
}

bool SQLConnection::drop() {
    if(_instance->db.isOpen())
        _instance->disconnect();
    bool flag = QFile::remove(SQL_DATABASE);
    delete _instance;
    _instance = NULL;
    return flag;
}

SQLConnection::~SQLConnection() {
    disconnect();
}

SQLConnection::SQLConnection(const char* dbName) {
   db = QSqlDatabase::addDatabase("QSQLITE");
   bool db_exists = exists();
   database = QString(dbName);
   db.setDatabaseName(database);
   connect();

   if (!db_exists)
   {
       setup();
   }
}

unique_ptr<QSqlQuery> SQLConnection::getQuery() {
    // Use unique_ptr because by using it the caller is freed from the contract of having to free the pointer after use.
    return unique_ptr<QSqlQuery>(new QSqlQuery(db));
}

bool SQLConnection::connect() {
    return db.open() && db.isOpen();
}


bool SQLConnection::disconnect() {
    if(db.isOpen())
        db.close();
    return !db.isOpen();
}


bool SQLConnection::exists() {
    return QFile::exists(database);
}


bool SQLConnection::setup() {
    if (!db.isOpen()) return false;
    QSqlQuery query(db);
    QFile scriptFile("tables.sql");
    // from http://stackoverflow.com/questions/3736984/multiple-sql-statements-in-qsqlquery-using-the-sqlite3-driver
    if (scriptFile.open(QIODevice::ReadOnly))
    {
        // The SQLite driver executes only a single (the first) query in the QSqlQuery
        //  if the script contains more queries, it needs to be splitted.
        QStringList scriptQueries = QTextStream(&scriptFile).readAll().split(';');

        foreach (QString queryTxt, scriptQueries)
        {
            if (queryTxt.trimmed().isEmpty()) {
                continue;
            }
            if (!query.exec(queryTxt))
            {
                throw std::runtime_error("One of the setup queries failed to execute."
                                         "Error detail:" + query.lastError().text().toStdString());
            }
            query.finish();
        }
    } else {
        return false;
    }
    return true;
}

bool SQLConnection::connected() {
   return db.isOpen();
}

