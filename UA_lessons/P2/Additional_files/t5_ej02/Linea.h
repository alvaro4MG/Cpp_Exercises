#ifndef _LINEA_H_
#define _LINEA_H_

#include <iostream>

using namespace std;

class Linea{
  private:
    int cantidad;
    float precio;
    string descripcion;
  public:
    Linea();
    float getSubtotal() const { return cantidad*precio; }
    int getCantidad() const { return cantidad; }
    float getPrecio() const { return precio; }
    string getDescripcion() const { return descripcion; }
    void setCantidad(int cantidad) { this->cantidad=cantidad; }
    void setPrecio(float precio) { this->precio=precio; }
    void setDescripcion(string descripcion) { this->descripcion=descripcion; }
};

#endif
