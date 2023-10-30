#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define NTHREADS 4

int contador = 0;

// Definir un mutex
pthread_mutex_t contador_mutex = PTHREAD_MUTEX_INITIALIZER;

void *hilo(void *arg)
{
    int i;
    i = (int)arg;

    // Bloquear el mutex antes de acceder al recurso compartido
    pthread_mutex_lock(&contador_mutex);

    contador = contador + i; // Acceder y modificar el recurso compartido (contador)

    // Desbloquear el mutex después de acceder al recurso compartido
    pthread_mutex_unlock(&contador_mutex);

    // Imprimir el ID del hilo y el valor actual del contador
    printf("Hilo %u, contador = %u\n", pthread_self(), contador);
    pthread_exit(0); // Finalizar el hilo
}

int main()
{
    int i;
    pthread_t thread[NTHREADS]; // Vector para definir los hilos
    for (i = 0; i < NTHREADS; i++)
    {
        // Crear un hilo y pasar el valor 'i' como argumento
        pthread_create(&thread[i], NULL, hilo, (void *)i);
    }
    
    for (i = 0; i < NTHREADS; i++)
    {
        // Esperar a que todos los hilos terminen su ejecución
        pthread_join(thread[i], NULL);
    }

    // Imprimir el valor final del contador en el hilo principal
    printf("Hilo principal, contador = %d\n", contador);

    // Destruir el mutex
    pthread_mutex_destroy(&contador_mutex);

    pthread_exit(0); // Finalizar el hilo principal
}
// se necesito 1 hilo para sincronizar el acceso a la variable contador
// nombre del archivo: Ejercicio01.cpp
// ejecutar: g++ -o Ejercicio01 Ejercicio01.cpp -lpthread