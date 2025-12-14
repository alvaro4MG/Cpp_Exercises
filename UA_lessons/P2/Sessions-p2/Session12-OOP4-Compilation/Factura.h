//

#include<iostream>
#include<vector>
#include "Linea.h"
#include "Cliente.h"

using namespace std;

class Factura{
    friend ostream& operator<<(ostream &os )
    private:
        static int sigId;   //Assign value in factura.cc
        string fecha;
        int id;
        static int getSigId();
        vector<Linea> lineas;   //Composition * .. infinite
        Cliente *cliente;       //Aggregation 1
    public:
        static const int IVA=18;
        Factura(Cliente *c,string fecha);
        void anyadirLinea(int cant,string desc, float prec);
};