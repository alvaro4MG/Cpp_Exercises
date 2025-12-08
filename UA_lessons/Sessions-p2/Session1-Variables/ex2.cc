#include<iostream>

using namespace std;

const int Global=10;    //We can use global constants since it cant be changed, better than local constants

int IAmGlobal=10;       //It is a global variable,accesible from any part of the function, but it may be changed and give problems (FORBIDDEN IN PROGRAMMING2)

int main(){
    int a=2;
    //int a=10              cant declare a variable twice,cant stand ambiguity
    //int b=017             will consider it as a 15 in octal, 0 isnt ignored

    if(a==2){
        bool a=true;        //This doesnt give problems, mo ambiguity, in this block it will be true, just between this {}, then it's end of the scope
    }


    cout<<a<<endl;          //Here will show the real a=2, since it's out of the block


    return 0;
}