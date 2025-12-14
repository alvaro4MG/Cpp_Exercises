//.cc file

//#include<iostream>
#include "Coordenada.h"

//using namespace std;

Coordenada::Coordenada(float cx,float cy){
    x=cx;
    y=cy;
}

Coordenada::Coordenada(const Coordenada &c){    //Copy constructor
    x=c.x;
    y=c.y;
}

ostream& operator<<(ostream&os, const Coordenada &c){
    os << "(" << c.x << "," << c.y << ")";
    //os << "(" << c.getX() << "," << c.y << ")";

    return os;
}