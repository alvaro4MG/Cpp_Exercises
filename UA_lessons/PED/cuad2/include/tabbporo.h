#ifndef _TABBPORO_H_
#define _TABBPORO_H_


#include "tvectorporo.h"
#include<queue>


class TNodoABB;         //Declaración forward para poder usarlo en TABBPoro

class TABBPoro{
    friend class TNodoABB;
    friend ostream& operator<<(ostream &os, const TABBPoro &abb);
    private:
        TNodoABB *nodo;
        void InordenAux(TVectorPoro &recorrido, int &n) const;
        void PreordenAux(TVectorPoro &recorrido, int &n) const;
        void PostordenAux(TVectorPoro &recorrido, int &n) const;
        //Aquí se podría hacer Copia() como {item=orig->item; iz=orig->iz; de=orig->de; }, uno recibe un nodo y otro recibe un árbol
        void Copiar(const TABBPoro &orig);
    public:
        TABBPoro();
        TABBPoro(const TABBPoro &orig);
        ~TABBPoro();
        TABBPoro& operator=(const TABBPoro &op2);
        bool operator==(const TABBPoro &op2) const;           //Sería const??
        TABBPoro operator+(const TABBPoro &op2);            //Deberían devolver referencia porque lo cambian?
        TABBPoro operator-(const TABBPoro &op2);
        bool EsVacio() const { return nodo==NULL; }
        bool Insertar(const TPoro &nuevo);
        bool Borrar(const TPoro &borrado);
        bool Buscar(const TPoro &buscado) const;
        TPoro Raiz() const;
        int Altura() const;
        int Nodos() const;
        int NodosHoja() const;
        TVectorPoro Inorden() const;
        TVectorPoro Preorden() const;
        TVectorPoro Postorden() const;
        TVectorPoro Niveles() const;
};

class TNodoABB{
    friend class TABBPoro;
    private:
        TPoro item;
        TABBPoro iz, de;
    public:
        TNodoABB();
        TNodoABB(const TNodoABB &orig);
        ~TNodoABB();
        TNodoABB& operator=(const TNodoABB &op2);
};

#endif
