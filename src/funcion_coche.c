#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "../include/simula_car.h"

void *funcion_coche(coche_t *pcoche)
{
    int aleatorio;
    unsigned int semilla = (pcoche->id) + pthread_self(); // semilla generacion num. aleatorios

    printf("Salida de %s %d\n", pcoche->cadena, pcoche->id + 1);
    fflush(stdout);

    aleatorio = rand_r(&semilla) % 10;
    sleep(aleatorio);

    printf("Llegada de %s %d\n", pcoche->cadena, pcoche->id + 1);

    // Bloqueamos el mutex para que solo este hilo pueda escribir en la clasificación final
    if (pthread_mutex_lock(&mutex) != 0) {
        perror("Error bloqueando mutex");
        exit(EXIT_FAILURE);
    }

    clasificacionFinal[finalCarrera] = pcoche->id;
    finalCarrera++;

    // Desbloqueamos el mutex para que los demás hilos puedan escribir en la clasificación final
    if (pthread_mutex_unlock(&mutex) != 0) {
        perror("Error desbloqueando mutex");
        exit(EXIT_FAILURE);
    }

    pthread_exit(NULL);
}