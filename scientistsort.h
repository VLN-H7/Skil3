#ifndef SORT_H
#define SORT_H
namespace ScientistSort {
    enum Field { FIRST_NAME = 1, LAST_NAME = 2, GENDER = 3, BIRTH_DATE = 4, DEATH_DATE = 5, COUNTRY = 6 };
    enum Order { ASC = 1, DESC = 2 };

    struct Comparer{
        Field field;
        Order order;
        Comparer(): field(FIRST_NAME), order(ASC) {}

        Comparer(Field field, Order order) : field(field), order(order) {}
        bool operator()(const Scientist &a, const Scientist &b){
            switch(field){

                case FIRST_NAME:
                    if(order == ASC){
                        return a.firstName.compare(b.firstName) < 0;
                    } else {
                        return a.firstName.compare(b.firstName) > 0;
                    }
                    break;

                case LAST_NAME:
                    if(order == ASC){
                        return a.lastName.compare(b.lastName) < 0;
                    } else {
                        return a.lastName.compare(b.lastName) > 0;
                    }
                    break;

                case GENDER:
                    if(order == ASC){
                        return a.gender < b.gender;
                    } else {
                        return a.gender > b.gender;
                    }
                    break;

                case BIRTH_DATE:
                    if(order == ASC){
                        return a.birthdate < b.birthdate;
                    } else {
                        return a.birthdate > b.birthdate;
                    }
                    break;

                case DEATH_DATE:
                    if(order == ASC){
                        return a.deathdate < b.deathdate;
                    } else {
                        return a.deathdate > b.deathdate;
                    }
                    break;

                case COUNTRY:
                    if(order == ASC){
                        return a.country.compare(b.country) < 0;
                    } else {
                        return a.country.compare(b.country) > 0;
                    }
                    break;

                default:
                    return true;
                    break;
            }
        }
    };
}

#endif // SORT_H
