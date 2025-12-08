#include<iostream>
#include<string.h>

using namespace std;

int main(){


    cout<< 'A' +2 <<endl;           //It will make an implicit conversion and change 'A' by its value in ASCII, then add 2 to it

    /*while (3){
        cout<<"ctrl+C"<<endl;           //It will create infintie loop
    }*/

    cout<< (char)('A' + 2) <<endl;          //Explicit conversion, you want to have a char variable, so it will show 'A'+2 in char wich is 'C'

    char cad[]="Hello everyone!";

    for(int i=0;(unsigned)i<strlen(cad);i++){   //If at console you wirte -Wall, it will have warning message, so we write (unsingned), strlen is unsigned but i isnt (it's just warning, in this case doesn't give errors but it's better if we change it)
        cout<<cad[i]<<endl;
    }


    return 0;
}