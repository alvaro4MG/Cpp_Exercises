/**
   $hilos
   Compilación: cc -o dekker dekker.c -lpthread
   Ejecución: taskset -c 0 ./dekker
**/
#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>


int I = 0;
bool states[2] = {false, false};
int turno = 1;

void *codigo_del_hilo (void *id){
    int i = *(int *)id;
    int j = (i == 1)? 0 : 1;
    int k;
    long constante = 10000000;
    for(k=0; k<constante; k++){
        // protocolo de entrada
        turno = i;
        states[i] = true;
        while(turno != i){
            while(states[j]);
            turno = i;
        }
        

        // Sección crítica
        I++;
        if(k == (constante-1)){
            printf("En hilo %d, I=%d\n", i,I);
        }
        //printf("En hilo %d, I=%d\n", i,I);
        
        // protocolo salida
        states[i] = false;
    }
    pthread_exit (id);
}

int main(){
    int h;
    pthread_t hilos[2];
    int id[2]={0,1};
    int error;
    int *salida;

    for(h=0; h<2; h++){
        error = pthread_create( &hilos[h], NULL, codigo_del_hilo, &id[h]);
        if (error){
            fprintf (stderr, "Error: %d: %s\n", error, strerror (error));
            exit(-1);
        }
    }
    
    for(h =0; h < 2; h++){
        error = pthread_join(hilos[h], (void **)&salida);
        if (error)
            fprintf (stderr, "Error: %d: %s\n", error, strerror (error));
        else
            printf ("Hilo %d terminado\n", *salida);
    }
}