#ifndef SORT_H
#define SORT_H
#include "scientist.h"

namespace ScientistSort {
    enum Field { FIRST_NAME = 1, LAST_NAME = 2, GENDER = 3, BIRTH_DATE = 4, DEATH_DATE = 5, NATIONALITY = 6 };
    enum Order { ASC = 1, DESC = 2 };

    struct Comparer{
        Field field;
        Order order;
        Comparer(): field(FIRST_NAME), order(ASC) {}

        Comparer(Field field, Order order) : field(field), order(order) {}
        bool operator()(const Scientist &a, const Scientist &b);
    };
}

#endif // SORT_H
