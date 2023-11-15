#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>

// Variable compartida por los hilos.
static long shared = 0;

// Semáforo para controlar el acceso a la variable compartida.
static sem_t sem;

// Número de hilos.
enum { THREADS = 4 };

// Macro para manejar errores.
#define errExit(msg) \
do { \
    perror(msg); \
    exit(EXIT_FAILURE); \
} while (0)

// Función ejecutada por cada hilo.
static void *threadFunc(void *arg) {
    long loops = *((long *)arg);

    for (long j = 0; j < loops; j++) {
        // Esperar el semáforo antes de acceder a la variable compartida.
        if (sem_wait(&sem) == -1) 
            errExit("sem_wait");

        shared++;

        // Liberar el semáforo después de actualizar la variable compartida.
        if (sem_post(&sem) == -1) 
            errExit("sem_post");
    }

    return NULL;
}

int main() {
    pthread_t t[THREADS];
    int s;

    // Definir número de iteraciones para cada hilo.
    long nloops = 10000;

    // Inicializar el semáforo.
    if (sem_init(&sem, 0, 1) == -1) 
        errExit("sem_init");

    // Crear los hilos.
    for (int i = 0; i < THREADS; ++i) {
        s = pthread_create(&t[i], NULL, threadFunc, &nloops);
        if (s != 0) 
            errExit("pthread_create");
    }

    // Esperar que los hilos terminen.
    for (int i = 0; i < THREADS; ++i) {
        s = pthread_join(t[i], NULL);
        if (s != 0) 
            errExit("pthread_join");
    }

    // Imprimir el valor final de la variable compartida.
    printf("shared = %ld\n", shared);

    // Finalizar el programa exitosamente.
    exit(EXIT_SUCCESS);
}

// file_name: shared_counter_sem.c
// exec: gcc -o shared_counter_sem shared_counter_sem.c -lpthread && ./shared_counter_sem
