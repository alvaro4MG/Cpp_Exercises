//Álvaro Martínez García, 48150407-E

#include "tlistaporo.h"

#include<iostream>

using namespace std;

int main(){
    //int a=7, b=3;
    char *color=new char[8];
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
    TListaNodo listaNodo;
    TListaPosicion listaPosicion;
    TListaPoro listaPoro;

    //cout << "Resultado: " << a+b <<endl;
    /*cout << porrillo << endl;
    cout << sinColor << endl;
    cout << vacio <<endl;*/

    vector[1]=porrillo;         //A partir de uno porque esto es para el usuario y ya se maneja a partir de 1
    vector[2]=sinColor;
    vector[3]=vacio;

    //cout << vector << endl;

    listaPoro.Insertar(porrillo);
    listaPoro.Insertar(sinColor);
    listaPoro.Insertar(copia);
    listaPoro.Insertar(copia);
    
    cout << listaPoro << endl;

    TListaPoro b;
    b.Insertar(porrillo2);
    b.Insertar(sinColor2);
    b.Insertar(copia2);
    b.Insertar(copia);
    
    cout << b << endl;

    cout << listaPoro-b <<endl;

    /*b.Insertar(vacio);
    cout << b.Longitud() << endl;
    cout << b << endl;*/

    TPoro copiaBorrar(3,4,10.2);
    b.Insertar(copiaBorrar);
    cout << "Lista sin borrar: " << b <<endl;
    b.Borrar(copiaBorrar);
    cout << b << endl;

    TListaPoro c=b.ExtraerRango(0,18);
    cout << b << endl;
    cout << c << endl;

    TPoro q(2, 2, 2, "verde");
    TListaPoro a;

    a.Insertar(q);
    cout << a << endl;
    q.Color("green");

    a.Borrar(q);
    cout << a << endl;

    TListaNodo sinNada();
    cout << sinNada << endl;
    

    return 0;
}