#ifndef _CLIENTE_H_
#define _CLIENTE_H_

#include <iostream>

using namespace std;

class Cliente{
  private:
    string nombre;
    string direccion;
    string telefono;
  public:
    Cliente(string nom,string dir,string tel);
    string getNombre() const { return nombre; }
    string getTelefono() const { return telefono; }
    string getDireccion() const { return direccion; }
    void setNombre(string nombre) { this->nombre=nombre; } 
    void setDireccion(string direccion) { this->direccion=direccion; }
    void setTelefono(string telefono) { this->telefono=telefono; }
};

#endif
