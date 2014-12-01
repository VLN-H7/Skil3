#ifndef SCIENTIST_H
#define SCIENTIST_H

#include <string>
#include <sstream>
#include <string>
#include <iostream>
#include "date.h"

using namespace std;

class Scientist
{
public:
    Scientist();
    string firstName;
    string lastName;
    char gender;
    Date birthdate;
    Date deathdate;
    string country;
    static Scientist fromString(string s, char delim);
};

#endif // SCIENTIST_H
