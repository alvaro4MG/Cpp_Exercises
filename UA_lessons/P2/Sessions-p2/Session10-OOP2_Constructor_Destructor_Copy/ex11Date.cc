//Date.cc
#include "ex11Date.h"

Date::Date(){
    day=1;
    month=1;
    year=1900;
}

Date::Date(int d, int m, int y){
    day=d;
    month=m;
    year=y;
}

void Date::setDate(int d,int m,int y){      //Function for Date, needs "Date::"
    day=d;
    month=m;
    year=y;
}

int Date::getDay(){
    return day;
}

int Date::getMonth(){
    return month;
}
int Date::getYear(){
    return year;
}