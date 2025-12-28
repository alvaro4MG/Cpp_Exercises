// Programación 2
// Tema 3 - Ejercicio 6

#include <iostream>
#include <fstream>

using namespace std;

const int KTAMDNI=10;
const int KTAMAPELLIDOS=40;
const int KTAMNOMBRE=20;
const char KFICH[]="alumnos.dat";
const char KERROR[]="ERROR: no se ha podido abrir el fichero";

struct TAlumno{
  char dni[KTAMDNI];
  char apellidos[KTAMAPELLIDOS];
  char nombre[KTAMNOMBRE];
  int grupo;
};

int main(){
  ifstream ficheroEntrada;
  
  ficheroEntrada.open(KFICH,ios::binary);
  if(ficheroEntrada.is_open()){
    TAlumno nuevo;
    // Leemos un registro de fichero de tipo TAlumno    
    while(ficheroEntrada.read((char *)&nuevo,sizeof(TAlumno))){
      if(nuevo.grupo==7){
        cout << nuevo.dni << endl;
      }
    }
    ficheroEntrada.close();
  }
  else{
    cerr << KERROR << " " << KFICH << endl;
  }
}
