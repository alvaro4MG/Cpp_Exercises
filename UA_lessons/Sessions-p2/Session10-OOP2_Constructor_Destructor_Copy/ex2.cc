//Destructor (not have to decleare them in our assignment, the default works perfectly)
    //Declared lke ~Date()  (which frees it, use delete)
    //If the destructor must do something like "delete p" for deleting a pointer, then you need your own destructor

//Copy constructor (not needed in assignment)
    //Creates a new object from a existing one
    /*
        //Declaration
            Date(const Date &d);
        //Implementation
            Date::Date(const Date &d){
                day=d.day;
                month=d.month;
                year=d.year;
            }
        //In main
            Date d(1,1,2020);   //Constructor
            Date f(d);          //Copy constructor
            of use f=d; and n ot (d)  //Assignment operator not studied in Programming2 (copies whole obejct, can't do just copy private values)
    */


//Inline declaration
    //When there is very short code (1 line), you can write it in the header file or declaring in .cc like inline int Date:: ...
        //int getDay() {return day;}
        //int getMonth() {return month;}

#include <iostream>
#include "ex11Date.h"

using namespace std;

void doNothing(){
    cout<<"i'm in the funciton"<<endl;
    Date f; //After the function this doesn't exists, it is destroyed
}

int main(){





    return 0;
}