

#include<iostream>
#include<vector>
#include<sstream>

using namespace std;

int main(){
    char str[]="hello";
    string s;
    s=str;      //To copy array to string

    char str2[10];
    string s="hello";
    strcpy(str,s.c_str());      //The inverse from before


    int num=100;
    stringstream ss;
    string s2;

    ss<<num;
    s=ss.str();     //Transform stringstream to string, can also use atoi and atof for numbers

    string s3="100";
    int num2=stoi(s.c_str());

    //Better to use strings, but can't use it always (can't use strings with binary files)

    return 0;
}