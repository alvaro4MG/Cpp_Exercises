//UML diagram to describe classes and relationships between classes in an object oriented design

//Accesors
    //Attributes are defined as private, so we access them with getters, setters and is methods (accessors)

#include<iostream>
#include "SpaceShip.h"

using namespace std;

int main(){
    SpaceShip s(500,"Death Star");
    SpaceShip o(200,"Flying Condor");

    s.setName("Pepito");

    cout<<s.getName()<<endl;
    cout<<o.getName()<<endl;



    return 0;
}

//Spaceship.h