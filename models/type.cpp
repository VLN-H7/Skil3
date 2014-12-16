#include "type.h"

Type::Type()
{
    id = -1;
}

bool operator ==(const Type &a, const Type &b) {
    if(a.type != b.type) return false;
    return true;
}

int Type::getID(){
    return id;
}

QString Type::getType(){
    return type;
}

void Type::setID(int cID){
    if(id == -1)
        id = cID;
}

void Type::setType(QString cType){
    type = cType;
}
