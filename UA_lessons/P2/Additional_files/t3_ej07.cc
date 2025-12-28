// Programación 2
// Tema 3 - Ejercicio 7

#include <iostream>
#include <fstream>
#include <string.h>

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

// Convierte una cadena a mayúsculas
// También se puede hacer con "toupper" de la librería "cctype"
void convertirMayusculas(char cadena[]){
  for(int i=0;(unsigned)i<strlen(cadena);i++){
    // Sólo convierte si es minúscula
    if(cadena[i]>='a' && cadena[i]<='z'){
      // Para convertir un carácter a mayúsculas sumo la diferencia que hay entre mayúsculas y minúsculas (utilizando para ello la distancia entre 'A' y 'a')
      cadena[i]=cadena[i]+('A'-'a');
    }
  }
}

int main(){
  fstream fichero;
  
  fichero.open(KFICH,ios::in|ios::out|ios::binary);
  if(fichero.is_open()){
    TAlumno nuevo;

    // Posicionamos antes del quinto registro del fichero
    // Asumimos que existen al menos 5 registros, si no fuera así tendríamos que 
    // comprobar la lectura con fail().
    fichero.seekg(4*sizeof(TAlumno),ios::beg);
    // Leemos el registro
    fichero.read((char *)&nuevo,sizeof(TAlumno));
    // Pasamos a mayúsculas los apellidos y el nombre
    convertirMayusculas(nuevo.apellidos);
    convertirMayusculas(nuevo.nombre);
    // Retrocedemos a la posición anterior del fichero para sobreescribir el registro leído
    fichero.seekp(4*sizeof(TAlumno),ios::beg);
    // Escribimos el registro modificado
    fichero.write((const char *)&nuevo,sizeof(TAlumno));
    
    fichero.close();
  }
  else{
    cerr << KERROR << " " << KFICH << endl;
  }
}
