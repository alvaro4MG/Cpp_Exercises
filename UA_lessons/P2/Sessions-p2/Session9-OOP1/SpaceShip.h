#ifndef _SPACESHIP_
#define _SPACESHIP_

#include<iostream>

using namespace std;

class SpaceShip{
    private:
        int maxSpeed;
        string name;
    public:
        SpaceShip(int ms,string nm);
        ~SpaceShip();               //destructor
        int trip(int distance);
        string getName() const;
        void setName(string n);
};