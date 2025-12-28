// Programación 2
// Tema 3 - Ejercicio 8

#include <iostream>
#include <fstream>
#include <string.h>

using namespace std;

const int KTAMDNI=10;
const int KTAMAPELLIDOS=40;
const int KTAMNOMBRE=20;
const char KFENTRADA[]="alumnos.txt";
const char KFSALIDA[]="alumnos.dat";
const char KERROR[]="ERROR: no se ha podido abrir el fichero";

// Estructura que almacena la información de cada alumno
struct TAlumno{
  char dni[KTAMDNI];
  char apellidos[KTAMAPELLIDOS];
  char nombre[KTAMNOMBRE];
  int grupo;
};

int main(){
  ifstream ficheroEntrada;
  ofstream ficheroSalida;
  
  ficheroEntrada.open(KFENTRADA);
  if(ficheroEntrada.is_open()){
    ficheroSalida.open(KFSALIDA,ios::binary);
    if(ficheroSalida.is_open()){
      TAlumno nuevo;
      string linea;

      // Leemos los datos de cada alumno, uno por línea, hasta completar el registro
      // Asumimos que no hay registros a medias (todo alumno tiene los cuatro campos especificados)
      while(getline(ficheroEntrada,linea)){
        // Almacenamos el dni
        strncpy(nuevo.dni,linea.c_str(),KTAMDNI-1);
        nuevo.dni[KTAMDNI-1]='\0';
        // Leemos y almacenamos los apellidos
        getline(ficheroEntrada,linea);
        strncpy(nuevo.apellidos,linea.c_str(),KTAMAPELLIDOS-1);
        nuevo.apellidos[KTAMAPELLIDOS-1]='\0';
        // Leemos y almacenamos el nombre        
        getline(ficheroEntrada,linea);
        strncpy(nuevo.nombre,linea.c_str(),KTAMNOMBRE-1);
        nuevo.nombre[KTAMNOMBRE-1]='\0';
        // Leemos y almacenamos el grupo
        ficheroEntrada >> nuevo.grupo;
        ficheroEntrada.get(); // Eliminamos el salto de línea que nos falta por leer
        
        // Guardamos en fichero el nuevo registro leído
        ficheroSalida.write((const char *)&nuevo,sizeof(TAlumno));
      }
      ficheroSalida.close();
    }
    else{
      cerr << KERROR << " " << KFSALIDA << endl;
    }  
    ficheroEntrada.close();
  }
  else{
    cerr << KERROR << " " << KFENTRADA << endl;
  }
}
