/*
 * hilos
 * Compilación: cc -o hilos hilos.c -lpthread
 */

#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <stdint.h>

#define NUM_HILOS 3

struct Parametro{
    char caracter;
    int iteraciones;
    int id;
};


void *codigo_del_hilo(void *parametro){        //debe recibir como parámetro una estructura en al que deben
                                               // ir encapsulados el carácter y n (iteraciones)
    int i;
    struct Parametro *recibido = (struct Parametro *)parametro;
    char caracter = recibido->caracter;
    int iteraciones = recibido->iteraciones;
    int *id = &(recibido->id);
    

    for(i = 0; i < iteraciones; i++)
        printf("Carácter %c, iteración = %d\n", caracter, i);
    
    pthread_exit (id);

}

int main(){
    int h;
    pthread_t hilos[NUM_HILOS];
    int id[NUM_HILOS] = {1, 2, 3};
    int error;
    int *salida;
    struct Parametro parametros[NUM_HILOS];


    for (h = 0; h < NUM_HILOS; h++){
        parametros[h].id = id[h];
        if(h == 0){
            parametros[h].caracter = 'A';
            parametros[h].iteraciones = 50;
        }else{
            parametros[h].caracter = 'A' + h;
            parametros[h].iteraciones = 50 + h * 50;
        }
        
        error = pthread_create( &hilos[h], NULL, codigo_del_hilo, &parametros[h]);
        if (error){
            fprintf (stderr, "Error: %d: %s\n", error, strerror (error));
            exit(-1);
        }
    }

    for (h = 0; h < NUM_HILOS; h++){
        error = pthread_join(hilos[h], (void **)&salida);
        if (error)
            fprintf (stderr, "Error: %d: %s\n", error, strerror (error));
        else{
            printf("Hilo %d terminado\n", *salida);
        }
    }
    return 0;
}