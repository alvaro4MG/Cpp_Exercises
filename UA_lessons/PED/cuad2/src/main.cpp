#include<iostream>

#include "tabbporo.h"

using namespace std;

int main(){

    /*char *color=new char[8];
    strcpy(color,"porrillo");
    TPoro porrillo(3,4,5.4,color);
    TPoro sinColor(3,4,5.3);
    TPoro copia(sinColor);
    TPoro porrillo2(3,4,4.4,color);
    TPoro sinColor2(3,4,6.3);
    TPoro copia2(3,4,4.3);
    TPoro copia3(3,4,3.3);
    TPoro vacio;
    TVectorPoro vector(3);


    vector[1]=porrillo;         //A partir de uno porque esto es para el usuario y ya se maneja a partir de 1
    vector[2]=sinColor;
    vector[3]=vacio;

    //cout << vector << endl;
    */

   TABBPoro a;

    TPoro p1(1,2,10,(char *) "rojo");
    TPoro p2(1,2,20,(char *) "rojo");
    TPoro p3(1,2,30,(char *) "rojo");
    TPoro p4(1,2,40,(char *) "rojo");
    TPoro p5(1,2,50,(char *) "rojo");
    TPoro p6(1,2,60,(char *) "rojo");
    TPoro p7(1,2,70,(char *) "rojo");
    TPoro p8(1,2,80,(char *) "rojo");
    TPoro p35(1,2,35,(char *) "rojo");
    TPoro p55(1,2,55,(char *) "rojo");

    /*a.Insertar(p1);
    a.Insertar(p2);
    a.Insertar(p3);
    a.Insertar(p4);
    a.Insertar(p5);
    a.Insertar(p6);
    a.Insertar(p7);*/

    //TABBPoro b(a);

    /*if(!a.Borrar(p1))
        cout << "Error NO BORRADO" << endl;

    //cout << a.Inorden() << endl;

    if(!a.Borrar(p5))
        cout << "Error NO BORRADO" << endl;


    if(!a.Borrar(p2))
        cout << "Error NO BORRADO" << endl;

    if(!a.Borrar(p4))
        cout << "Error NO BORRADO" << endl;

    a.Insertar(p8);

    cout << a.Inorden() << endl;
    cout << b.Inorden() << endl;*/

    //a.Insertar(p);
    a.Insertar(p6);
    a.Insertar(p7);
    a.Insertar(p2);
    a.Insertar(p1);
    a.Insertar(p5);
    a.Insertar(p3);
    a.Insertar(p4);
    a.Insertar(p55);
    a.Insertar(p35);

    if(!a.Borrar(p5))
        cout << "Error NO BORRADO" << endl;

    cout << a.Preorden() << endl;
    cout << a.Inorden() << endl;




    return 0;
}