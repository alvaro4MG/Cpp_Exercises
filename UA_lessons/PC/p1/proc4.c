/* PROCESOS */

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define NUM_PROCESOS 3

const unsigned iteraciones = 5;

void codigo_del_proceso(int id, char imprimir){
    int i;

    for(i = 0; i < iteraciones; i++){
        printf("Proceso(id=%d): letra= %c \n", id, imprimir);          //Imprimir A, B y C
    }

    // el id se almacena en los bits 8 al 15 antes de devolverlo al padre
    exit(id);
}

int main(){
    int p;
    int id[NUM_PROCESOS] = {1, 2, 3};
    int pid;
    int salida;

    for (p = 0; p < NUM_PROCESOS; p++){
        pid = fork();
        if (pid == -1){
            perror("Error al crear un proceso: ");
            exit(-1);
        }else if (pid == 0){ // Codigo del hijo
            char imprimir;

            switch(id[p]){
                case 1:
                        imprimir = 'A';
                    break;
                case 2:
                        imprimir = 'B';
                    break;
                case 3:
                        imprimir = 'C';
                    break;
                default:
                    imprimir = 'X';
            }
            codigo_del_proceso(id[p], imprimir);
        }
    }

    // Codigo del padre
    for (p = 0; p < NUM_PROCESOS; p++){
        pid = wait(&salida);
        printf("Proceso(pid=%d) con id = %x terminado y status = %d \n", pid,
                salida >> 8, WEXITSTATUS(salida));
    }
    return 0;
}