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
    string nationality;
    static Scientist fromString(string s, char delim);
    friend bool operator ==(const Scientist &a, const Scientist &b);
};

#endif // SCIENTIST_H
