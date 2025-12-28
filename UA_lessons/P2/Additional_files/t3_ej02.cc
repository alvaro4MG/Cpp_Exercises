// Programación 2
// Tema 3 - Ejercicio 2
#include <iostream>
#include <fstream>

using namespace std;

// Nombres de los ficheros de entrada y salida
const char KFICHENTRADA[]="fichero.txt";
const char KFICHSALIDA[]="FICHERO.txt";

// Convierte un carácter a mayúsculas
// Hace lo mismo que la función "toupper" de la librería "cctype"
char convertirMayusculas(char c){
  char convertido=c;
  if(c>='a' && c<='z') {
    convertido=c+('A'-'a');
  }
  return convertido;
}

int main(){
  ifstream ficheroEntrada;
  ofstream ficheroSalida;

  ficheroEntrada.open(KFICHENTRADA);
  if(ficheroEntrada.is_open()){
    ficheroSalida.open(KFICHSALIDA);
    if(ficheroSalida.is_open()){
      char c;
      // Leemos carácter a carácter de la entrada
      while(ficheroEntrada.get(c)) {
        ficheroSalida << convertirMayusculas(c);
      }      
      ficheroSalida.close();
    }
    else{
      cerr << "ERROR: no se ha podido crear el fichero " << KFICHSALIDA << endl;
    }       
    ficheroEntrada.close();
  }
  else{
    cerr << "ERROR: no se ha podido abrir el fichero " << KFICHENTRADA << endl;
  }
}
