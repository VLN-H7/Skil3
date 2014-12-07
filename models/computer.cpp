#include "computer.h"

Computer::Computer() {
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
