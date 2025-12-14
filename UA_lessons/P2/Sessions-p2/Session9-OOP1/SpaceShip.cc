//SpaceShip.cc (implementation of methods)

#include "SpaceShip.h"

//Constructor
SpaceShip::SpaceShip(int ms,int nm){
    maxSpeed=ms;
    name=nm;
}

SpaceShip::~SpaceShip(){}

int SpaceShip::trip(int distance){
    return distance/maxSpeed;
}

string SpaceShip::getName() const{
    return name;
}

int SpaceShip::getSpeed(){
    return maxSpeed;
}

void SpaceShip::setName(string n){
    name=n;
}