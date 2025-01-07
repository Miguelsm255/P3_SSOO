#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define N_COCHES 8

// Tipo de datos que representa un coche
typedef struct {
    int id;
    char *cadena;
} coche_t;

// Array de datos de tipo coche_t
coche_t Coches[N_COCHES];

volatile int clasificacionFinal[N_COCHES];
volatile int finalCarrera = 0;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

// Funcion ejecutada por los hilos
void *funcion_coche(coche_t *pcoche)
{
    int aleatorio;
    unsigned int semilla = (pcoche->id) + pthread_self(); // semilla generacion num. aleatorios

    printf("Salida de %s %d\n", pcoche->cadena, pcoche->id+1);
    
    fflush (stdout);

    // generar numero aleatorios con funcion re-entrante rand_r()    
    aleatorio = rand_r(&semilla) % 10;

    sleep(aleatorio);
 
    printf("Llegada de %s %d\n", pcoche->cadena, pcoche->id+1);

    /* CODIGO 4 */

    // Bloqueo el mutex
    if (pthread_mutex_lock(&mutex) != 0) {
        perror("Error bloqueando mutex");
        exit(EXIT_FAILURE);
    }

    // Guardamos la clasificacion del coche
    clasificacionFinal[finalCarrera] = pcoche->id;
    finalCarrera++;

    // Desbloqueo el mutex
    if (pthread_mutex_unlock(&mutex) != 0) {
        perror("Error desbloqueando mutex");
        exit(EXIT_FAILURE);
    }

    /* CODIGO 2 */    
    pthread_exit(NULL);
}


int main(void)
{
    // Inicializar el mutex
    if (pthread_mutex_init(&mutex, NULL) != 0) {
        perror("Error inicializando mutex");
        exit(EXIT_FAILURE);
    }

    pthread_t hilosCoches[N_COCHES]; // tabla con los identificadores de los hilos
    int i;
    
    printf("Se inicia proceso de creacion de hilos...\n\n");
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
