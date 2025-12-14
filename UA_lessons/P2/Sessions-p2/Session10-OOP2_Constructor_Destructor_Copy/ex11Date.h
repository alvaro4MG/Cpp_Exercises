//Date.h

#include<iostream>

using namespace std;

//Date d; //day == 12, month == 12, year == 2020

class Date{
    private: 
        int day;
        int month;
        int year;
    public:
        Date();                         //Constructor without parameters
        Date(int d, int m, int y);      //Constructor with parameters

        //Date(int d=12, int m=12, int y=2020); //If using this, we need the Date d(?, maybe not) and not need the constructor without parameters

        void setDate(int d, int m, int y);
        int getDay();
        int getMonth();
        int getYear();
};