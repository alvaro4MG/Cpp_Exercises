/*
ADA. 2021-22
Práctica 1.
*/

#include <unistd.h>
#include <iostream>
#include <math.h>
#include <chrono>

using namespace std;
using namespace chrono;

//--------------------------------------------------------------
// Bubble sort basic algorithm
void 
bubbleSort(int * v, size_t size){
int aux;

for (size_t i = 1; i < size; i++)
    for (size_t j = 0; j < size - i; j++)
        if (v[j]>v[j+1]){ /*swap*/
            aux = v[j]; 
            v[j] = v[j+1]; 
            v[j+1] = aux;
        }
}  
//--------------------------------------------------------------                


int
main(void){

//    srand(getpid());
    srand(0);

    cout << "# BubbleSort CPU times in milliseconds:"
        << endl
        << "# Size \t CPU time (ms.)"
        << endl
        << "# ----------------------------"
        << endl;

    for (int exp = 10; exp <= 16; exp++){
        size_t size = size_t( pow(2,exp) );                 //size_t elige el compilador el tipo que quiere (entero sin signo), quicksort maneja números negativos, cuidao
        int* v = new int [size];                            //hace memoria dinámica
        if (!v){
            cerr << "Error, not enough memory!" << endl;
            exit (EXIT_FAILURE);  
        }

        cout << size << "\t\t" << flush;               //dibujamos la gráfica, flush vacía el buffer de inversión y que imprima antes

        for (size_t j = 0; j < size; j++)                   //Aquí da números aleatorios al vector, distintos por el srand del principio
            v[j] = rand(); 

        auto start = clock();                               //Estas para cronometrar, clock() es el número de ciclos de procesador que está el proceso
        bubbleSort(v,size);                                     //+auto es un tipo que se decide en el compilador
        auto end = clock();


        cout << 1000.0 * (end-start) / CLOCKS_PER_SEC  << endl;     //multiplicamos por 1000 por los ms

        for (size_t i = 1; i < size; i++)                           //Comprobación de que ha ido bien                      
            if (v[i] < v[i-1]){ 
                cerr << "Panic, array not sorted! " << i << endl; 
                exit(EXIT_FAILURE);            
            }

        delete[] v;                                                 //libera el bloque de memoria 
    }
}


