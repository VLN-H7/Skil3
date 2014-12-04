#include "computer.h"

Computer::Computer()
{
}

Computer Computer::fromQuery(const QSqlQuery* query){
    Computer comp;
    comp.id = query->value("id").toInt();
    comp.name = query->value("name").toString().toStdString();
    comp.type = query->value("type").toString().toStdString();
    comp.buildyear = query->value("build_year").toInt();
    comp.built = query->value("was_built").toBool();
    return comp;
}

bool operator ==(const Computer &a, const Computer &b){
    if(a.name != b.name) return false;
    else if (a.type != b.type) return false;
    else if (a.buildyear != b.buildyear) return false;
    else if (a.built != b.built) return false;

    return true;
}
