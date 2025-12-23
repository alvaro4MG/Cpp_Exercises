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
bool choosing[2] = {false, false};
int number[2] = {0, 0};


void *codigo_del_hilo (void *id){
    int i = *(int *)id;
    int j = (i == 1)? 0 : 1;
    int k;
    int max;
    int iteraciones = 100000000;

    for(k=0; k<iteraciones; k++){
        // protocolo de entrada
        choosing[i] = true;
        max = (number[i] > number[j]) ? number[i] : number[j];
        number[i] = 1 + max;
        choosing[i] = false;

        for(int l = 0; l < 2; l++){
            while(choosing[j]);

            while( (number[j] > 0) && (number[j] < number[i]) ||
                    (number[j] == number[i]) && (j < i) );
        }

        

        // Sección crítica
        I++;
        //printf("En hilo %d, I=%d\n", i,I);
        
        // protocolo salida
        number[i] = 0;
    }
    printf("En hilo %d, I=%d\n", i,I);

    pthread_exit (id);
}

int main(){
    int h;
    pthread_t hilos[2];
    int id[2]={1,2};
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