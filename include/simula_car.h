#ifndef SIMULA_CAR_H
#define SIMULA_CAR_H

#include <pthread.h>

#define N_COCHES 8

// Tipo de datos que representa un coche
typedef struct {
    int id;
    char *cadena;
} coche_t;

extern coche_t Coches[N_COCHES];
extern volatile int clasificacionFinal[N_COCHES];
extern volatile int finalCarrera;
extern pthread_mutex_t mutex;

void *funcion_coche(coche_t *pcoche);

#endif // SIMULA_CAR_H