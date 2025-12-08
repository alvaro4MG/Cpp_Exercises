//Object oriented programming (OOP)
    //Uses objetcs and interactions to design software
    //Application is a cooperation of objects and their relationships
    //By the moment we have been doing imperative (procedural) programming, but c++ also lets object oriented programming
    //You have to think, instead of functions, in classes, methods ...

//Objects and classes
    //Strings are classes (string s; ///Declare an object s of string class)
    //Class is a model for creating objects of that type
    //Object of a certain class is called an instance of that class (s is an instance/object of the class string)
    //classes are similar to simple types, but allow more functionalities
//A class is similar to a struct (a "light" class) that stores visible data
    //A class stores values for the attributes
    //A class contains data and a set of functions that manipulatethis data, called member functions or methods (like s.length(), length is a method)
    //These can be visible (public) or hidden (private), but methods can access both



#include<iostream>

using namespace std;

struct TDate{
    int day;
    int month;
    int year;
};

class Date{     //Bad example, doesn't have any advantages
    public:         //Public data, atributes are public
        int day;
        int month;
        int year;
};

/*
class Date{
    private:        //Only accessible with class methods
        int day;
        int month;
        int year;
    public:
        void setDate(int d,int m,int y){...};
        //int year could be here, it depends on the design
};
*/

void Date::setDate(int d,int m,int y){      //Function for Date, needs "Date::"
    //...
}

int main(){
    Date d;

    d.day=12;       //Direct access to elements of the object, like structs. In good OOP, this isn't used, methods are used to modify the data
    d.month=45;
    d.year=2021;

/*
    d.day=12; is impossible, cannot access it

    d.setDate(12,45,2021);
*/


    return 0;
}