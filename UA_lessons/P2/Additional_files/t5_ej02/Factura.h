#ifndef _FACTURA_H_
#define _FACTURA_H_

#include <vector>
#include "Cliente.h"
#include "Linea.h"

class Factura{
  friend ostream &operator<<(ostream &os, const Factura &f);
  private:
    static int sigId; // Hay que inicializarlo en "Factura.cc". Aquí no se puede al no ser "const"
    string fecha;
    int id;
    Cliente *cliente;
    vector<Linea> lineas;
    static int getSigId();
  public:
    static const int IVA = 18;
    Factura(Cliente* c, string fecha);
    void anyadirLinea(int cant, string desc, float prec);
};

#endif
