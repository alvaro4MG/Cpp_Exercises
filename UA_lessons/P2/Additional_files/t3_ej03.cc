// Programación 2
// Tema 3 - Ejercicio 3

#include <iostream>
#include <fstream>

using namespace std;

const char KFICH1[]="f1.txt";
const char KFICH2[]="f2.txt";
const char KERROR[]="ERROR: no se ha podido abrir el fichero";

int main(){
  ifstream fichero1,fichero2;
  string linea1,linea2;

  fichero1.open(KFICH1);
  if(fichero1.is_open()){
    fichero2.open(KFICH2);
    if(fichero2.is_open()){
      // Recorre ambos ficheros mientras existan líneas en alguno de los dos
      while((getline(fichero1,linea1) && getline(fichero2,linea2)) || linea1!="" || linea2!=""){
        if(linea1!=linea2){
          if(linea1!=""){
            cout << "< " << linea1 << endl;
          }
          if(linea2!=""){
            cout << "> " << linea2 << endl;
          }
        }        
        // Asignamos cadena vacía para asegurarnos que si "getline()" no lee nada de fichero porque ha llegado al final, el bucle termina
        linea1="";
        linea2="";
      }      
      fichero2.close();
    }
    else{
      cerr << KERROR << " " << KFICH2 << endl;
    }       
    fichero1.close();
  }
  else{
    cerr << KERROR << " " << KFICH1 << endl;
  }
}
