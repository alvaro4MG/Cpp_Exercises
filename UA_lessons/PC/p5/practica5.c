/*************************************************************************/
/*      gcc -o practica5 practica5.c -lpthread   */
/*************************************************************************/
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define NUM_LECTORES 10
#define NUM_ESCRITORES 5

//Variables globales
int libro = -1;
int contadorLectores = 0;

// Semaforos binarios
pthread_mutex_t mx_lock = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t writer_mutex = PTHREAD_MUTEX_INITIALIZER;



//Métodos escritor
void writer_lock(){
    //writer.wait();
    pthread_mutex_lock(&writer_mutex);
}

void writer_unlock(){
    //writer.signal();
    pthread_mutex_unlock(&writer_mutex);
}


//Métodos lector
void reader_lock(){
    //mx.wait();
    pthread_mutex_lock(&mx_lock);

    contadorLectores += 1;
    if(contadorLectores == 1){
        //writer.wait();
        pthread_mutex_lock(&writer_mutex);
    }

    //mx.signal();
    pthread_mutex_unlock(&mx_lock);
}

void reader_unlock(){
    //mx.wait();
    pthread_mutex_lock(&mx_lock);

    contadorLectores -= 1;
    if(contadorLectores == 0){
        //writer.signal();
        pthread_mutex_unlock(&writer_mutex);
    }
    
    //mx.signal();
    pthread_mutex_unlock(&mx_lock);
}


// Funciones escritor-lector
void *escritor(void *arg1) {
    int id = *(int *)arg1;
    int i;

    for (i = 1; i <= NUM_ESCRITORES; i++) {

        //retardo aleatorio
        sleep((rand() % 5 + 1) / 10);

        writer_lock();
        libro = id;
        printf("El escritor %d ha actualizado el recurso\n", id);
        writer_unlock();

    }

    pthread_exit( NULL );
}

void *lector(void *arg2) {
    int id = *(int *)arg2;
    int i, midato;

    for (i = 1; i<= NUM_LECTORES; i++) {

        //retardo aleatorio
        sleep((rand() % 5 + 1) / 10);

        reader_lock();
        printf("El lector %d ha leído un valor de %d\n", id, libro);
        reader_unlock();
    }

    pthread_exit( NULL );
}


// Funcion principal
int main() {
    pthread_t lectores[NUM_LECTORES], escritores[NUM_ESCRITORES];
    unsigned i;
    int id[NUM_LECTORES]={0,1,2,3,4,5,6,7,8,9};

    srand((unsigned int)time(NULL));
    

    // Se crean los hilos
    for(i = 0 ; i < NUM_LECTORES ; i++){
        if(i < NUM_ESCRITORES){
            pthread_create(&escritores[i], NULL, escritor, &id[i]);
        }
        pthread_create(&lectores[i], NULL, lector, &id[i]);
    }
    

    // Se espera a que los hilos terminen
    for(i = 0 ; i < NUM_LECTORES ; i++){
        if(i < NUM_ESCRITORES){
            pthread_join(escritores[i], NULL);
        }
        pthread_join(lectores[i], NULL);
    }


    return 0;
}