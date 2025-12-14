//Constant methods
    //They dont modify attributes, and can be used with constant objects
    //Write after the name of the funciton, before '{'
//Friend functions
    //They are not in the class but they can accesss private parts, use 'friend'    {friend void aFriendFunction(int MyClass... )  
    //To overwrite output and input operators
//Input and output overload
    //
    // friend ostream& operator << (ostream)

#include<iostream>
#include "Date13.h"

using namespace std;

int main(){
    Date d(10,20,2040);


    cout<< d.getDay() << endl;

    //cout << d << endl;    //This doesn't work, must overload

    cout << d;      //Once we declared and described ostream in .cc, we are now telling the program what to do

    cin >> d;

    cout << d;

    return 0;
}

/*
    List l;
    Task t;

    cout << t <<t endl;
    cout << l << endl;

    ostream& operator<<(ostream& os, cosnt List &l){
        for (int i=0; i<l.tasks.size();i++){
            cout<< l.tasks[i] << endl;
        }
    }

*/