#ifndef _COORDENADA_H_
#define _COORDENADA_H_

#include <iostream>

using namespace std;

class Coordenada{
  friend ostream& operator<<(ostream &os,const Coordenada &c);
  private:
    float x;
    float y;
  public:
    Coordenada(float cx=0, float cy=0);
    Coordenada(const Coordenada& c); 
    ~Coordenada() {}
    float getX() const { return x; }
    float getY() const { return y; }
    void setX(float x) { this->x=x; }
    void setY(float y) { this->y=y; }
};

#endif
