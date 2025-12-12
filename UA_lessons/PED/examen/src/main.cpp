#include<iostream>

#include "tavlporo.h"
#include "tlistaporo.h"

using namespace std;

int main(){

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

    /*cout << porrillo << endl;
    cout << sinColor << endl;
    cout << vacio <<endl;*/

    vector[1]=porrillo;         //A partir de uno porque esto es para el usuario y ya se maneja a partir de 1
    vector[2]=sinColor;
    vector[3]=vacio;

    //cout << vector << endl;

    TAVLPoro a,b,c;

    TPoro p1(1,2,10,(char *) "rojo");
    TPoro p2(1,2,20,(char *) "rojo");
    TPoro p3(1,2,30,(char *) "rojo");
    TPoro p4(1,2,40,(char *) "rojo");
    TPoro p5(1,2,50,(char *) "rojo");
    TPoro p6(1,2,60,(char *) "rojo");
    TPoro p7(1,2,70,(char *) "rojo");
    TPoro p8(1,2,80,(char *) "rojo");
    TPoro p9(1,2,90,(char *) "rojo");
    TPoro p10(1,2,100,(char *) "rojo");
    TPoro p11(1,2,110,(char *) "rojo");
    //TPoro p(1,2,0,(char *) "rojo");
    

    if(false){               //Ejemplo video Borrar
        //a.Insertar(p);
        a.Insertar(p5);
        a.Insertar(p3);
        a.Insertar(p8);
        a.Insertar(p2);
        a.Insertar(p4);
        a.Insertar(p7);
        a.Insertar(p10);
        a.Insertar(p1);
        a.Insertar(p6);
        a.Insertar(p9);
        a.Insertar(p11);
        

        if(!a.Borrar(p4))
            cout << "No se ha borrado" << endl;

        cout << "llega" << endl;
        if(!a.Borrar(p8))
            cout << "No se ha borrado" << endl;

        if(!a.Borrar(p6))
            cout << "No se ha borrado" << endl;

        if(!a.Borrar(p5))
            cout << "No se ha borrado" << endl;
        if(!a.Borrar(p2))
            cout << "No se ha borrado" << endl;
        if(!a.Borrar(p1))
            cout << "No se ha borrado" << endl;
        if(!a.Borrar(p7))
            cout << "No se ha borrado" << endl;

        b.Insertar(p10);
        b.Insertar(p3);
        b.Insertar(p11);
        b.Insertar(p9);
        
        cout << "todo ok" << endl;

        cout << a.Inorden() << endl;
        cout << b.Inorden() << endl;

        cout << a.Preorden() << endl;
        cout << b.Preorden() << endl;

    }

    TPoro e1(1,2,1,(char *) "rojo");
    TPoro e3(1,2,3,(char *) "rojo");
    TPoro e5(1,2,5,(char *) "rojo");
    TPoro e6(1,2,6,(char *) "rojo");
    TPoro e7(1,2,7,(char *) "rojo");
    TPoro e8(1,2,8,(char *) "rojo");
    TPoro e10(1,2,10,(char *) "rojo");
    TPoro e25(1,2,25,(char *) "rojo");
    
    a.Insertar(e6);
    a.Insertar(e3);
    a.Insertar(e8);
    a.Insertar(e1);
    a.Insertar(e5);
    a.Insertar(e7);
    a.Insertar(e10);

    //cout << a << endl;
    

    listaPoro.Insertar(e1);
    listaPoro.Insertar(e6);
    listaPoro.Insertar(e8);
    listaPoro.Insertar(e25);
    
    //cout << listaPoro << endl;

    int* enteros= new int[4];

    enteros=a.BuscaAVL(listaPoro);

    for(int i=0;i<4;i++){
        cout << enteros[i] << " ";
    }
    cout << endl;

    return 0;
}