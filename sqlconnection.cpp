#include "sqlconnection.h"
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

unique_ptr<QSqlQuery> SQLConnection::getQuery(){
    // Use unique_ptr because by using it the caller is freed from the contract of having to free the pointer after use.
    return unique_ptr<QSqlQuery>(new QSqlQuery(db));
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
                qFatal(QString("One of the query failed to execute."
                            " Error detail: " + query.lastError().text()).toLocal8Bit());
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

