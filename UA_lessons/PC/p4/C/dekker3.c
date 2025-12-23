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
bool states[3] = {false, false, false};
int turno = 0;

void *codigo_del_hilo (void *id){
    int i = *(int *)id;
    int j,jj;
    switch(i){
        case 0:
                j = 1;
                jj = 2;
            break;
        case 1:
                j = 2;
                jj = 0;
            break;
        case 2:
                j = 0;
                jj = 1;
            break;
    }
    
    int k;
    for(k=0; k<100; k++){
        // protocolo de entrada
        states[i] = true;
        while(states[j] || states[jj]){
            if(turno == j || turno == jj){
                states[i] = false;
                while(turno != i);

                states[i] = true;
            }
        }
        

        // Sección crítica
        I++;
        printf("En hilo %d, I=%d\n", i,I);
        
        // protocolo salida
        states[i] = false;
        turno = j;
    }
    pthread_exit (id);
}

int main(){
    int h;
    pthread_t hilos[3];
    int id[3]={0,1,2};
    int error;
    int *salida;

    for(h=0; h<3; h++){
        error = pthread_create( &hilos[h], NULL, codigo_del_hilo, &id[h]);
        if (error){
            fprintf (stderr, "Error: %d: %s\n", error, strerror (error));
            exit(-1);
        }
    }
    
    for(h =0; h < 3; h++){
        error = pthread_join(hilos[h], (void **)&salida);
        if (error)
            fprintf (stderr, "Error: %d: %s\n", error, strerror (error));
        else
            printf ("Hilo %d terminado\n", *salida);
    }
}