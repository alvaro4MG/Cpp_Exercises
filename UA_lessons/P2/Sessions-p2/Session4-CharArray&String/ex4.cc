//The string class

#include<iostream>
#include<vector>        //To use string, which is like a complex struct (It is a class, will see it in unit 5)
#include<sstream>           //Tp use stringstream

using namespace std;

const string GREET="hello";

void myFunction (string s1, string &s2);            //We pass it like a value or reference, since we need the &

int main(){
    string s;               //No need to set the size, it will asign the empty string (string s="")
    s="hello";      //Stores 5 characters
    s="hello everybody"; //Stores 15 chars, it adapts to it and you don't have to write \0

    cout<<s<<endl;

    cin>>s;                 //Cin works like char arrays (ignores blanks before it and ends with them)
    getline(cin,s);             //Here is the getline, doesn't limit the characters read since in string class is not necessary, it reads until \n
    getline(cin,s,'.');     //Pass an additional parameter, to stop onñy there

    cout<<"Real: "<<s<<endl;


    //sstream
    stringstream ss("Hello cruel world 666");
    string s2;

    while(ss>>s2){                   //Extract word one by one
        cout<<"Word: "<<s2<<endl;
    }


    return 0;
}