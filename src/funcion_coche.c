#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "../include/simula_car.h"

void *funcion_coche(coche_t *pcoche) {

    // Bloqueamos el mutex para que los hilos no empiecen hasta que se hayan creado todos
    if (pthread_mutex_lock(&mutexInicio) != 0) {
        perror("Error bloqueando mutex");
        exit(EXIT_FAILURE);
    }

    // Desbloqueamos el mutex para que los demás hilos también puedan empezar
    if (pthread_mutex_unlock(&mutexInicio) != 0) {
        perror("Error desbloqueando mutex");
        exit(EXIT_FAILURE);
    }

    int aleatorio;
    unsigned int semilla = (pcoche->id) + pthread_self(); // semilla generacion num. aleatorios

    printf("Salida de %s %d\n", pcoche->cadena, pcoche->id + 1);
    fflush(stdout);

    aleatorio = rand_r(&semilla) % 10;
    sleep(aleatorio);

    printf("Llegada de %s %d\n", pcoche->cadena, pcoche->id + 1);

    // Bloqueamos el mutex para que solo este hilo pueda escribir en la clasificación final
    if (pthread_mutex_lock(&mutexDatos) != 0) {
        perror("Error bloqueando mutex");
        exit(EXIT_FAILURE);
    }

    clasificacionFinal[finalCarrera] = pcoche->id;
    finalCarrera++;

    // Desbloqueamos el mutex para que los demás hilos puedan escribir en la clasificación final
    if (pthread_mutex_unlock(&mutexDatos) != 0) {
        perror("Error desbloqueando mutex");
        exit(EXIT_FAILURE);
    }

    pthread_exit(NULL);
}