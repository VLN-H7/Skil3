#include "date.h"

Date::Date()
{
    day = 1;
    month = 1;
    year = 1;
}
Date::Date(unsigned int d, unsigned int m, int y){
    day = d;
    month = m;
    year = y;
}
bool Date::validate(){
    if(month <= 0 || month > 12) return false;
    else if(day < 0 && day > 31) return false;
    else if((month == 4 || month == 6 || month == 9 || month == 11) && day > 30) return false;
    else if(month == 2){
        if(year % 4 != 0) return day <= 28;
        else if(year % 100 != 0) return day <= 29;
        else if (year % 400 != 0) return day <= 28;
        else return day <= 29;
    }
    return year != 0;
}

