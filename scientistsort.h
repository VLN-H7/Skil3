#ifndef SORT_H
#define SORT_H
#include "scientist.h"

namespace ScientistSort {
    enum Field { FIRST_NAME = 1, LAST_NAME = 2, GENDER = 3, BIRTH_DATE = 4, DEATH_DATE = 5, NATIONALITY = 6 };
    enum Order { ASC = 1, DESC = 2 };

    QString toField(Field f);
}

#endif // SORT_H
