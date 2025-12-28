// Programación 2
// Tema 3 - Ejercicio 1

#include <iostream>
#include <fstream>

using namespace std;

const char KFICHENTRADA[]="fichero.txt";
const char KCADENA[]="Hola";

int main(){
  ifstream ficheroEntrada(KFICHENTRADA);

  if(ficheroEntrada.is_open()){
    string linea;
    while(getline(ficheroEntrada,linea)){
      if(linea.find(KCADENA)!=string::npos){
        cout << linea << endl;
      }
    }
    ficheroEntrada.close();
  }
  else{
    cout << "ERROR: no se ha podido abrir el fichero " << KFICHENTRADA << endl;
  }
}
