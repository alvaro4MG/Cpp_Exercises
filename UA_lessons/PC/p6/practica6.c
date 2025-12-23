/*************************************************************************/
/*      gcc -o practica6 practica6.c -lpthread   */
/*************************************************************************/
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define MISIONEROS 5
#define NUM_CANIBALES 5
#define NUM_COCINEROS 1

//Variables globales
int olla;


// Semaforos generales
sem_t espera;
sem_t coci;
sem_t olla_mutex;


// Funciones cocinero-caníbal
void *cocinero(void *arg1) {
    int id = *(int *)arg1;

    while(1){
        //retardo aleatorio
        sleep((rand() % 3));

        sem_wait(&coci);

        olla = MISIONEROS;
        if(NUM_COCINEROS > 1){
            printf("El cocinero %d ha cocinado\n", id);
        }else{
            printf("El cocinero ha cocinado\n");
        }

        sem_post(&espera);
    }
    pthread_exit( NULL );
}

void *canibal(void *arg2) {
    int id = *(int *)arg2;

    while(1){
        //retardo aleatorio
        sleep((rand() % 5));
        
        sem_wait(&olla_mutex);

        if(olla < 1){
            sem_post(&coci);
            sem_wait(&espera);
        }
        olla--;
        printf("El canibal %d ha comido\n", id);

        sem_post(&olla_mutex);
    }
    pthread_exit( NULL );
}


// Funcion principal
int main() {
    pthread_t canibales[NUM_CANIBALES], cocineros[NUM_COCINEROS];
    unsigned i;
    int id[NUM_CANIBALES]={0,1,2,3,4};
    olla = MISIONEROS;
    
    srand((unsigned int)time(NULL));

    // Inicializacion de semaforos
    sem_init(&coci, 0, 0);
    sem_init(&espera, 0, 0);
    sem_init(&olla_mutex, 0, 1);


    // Se crean los hilos
    for(i = 0 ; i < NUM_CANIBALES ; i++){
        if(i < NUM_COCINEROS){
            pthread_create(&cocineros[i], NULL, cocinero, &id[i]);
        }
        pthread_create(&canibales[i], NULL, canibal, &id[i]);
    }
    

    // Se espera a que los hilos terminen
    for(i = 0 ; i < NUM_CANIBALES ; i++){
        if(i < NUM_COCINEROS){
            pthread_join(cocineros[i], NULL);
        }
        pthread_join(canibales[i], NULL);
    }

    
    return 0;
}