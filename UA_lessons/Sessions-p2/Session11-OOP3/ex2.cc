//Class attributes and methods
    //Class attributes are like global variables
    //Class methods produce ...
//"this" pointer
    //Pointer that refers to the objject that made the call?


#include<iostream>
#include "Date13.h"

using namespace std;

int main(){
    Date d(10,20,2040);
    Date f(13,4,1995);

    cout<< d.getDay() << endl;

    //cout << d << endl;    //This doesnt work, must overload

    cout << d;      //Once we declared and described ostream in .cc, we are now telling the program what to do

    cout << d.daysPerWeek <<endl;   //Like a constant is the same in both
    cout << f.daysPerWeek <<endl;

    return 0;
}

/*
    Util u;
    u.error(ERR_ID);
        OR
    Util::error(ERR_ID)     //No need for u, error is a static method


    class ToDo{
        private:
            static int nextId=1;    //Cant assign the 1 here, since it isn't constant (it is simple, but not constant), must be in the class but get the value out
    };

    ToDo.cc
    int ToDo::nextId=1;         //Don't include static
    const string ToDo:: ...;    //String isn't a simple type, so must be used like this


    Task.cc
    Task::Task(string name){}
        this->name=name;        //If it was just "name=name" it would just refer to the parameter, not the attribute

    Task t;

    t.setDeadline("20/5/2020");

    bool setDeadline(string deadline){
        this->deadline=string;
    }
*/