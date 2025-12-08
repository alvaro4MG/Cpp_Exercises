//Date.cc
#include "Date13.h"

int Date::daysPerYear=365;

Date::Date(int day, int m, int y){
    this->day=day;      //Pointer to object that made the call
    month=m;
    year=y;
}

int Date::getDay() const{
    return day;
}

//Dont include "friend"
ostream& operator<<(ostream &os, const Date &d){
    os << d.year << "-" << d.getMonth() << "-" << d.day << endl;

    return os;
}

istream& operator>>(istream &is, Date &d){
    char dummy;

    is >> d.year >> dummy >> d.month >> dummy >> d.day;    //First integer for year, then / or - for dummy, the second integer for month

    return is;
}