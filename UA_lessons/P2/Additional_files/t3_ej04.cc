// Programación 2
// Tema 3 - Ejercicio 4

#include <iostream>
#include <fstream>

using namespace std;

const string KERROR1="ERROR: el numero de lineas debe ser mayor que cero";
const string KERROR2="ERROR: no se ha podido abrir el fichero";

// Inserta una nueva línea en el vector
void insertarLinea(string listaLineas[], string linea, int n, int &contador){
  // Si todavía no hemos leído las "n" líneas, añadimos a la lista
  if(contador<n){
    listaLineas[contador]=linea;
    contador++;
  }
  // Si ya hemos leído "n" líneas, desplazamos las líneas y hacemos hueco para una nueva
  else{
    // Hacemos hueco al final de la lista
    for(int i=0;i<n-1;i++){
      listaLineas[i]=listaLineas[i+1];
    }
    // La línea más nueva se introduce al final de la lista
    listaLineas[n-1]=linea;
  }
}

// Mostramos las "n" líneas almacenadas
void mostrarLineas(string listaLineas[],int n){
  // Recorremos la lista para mostrar las líneas almacenadas
  for(int i=0;i<n;i++){
    cout << listaLineas[i] << endl;
  }
}

// Muestra las "n" últimas líneas de "nomFichero"
void finfichero(int n, string nomFichero) {
  ifstream ficheroEntrada(nomFichero.c_str());
    
  if(ficheroEntrada.is_open()){
    int contador=0;
    string listaLineas[n];
    string linea="";
     
    while(getline(ficheroEntrada,linea)){
      // Insertamos la nueva línea en el vector
      insertarLinea(listaLineas,linea,n,contador);
    }
    // "contador" indica cuántas líneas se han almacenado realmente en el vector, de forma que si el número de líneas solicitado es mayor que el número de líneas del fichero, mostramos como máximo el número de líneas total del fichero
    mostrarLineas(listaLineas,contador);
      
    ficheroEntrada.close();
  }
  else{
    cerr << KERROR2 << " " << nomFichero << endl;
  }
}

int main() {
  finfichero(3,"cadenas.txt");
}
