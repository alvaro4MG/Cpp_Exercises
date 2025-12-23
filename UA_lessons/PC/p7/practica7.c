/*************************************************************************/
/*      gcc -o practica7 practica7.c -lpthread   */
/*************************************************************************/
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define MAX_CLIENTES 20
#define NUM_CLIENTES 25
#define NUM_SILLAS 3
#define NUM_BARBEROS 3
#define SOFA 4

#define ITERACIONES 2

//Variables globales
int caja;


// Semaforos generales
sem_t max_capacidad;
sem_t sofa;
sem_t silla_barbero;
sem_t cliente_listo;
sem_t terminado;
sem_t dejar_silla_barbero;
sem_t pago;
sem_t recibo;
sem_t coord;

// Funciones barbero-cliente-cajero
void *barbero(void *arg1) {
    int id = *(int *)arg1;

    while(caja < (NUM_CLIENTES * ITERACIONES)){
        sem_wait(&cliente_listo);
        sem_wait(&coord);
        //cortar pelo
        printf("El barbero %d ha afeitado\n", id);
        sem_post(&coord);
        sem_post(&terminado);
        sem_wait(&dejar_silla_barbero);
        sem_post(&silla_barbero);

        //retardo aleatorio
        sleep((rand() % 5) /100);

    }
    //printf("Barbero %d fuera\n", id);
    pthread_exit( NULL );
}

void *cliente(void *arg2) {
    int id = *(int *)arg2;

    for(int i = 0; i < ITERACIONES; i++){
        sem_wait(&max_capacidad);
        //entrar barberia
        printf("El cliente %d ha entrado\n", id);
        sem_wait(&sofa);
        //sentarse sofa
        printf("El cliente %d se ha sentado en el sofá\n", id);
        sem_wait(&silla_barbero);
        //levantarse_sofa
        printf("El cliente %d se ha levantado del sofá\n", id);
        sem_post(&sofa);
        //sentarse silla barbero
        printf("El cliente %d se ha sentado en la silla\n", id);
        sem_post(&cliente_listo);
        sem_wait(&terminado);
        //levantarse silla barbero
        printf("El cliente %d se ha levantado de la silla\n", id);
        sem_post(&dejar_silla_barbero);
        //pagar
        printf("El cliente %d ha pagado\n", id);
        sem_post(&pago);
        sem_wait(&recibo);
        //salir tienda
        printf("El cliente %d ha salido de la tienda\n", id);
        sem_post(&max_capacidad);

    }
    pthread_exit( NULL );
}

void *cajero(void *arg3){

    while(caja < (NUM_CLIENTES * ITERACIONES)){
        sem_wait(&pago);
        sem_wait(&coord);
        //cobrar
        caja++;
        printf("La caja ha cobrado. Total: %d €\n", caja);
        sem_post(&coord);
        sem_post(&recibo);
    }
    //printf("Caja fuera\n");
    pthread_exit( NULL );
}


// Funcion principal
int main() {
    pthread_t clientes[NUM_CLIENTES], barberos[NUM_BARBEROS], cajeros;
    unsigned i;
    int id[NUM_CLIENTES];
    caja = 0;

    for(i = 0; i < NUM_CLIENTES; i++){
        id[i] = i;
    }
    
    srand((unsigned int)time(NULL));

    // Inicializacion de semaforos
    sem_init(&max_capacidad, 0, MAX_CLIENTES);
    sem_init(&sofa, 0, SOFA);
    sem_init(&silla_barbero, 0, NUM_SILLAS);
    sem_init(&cliente_listo, 0, 0);     //no se especifica
    sem_init(&terminado, 0, 0);
    sem_init(&dejar_silla_barbero, 0, 0);
    sem_init(&pago, 0, 0);
    sem_init(&recibo, 0, 0);
    sem_init(&coord, 0, NUM_BARBEROS);


    // Se crean los hilos
    pthread_create(&cajeros, NULL, cajero, NULL);
    for(i = 0 ; i < NUM_CLIENTES ; i++){
        if(i < NUM_BARBEROS){
            pthread_create(&barberos[i], NULL, barbero, &id[i]);
        }
        pthread_create(&clientes[i], NULL, cliente, &id[i]);
        
    }
    

    // Se espera a que los hilos terminen
    for(i = 0 ; i < NUM_CLIENTES ; i++){
        pthread_join(clientes[i], NULL);
    }

    pthread_join(cajeros, NULL);


    if(i < NUM_BARBEROS){
        pthread_join(barberos[i], NULL);    //Para que terminen puedo hacer señales a los semaforos
    }
    printf("Barbería cerrada, vuelvan mañana\n");

    
    return 0;
}