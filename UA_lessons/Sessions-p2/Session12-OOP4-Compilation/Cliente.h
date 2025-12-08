//Exercise 1

#include<iostream>

using namespace std;

class Cliente{
    private:
        string nombre;
        string direccion;
        string telefono;
    public:
        Client(string nom,string dir,string tel);
        string getNombre() const;
        string getDireccion() const;
        string getTelefono() const;
        void setNombre(string nom);
        void setDireccion();
        void setTelefono();
};