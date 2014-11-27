#ifndef SCIENTIST_H
#define SCIENTIST_H

#include <string>
#include "date.h"

using namespace std;

class Scientist
{
public:
    Scientist();
    string firstName;
    string lastName;
    char gender;
    Date birthday;
    Date deathday;
};

#endif // SCIENTIST_H
