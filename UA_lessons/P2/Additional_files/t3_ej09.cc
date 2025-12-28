// Programación 2
// Tema 3 - Ejercicio 9

#include <iostream>
#include <fstream>
#include <string.h>
#include <cstdlib>

using namespace std;

const int KTAMDNI=10;
const int KTAMAPELLIDOS=40;
const int KTAMNOMBRE=20;
const char KFICH[]="alumnos.dat";
const char KERROR[]="ERROR: no se ha podido abrir el fichero";

// Estructura que almacena la información de cada alumno
typedef struct
{
  char dni[KTAMDNI];
  char apellidos[KTAMAPELLIDOS];
  char nombre[KTAMNOMBRE];
  int grupo;
}TAlumno;

int main()
{
  fstream fichero;
  
  fichero.open(KFICH,ios::in|ios::out|ios::binary);
  if(fichero.is_open()){
    TAlumno nuevo;
    
    while(fichero.read((char *)&nuevo,sizeof(TAlumno))){
      // Calculamos el número de dígitos del DNI
      int tam=strlen(nuevo.dni);
      // Almacenamos el último dígito del DNI para asignar el grupo
      // Restamos el caracter '0' para convertir a entero (p.ej. '8' - '0' = 8, '3' - '0' = 3, etc.)
      nuevo.grupo=nuevo.dni[tam-1]-'0';
      // Si el grupo es 0, se le asigna el grupo 10
      if(nuevo.grupo==0) {
        nuevo.grupo=10;
      }
      // Retrocedemos a la posición anterior a la lectura
      fichero.seekp(-1*sizeof(TAlumno),ios::cur);
      // Escribimos el registro modificado
      fichero.write((const char *)&nuevo,sizeof(TAlumno));
    }
    fichero.close();
  }
  // Error de apertura del fichero de entrada
  else{
    cerr << KERROR << " " << KFICH << endl;
  }
}
