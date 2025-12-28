#include "Coordenada.h"

Coordenada::Coordenada(float cx, float cy){ 
  x=cx;
  y=cy;
}

Coordenada::Coordenada(const Coordenada &c){
  x=c.x;
  y=c.y;
}

ostream& operator<< (ostream &os, const Coordenada &c){
  os << c.x << "," << c.y;
  return os;
}
