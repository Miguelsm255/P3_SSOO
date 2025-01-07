#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "../include/simula_car.h"

// Array de datos de tipo coche_t
coche_t Coches[N_COCHES];

volatile int clasificacionFinal[N_COCHES];
volatile int finalCarrera = 0;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

int main(void)
{
    // Inicializar el mutex
    if (pthread_mutex_init(&mutex, NULL) != 0) {
        perror("Error inicializando mutex");
        exit(EXIT_FAILURE);
    }

    pthread_t hilosCoches[N_COCHES]; // tabla con los identificadores de los hilos
    int i;
    
    printf("Se inicia proceso de creacion de hilos...\n");
    printf("SALIDA DE COCHES\n");

    for (i=0; i<N_COCHES; i++)
    {
        
        /* CODIGO 1 */

        // Inicializamos los datos del coche
        Coches[i].id = i;
        Coches[i].cadena = "Coche";

        // Creamos el hilo del coche
        if (pthread_create(&hilosCoches[i], NULL, (void *(*)(void *))funcion_coche, (void *)&Coches[i]) != 0) {
            perror("Error creando hilo");
            exit(EXIT_FAILURE);
        }
    }

    printf("Proceso de creacion de hilos terminado\n\n");
    
    for (i=0; i<N_COCHES; i++)
    {
        
        /* CODIGO 3 */

        // Esperamos a que termine el hilo del coche
        if (pthread_join(hilosCoches[i], NULL) != 0) {
            perror("Error esperando hilo");
            exit(EXIT_FAILURE);
        }
    }
   
    printf("Todos los coches han LLEGADO A LA META \n");

    //Destruyo el mutex
    pthread_mutex_destroy(&mutex);
    
    /* CODIGO 5 */        

    printf("CLASIFICACION FINAL:\n");
    for (i=0; i<N_COCHES; i++)
    {
        printf( "%dº: Coche %d\n", i+1, clasificacionFinal[i]+1);
    }    

    return 0;
}
