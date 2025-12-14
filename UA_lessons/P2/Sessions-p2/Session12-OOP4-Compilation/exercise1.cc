//Exercise 1

#include<iostream>
#include "Coordenada.h"

using namespace std;

int main(){
    float cx,cy;

    cout << "x: ";
    cin >> cx;
    cout <<  "y: ";
    cin>>cy;

    Coordenada c(cx,cy);
    cout << c << endl;


    return 0;
}