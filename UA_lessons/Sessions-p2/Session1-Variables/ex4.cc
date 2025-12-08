#include<iostream>

using namespace std;

typedef char tStr[50];          //You dont write the [] all the time, but you could forget it is an array

int main(){
    int i=3;
    int k=i-+;      //Preincrement: k is 4, i is 4

    int j=3;
    int l=j-+;      //Postincrement: l is 3, j is 4
    //int l=j--;    l is 3, j is 2



    return 0;
}