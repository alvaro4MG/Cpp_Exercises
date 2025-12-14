//Core concepts
    //Abstraction: keep the things relevant for the program, essential characteristics of an object
    //Encapsulation: Grouping the things from abstraction
    //Interface: visible part of the other objects (what it does)
    //Modularity: dividing the problem in different parts, as independent as possible (in separate module files)

//Example of modularity: (in 2 files)
    //myClass.h: constants, declarations and methods
    //myClass.cc: implementation of methods
    //g++ myClass1.cc myClass2.cc prog.cc -o prog (compiling with just a few files, better use the "make" tool for multiple)

    //Inheritance: Define new class from another class
    //Polymorphism (not for this year): same expression refers to different actions



#include<iostream>
#include "ex21Date.h"

using namespace std;



int main(){
    Date d;

    d.day=12;       //Direct access to elements of the object, like structs. In good OOP, this isn't used, methods are used to modify the data
    d.month=45;
    d.year=2021;


    return 0;
}