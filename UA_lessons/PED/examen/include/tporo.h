#ifndef _TPORO_H_
#define _TPORO_H_


#include<iostream>
#include<string.h>

using namespace std;

class TPoro{
    friend ostream& operator<<(ostream &os, const TPoro &poro);
    private:
        int x;
        int y;
        double volumen;
        char* color;
    public:
        TPoro();
        TPoro(int a, int b, double vol);
        TPoro(int a, int b, double vol, char* orig);
        TPoro(const TPoro &orig);
        ~TPoro();
        TPoro& operator=(const TPoro &op2);
        bool operator==(const TPoro &op2);
        bool operator<(const TPoro &op2);
        bool operator>(const TPoro &op2);
        bool operator!=(const TPoro &op2);
        void Posicion(int x, int y);
        void Volumen(double volumen){this->volumen=volumen;}
        void Color(char *color);
        int PosicionX() const {return x;}           //Los setters (y EsVacio()) son métodos constantes porque no modifican al TPoro
        int PosicionY() const {return y;}
        double Volumen() const {return volumen;}
        char * Color() const {return color;}
        bool EsVacio() const;
};


#endif