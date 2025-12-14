//All classes must implement these 4 methods: constructor, destructor, copy constructor and assignment operator (the compiler creates them by default, but they are heavier) [in assignment 3 only constructors]
    //The constructor: automatically called when a new object of the class is created (you need at least 1 or more, if not, the compiler creates one, but the values are uninitialised)
        //Date::Date()  without parameters =/= Date::Date(d,m,y) with parameters
        //They can have default parameters in header file, not .cc (class Date{...Date(int d=1,int m=3,int y=2020)...})

#include<iostream>
//Use Date.h
#include "ex11Date.h"   //Itis in other directory

using namespace std;

int main(){
    string s;       //string is a class and s is an object => Constructor creates it
    Date d;

    //d.setDate(12,12,2021);  //Without a constructor   Date()

    cout<< d.getDay()<<endl;    //Without a default value
    cout<< d.getMonth()<<endl;
    cout<< d.getYear()<<endl;

    //After creating constructors
    //Call them with:
  //Date d;   Constructor without parameters
    Date f(1,5,2030);

    //With the constructor with default values you can declare values as Date(12) [just day], Date(12,25) [day and month, can't skip to year]
    //If parameters are wrong, object isn't created
        //if(day<1){day=d;} if day is wrong, the whole object isn't created
        //You can "throw exception();", after using "try{}" then catch(...){}
            //If try fails, it jumps to catch
            //Can do if(condition){}else{throw exception() or throw 0; throw 1;}
            /*
                Date::Date(int d,int m, int y){
                    if(d>=1 && d <=31)
                        day=d;
                    else
                        //throw exception();
                        throw 0;
                    if(m>=1 && m <=12)
                        month=m;
                    else
                        throw 1;
                    if(y>=1900 && y<=3200)
                        year=y;
                    else
                        throw 2;

                then, in catch it can be:
                catch(Error error){
                    if(error==ERR_ID){
                        cout<<"Wrong day"<<endl;
                    }
                    else if(error==1)
                        cout<<"Wrong month"<<endl;
                    else
                        cout<<"Wrong year"<<endl;
                }
                }
            */

    return 0;
}