/* PROCESOS */

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define NUM_PROCESOS 2

const unsigned iteraciones = 5;

void codigo_del_proceso(int id, int imprimir){
    int i;

    for(i = 0; i < iteraciones; i++){
        printf("Proceso(id=%d): numero= %d \n", id, imprimir);
    }

    // el id se almacena en los bits 8 al 15 antes de devolverlo al padre
    exit(id);
}

int main(){
    int p;
    int id[NUM_PROCESOS] = {1, 2};
    int pid;
    int salida;

    for (p = 0; p < NUM_PROCESOS; p++){
        pid = fork();
        if (pid == -1){
            perror("Error al crear un proceso: ");
            exit(-1);
        }else if (pid == 0){ // Codigo del hijo
            int imprimir;

            switch(id[p]){
                case 1:
                        imprimir = 1;
                    break;
                case 2:
                        imprimir = 2;
                    break;
                default:
                    imprimir = 0;
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