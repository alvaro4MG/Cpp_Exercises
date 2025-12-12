#ifndef _TAVLPORO_H_
#define _TAVLPORO_H_


#include "tvectorporo.h"
#include "tlistaporo.h"     //Para la función nueva
#include<queue>


class TNodoAVL;         //Declaración forward para poder usarlo en TAVLPoro

class TAVLPoro{
    friend class TNodoAVL;
    friend class TListaPoro;
    friend ostream& operator<<(ostream &os, const TAVLPoro &avl);
    private:
        TNodoAVL *raiz;
        void InordenAux(TVectorPoro &recorrido, int &n) const;
        void PreordenAux(TVectorPoro &recorrido, int &n) const;
        void PostordenAux(TVectorPoro &recorrido, int &n) const;
        //Aquí se podría hacer Copia() como {item=orig->item; iz=orig->iz; de=orig->de; }, uno recibe un nodo y otro recibe un árbol
        void Copiar(const TAVLPoro &orig);

        bool InsertarAux(const TPoro &nuevo,bool &crece);
        void EquilibrarIzquierda();
        void EquilibrarIzquierdaBorrar();        
        void EquilibrarDerecha();
        void EquilibrarDerechaBorrar();
        bool BorrarAux(const TPoro &nuevo,bool &crece);
    public:
        TAVLPoro();
        TAVLPoro(const TAVLPoro &orig);
        ~TAVLPoro();
        TAVLPoro& operator=(const TAVLPoro &op2);

        bool operator==(const TAVLPoro &op2) const;
        bool operator!=(const TAVLPoro &op2) const;
        bool EsVacio() const { return raiz==NULL; }
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

        //PRACTICAR EXAMEN
        int* BuscaAVL(const TListaPoro &lista) const;
};

class TNodoAVL{
    friend class TAVLPoro;
    private:
        TPoro item;
        TAVLPoro iz, de;
        int fe;
    public:
        TNodoAVL();
        TNodoAVL(const TNodoAVL &orig);
        ~TNodoAVL();
        TNodoAVL& operator=(const TNodoAVL &op2);
};

#endif
