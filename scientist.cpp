#include "scientist.h"

Scientist::Scientist()
{
}

bool operator ==(const Scientist &a, const Scientist &b){
    if(a.firstName != b.firstName) return false;
    else if (a.lastName != b.lastName) return false;
    else if (a.gender != b.gender) return false;
    else if (a.birthdate != b.birthdate) return false;
    else if (a.deathdate != b.deathdate) return false;
    else if (a.nationality != b.nationality) return false;
    return true;
}
