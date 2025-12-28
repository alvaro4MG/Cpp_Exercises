#include "Factura.h"

int main(){
  Cliente *c=new Cliente("Agapito Piedralisa", "c/ Rio Seco, 2", "123465789");
  Factura f(c,"18/4/2011");
    
  // Modo alternativo:
  // Cliente c("Agapito Piedralisa", "c/ Rio Seco, 2", "123465789");
  // Factura f(&c, "18/4/2011");

  f.anyadirLinea(1, "Raton USB", 8.43);
  f.anyadirLinea(2, "Memoria RAM 2GB", 21.15);
  f.anyadirLinea(1, "Altavoces", 12.66);
  cout << f << endl;
    
  delete c;
}
