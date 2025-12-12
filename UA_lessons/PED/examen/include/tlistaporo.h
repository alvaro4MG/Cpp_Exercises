#ifndef _TLISTAPORO_H_
#define _TLISTAPORO_H_

#include "tvectorporo.h"


class TListaNodo{
    friend class TListaPosicion;
    friend class TListaPoro;
    friend class TAVLPoro;
    private:
        TPoro e;
        TListaNodo *anterior;
        TListaNodo *siguiente;
    public:
        TListaNodo();
        TListaNodo(const TListaNodo &orig);
        ~TListaNodo();
        TListaNodo& operator=(const TListaNodo &op2);
};

class TListaPosicion{
    friend class TListaNodo;
    friend class TListaPoro;
    friend class TAVLPoro;
    private:
        TListaNodo *pos;
    public:
        TListaPosicion();
        TListaPosicion(const TListaPosicion &orig);
        ~TListaPosicion();
        TListaPosicion& operator=(const TListaPosicion &op2);
        bool operator==(const TListaPosicion &op2) { return (pos==op2.pos); }
        TListaPosicion Anterior();
        TListaPosicion Siguiente();
        bool EsVacia() const { return (pos==NULL); }
};

class TListaPoro{
    friend class TListaNodo;
    friend class TListaPosicion;
    friend class TAVLPoro;
    friend ostream& operator<<(ostream &os, const TListaPoro &lista);

    private:
        TListaNodo *primero;
        TListaNodo *ultimo;
    public:
        TListaPoro();
        TListaPoro(const TListaPoro &orig);
        ~TListaPoro();
        TListaPoro& operator=(const TListaPoro &op2);
        bool operator==(const TListaPoro &op2);
        TListaPoro& operator+(const TListaPoro &op2);
        TListaPoro& operator-(const TListaPoro &op2);
        bool EsVacia() const { return primero==NULL; }
        bool Insertar(const TPoro &nuevo);
        bool Borrar(const TPoro &viejo);
        bool Borrar(const TListaPosicion &posicion);
        TPoro Obtener(const TListaPosicion &posicion) const;
        bool Buscar(const TPoro &buscado) const;
        int Longitud() const;
        TListaPosicion Primera() const;
        TListaPosicion Ultima() const;
        TListaPoro ExtraerRango(int n1, int n2);
};
#endif
