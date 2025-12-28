// Programación 2
// Tema 3 - Ejercicio 5

#include <iostream>
#include <fstream>
#include <cstring> // Para stoi()

using namespace std;

const char KFICH1[]="f1.txt";
const char KFICH2[]="f2.txt";
const char KFICH3[]="f3.txt";
const char KERROR1[]="ERROR: no se ha podido abrir alguno de los ficheros de entrada";
const char KERROR2[]="ERROR: no se ha podido crear el fichero de salida";

// Extraemos el primer número de la cadena
int extraerIndice(string cadena){
  string indice;

  // Recorremos hasta encontrar los primeros ":"  
  for(int i=0;(unsigned)i<cadena.find(":");i++){
    indice+=cadena[i];
  }
  
  return stoi(indice);
}

// Extrae el contenido que hay después de los primeros ":" en ambas cadenas y los combina en una única cadena
string combinarLineas(string linea1,string linea2){
  string combinada=linea1; // La primera cadena se copia completa

  // La segunda cadena se copia a partir de ":"
  for(int i=linea2.find(":");(unsigned)i<linea2.length();i++){
    combinada+=linea2[i];
  }

  return combinada;
}

int main(int argc,char *argv[])
{
  ifstream fichero1,fichero2;
  ofstream fichero3;
  
  fichero1.open(KFICH1);
  fichero2.open(KFICH2);
  // Comprobamos que los dos ficheros de entrada se hayan abierto correctamente
  if(fichero1.is_open() && fichero2.is_open()){
    fichero3.open(KFICH3);
    if(fichero3.is_open()){
      string linea1,linea2;
      getline(fichero1,linea1);
      getline(fichero2,linea2);
      // La lectura acaba cuando hemos llegado al final de alguno de los ficheros      
      while((!fichero1.eof() && !fichero2.eof()) || (linea1!="" && linea2!="")){
        // Extraemos el primer número de la cadena antes de los ":"
        int indice1=extraerIndice(linea1);
        int indice2=extraerIndice(linea2);
        // Si los números coinciden en ambos ficheros, combinamos los valores y guardamos en el fichero de salida
        if(indice1==indice2){
          fichero3 << combinarLineas(linea1,linea2) << endl;
          // Leemos una nueva línea de cada fichero
          linea1="";
          linea2="";
          getline(fichero1,linea1);
          getline(fichero2,linea2);
        }
        // Si el número leído en el primer fichero es mayor que el leído en el segundo, leemos una nueva línea únicamente del segundo fichero
        else if(indice1>indice2){
          linea2="";
          getline(fichero2,linea2);
        }
        // Si el número leído en el primer fichero es menor que el leído en el segundo, leemos una nueva línea únicamente del primer fichero
        else{
          linea1="";
          getline(fichero1,linea1);
        }
      }
      fichero3.close();
    }
    else{
      cerr << KERROR2 << endl;
    }
    fichero1.close();
    fichero2.close();    
  }
  else {
    cerr << KERROR1 << endl;
  }
}
