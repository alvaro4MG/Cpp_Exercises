//string.h, important for practical 2

#include<iostream>
#include<string.h>

using namespace std;

int main(){
    char str[10]="hello";
    char str2[]="hello world";

    cout<<strlen(str)<<endl;            //Gives the number of characters, not including the NULLs or \0, so it gives 5 (=hello)

    strcpy(str,"cool");         //Copies one char array into another, try not to pass the size

    cout<<strcmp(str,str2)<<endl;       //To compare strings, if before in alphabetical order, will get 1 (if afetr, -1; if equals, then it is 0)
    cout<<strcmp(str2,str2)<<endl;          //Get 0

    //You can use cmp and cpy with n characters using strncpy/strncmp, but strncpy doesn't copy \0, we have to give it 
    strncpy(str,"hello, world",5);      //Copy first 5, hello
    str[5]='\0';                            //Then add \0
    cout<<str<<endl;

    return 0;
}