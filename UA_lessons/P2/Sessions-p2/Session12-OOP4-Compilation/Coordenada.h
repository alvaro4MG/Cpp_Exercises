//Start with header file

#include<iostream>

using namespace std;

class Coordenada{
    friend ostream& operator<<(ostream&os, const Coordenada &C);
    private:
        float x;
        float y;
    public:
        Coordenada(float cx=0, float cy=0);     //With default parameters
        Coordenada(const Coordenada &c);        //Copy constructor
        ~Coordenada(){}                         //Destructor written here, no need in the .cc file
        float getX() const { return x; };
        float getY() const { return y; };
        void setX(float cx) { x=cx; };
        void setY(float cy) { y=cy; };

};

//Coordenada f(12,23);
//Coordenada g(f);      //Copy constructor