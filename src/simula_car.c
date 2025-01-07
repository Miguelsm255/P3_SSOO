#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "../include/simula_car.h"

// Array de datos de tipo coche_t
coche_t Coches[N_COCHES];

volatile int clasificacionFinal[N_COCHES];
volatile int finalCarrera = 0;

pthread_mutex_t mutexDatos = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutexInicio = PTHREAD_MUTEX_INITIALIZER;

int main(void)
{
    // Inicializar el mutex para sincronizar la escritura en la clasificación final
    if (pthread_mutex_init(&mutexDatos, NULL) != 0) {
        perror("Error inicializando mutex");
        exit(EXIT_FAILURE);
    }

    // Inicializar el mutex para que los hilos no empiecen hasta que se hayan creado todos
    if (pthread_mutex_init(&mutexInicio, NULL) != 0) {
        perror("Error inicializando mutex");
        exit(EXIT_FAILURE);
    }

    pthread_t hilosCoches[N_COCHES]; // tabla con los identificadores de los hilos
    int i;
    
    printf("Se inicia proceso de creacion de hilos...\n");
    
    // Bloqueamos el mutex para que los hilos no empiecen hasta que se hayan creado todos
    if(pthread_mutex_lock(&mutexInicio) != 0) {
        perror("Error bloqueando mutex");
        exit(EXIT_FAILURE);
    }

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

    // Desbloqueamos el mutex para que los hilos puedan empezar
    if (pthread_mutex_unlock(&mutexInicio) != 0) {
        perror("Error desbloqueando mutex");
        exit(EXIT_FAILURE);
    }

    printf("Proceso de creacion de hilos terminado\n\n");
    printf("SALIDA DE COCHES\n");
     
    
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

    //Destruyo los mutex
    pthread_mutex_destroy(&mutexDatos);
    pthread_mutex_destroy(&mutexInicio);
    
    /* CODIGO 5 */        

    printf("CLASIFICACION FINAL:\n");
    for (i=0; i<N_COCHES; i++)
    {
        printf( "%dº: Coche %d\n", i+1, clasificacionFinal[i]+1);
    }    

    return 0;
}
