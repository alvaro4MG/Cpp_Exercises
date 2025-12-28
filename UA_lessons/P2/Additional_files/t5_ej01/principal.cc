#include <iostream>
#include "Coordenada.h"

using namespace std;

int main(){
  Coordenada c(2,1);
  Coordenada c2(c); // Equivalente a "Coordenada c2=c;"
  Coordenada c3;
  
  cout << c.getX() << "," << c.getY() << endl;
  c3.setX(10); 
  c3.setY(20);
  cout << c3 << endl;
}
