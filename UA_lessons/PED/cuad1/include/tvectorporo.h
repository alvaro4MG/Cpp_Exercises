#ifndef _TVECTORPORO_H_
#define _TVECTORPORO_H_


#include "tporo.h"


class TVectorPoro{
    friend ostream& operator<<(ostream &os, const TVectorPoro &vector);
    private:
        int dimension;
        TPoro *datos;
        TPoro error;
    public:
        TVectorPoro();
        TVectorPoro(int a);
        TVectorPoro(const TVectorPoro &orig);
        ~TVectorPoro();
        TVectorPoro& operator=(const TVectorPoro &op2);
        bool operator==(const TVectorPoro &op2);
        bool operator!=(const TVectorPoro &op2);
        TPoro& operator[](int pos);
        TPoro operator[](int pos) const;
        int Longitud() const { return dimension; }
        int Cantidad() const;
        bool Redimensionar(int nueva);
};
#endif