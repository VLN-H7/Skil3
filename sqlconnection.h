#ifndef SQLCONNECTION_H
#define SQLCONNECTION_H
#include <QSqlDatabase>
#include <QString>
#include <QSqlQuery>
#include <QFile>
#include <QVariant>
#include <QSqlError>
#include <QTextStream>
#include <memory>
#include <stdexcept>
using namespace std;
// A singleton to manage sql connections
class SQLConnection
{
  private:
    static SQLConnection* _instance;

  protected:
    SQLConnection(const char* dbName);

    QSqlDatabase db;
    QString database;

  public:
    static SQLConnection* getInstance();
    static bool drop();
    ~SQLConnection();
    bool connected();
    unique_ptr<QSqlQuery> getQuery();
  private:
    bool connect();
    bool exists();
    bool setup();
    bool disconnect();
};

#endif // SQLCONNECTION_H
