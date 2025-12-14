//Dynamic memory
    //Static memory is when the size of the data is fixed before running the program (like variables, allocated in memory address from EC)
    //Dynamic memory can let size grow or shrink, depending on the needs, using pointers
//Pointers
    //Behaves like a variable, stores memory addresses (points to the data)
    //Declared using *

#include<iostream>

using namespace std;

int main(){
    //int *intPointer;        //Declaration of an integer pointer, could array just by using [], or double wiht **

    int i=3;            //This is stored in a location of the memory (cuadradito int i en 2040 con 3 dentro)
    int *pi;            //Stored in cuadradito int* llamado pi en 4056
    pi=&i;             //& returns the memory address where the variable is stored, so pi will get the location of i (2040)
    *pi=11;            //* allows to get to the content of the pointer, so i changes to 11 from 3

    //Can do directly int *pi=&i; we can also set it as a NULL

    cout<<"  i: "<<i<<endl;
    cout<<" &i: "<<&i<<endl;
    cout<<" pi: "<<pi<<endl;        //pi and &i are the same, since pi stores what &i is, the direction 0x...  
    cout<<"*pi: "<<*pi<<endl;
    cout<<"&pi: "<<&pi<<endl;

    int a=7;
    int *p=&a;
    int **pp=&p;            //Can be read like (int *)*
    cout<<**pp<<endl;       //Can also be read like *(*pp), if we used only one *, it would give the address of *P

    return 0;
}