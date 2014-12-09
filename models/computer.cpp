#include "computer.h"

Computer::Computer() {
    id = -1;
}

bool operator ==(const Computer &a, const Computer &b) {
    if(a.name != b.name) return false;
    else if (a.type != b.type) return false;
    else if (a.buildyear != b.buildyear) return false;
    else if (a.built != b.built) return false;

    return true;
}

QString ComputerFields::toField(Field f) {
    switch(f) {
        case ID:
            return "id";
        case NAME:
            return "name";
        case TYPE:
            return "type";
        case BUILD_YEAR:
            return "build_year";
        case BUILT:
            return "built";
        default:
            return "name";
    }
}

int Computer::getID(){
    return id;
}

string Computer::getName(){
    return name;
}

string Computer::getType(){
    return type;
}

int Computer::getBuildYear(){
    return buildyear;
}

bool Computer::getBuilt(){
    return built;
}

void Computer::setID(int ID){
    if(id == -1)
        id = ID;
}

void Computer::setName(string cName){
    name = cName;
}

void Computer::setType(string cType){
    // TODO: make this uniform, perhaps with a table?
    // It is not clear what types of computers should be defined, so it is left as a string for now.
    type = cType;
}

void Computer::setBuildYear(int year){
    buildyear = year;
}

void Computer::setBuilt(bool b){
    built = b;
}
