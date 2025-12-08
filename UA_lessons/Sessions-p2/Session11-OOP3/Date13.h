//Header Date.h for ex1-3

#include<iostream>

using namespace std;

//Date d; //day == 12, month == 12, year == 2020

class Date{     //In public part they work too
    friend ostream& operator<<(ostream &os, const Date &d); //const because it wont change it   //With the ostream you can link like "hello"<<"another string"
    friend istream& operator>>(istream &is, Date &d);
    private: 
        int day;
        int month;
        int year;
    public:
        static const int weeksPerYear=52;       //Static attribute, in the UML they are underlined
        static const int daysPerWeek=7;
        //static int daysPerYear=365;           //Not constant, assign in Date.cc
        static int daysPerYear;

        Date(int day, int m, int y);      //Constructor with parameters

        int getDay() const;
        int getMonth() const {return month;};  //Inline method
        int getYear() const {return year;};      //Inline method
};