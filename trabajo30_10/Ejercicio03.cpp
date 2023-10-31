#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

// Variable compartida 'mails' accesible por todos los hilos.
int mails = 0;

// Mutex para controlar el acceso a la variable compartida 'mails'.
pthread_mutex_t mutex;

// Función que será ejecutada por cada hilo.
void* routine(void *arg) {
    // Obtener el número del hilo de los argumentos.
    int thread_num = *((int *)arg);

    // Cada hilo incrementa la variable 'mails' 10,000,000 de veces.
    for (int i = 0; i < 10000000; i++) {
        // Bloquear el mutex para evitar condiciones de carrera.
        pthread_mutex_lock(&mutex);

        // Incrementar la variable 'mails'.
        mails++;

        // Desbloquear el mutex.
        pthread_mutex_unlock(&mutex);
    }

    // Imprimir un mensaje cuando el hilo haya terminado.
    printf("Hilo %d terminado.\n", thread_num);

    return NULL;
}

int main(int argc, char* argv[]) {
    // Inicializar el mutex.
    pthread_mutex_init(&mutex, NULL);

    // Array para almacenar los identificadores de los 10 hilos.
    pthread_t threads[10];
    
    // Array para almacenar los números de los 10 hilos.
    int thread_nums[10];

    // Crear los 10 hilos.
    for (int i = 0; i < 10; i++) {
        // Asignar el número del hilo.
        thread_nums[i] = i + 1;

        // Crear el hilo y pasarle el número como argumento.
        if (pthread_create(&threads[i], NULL, &routine, (void *)&thread_nums[i]) != 0) {
            // Si falla la creación del hilo, terminar el programa.
            return i + 1;
        }
    }

    // Esperar a que los 10 hilos terminen.
    for (int i = 0; i < 10; i++) {
        if (pthread_join(threads[i], NULL) != 0) {
            // Si falla la unión del hilo, terminar el programa.
            return i + 11;
        }
    }

    // Destruir el mutex.
    pthread_mutex_destroy(&mutex);

    // Imprimir el valor final de la variable 'mails'.
    printf("Numero de mails: %d\n", mails);

    return 0;
}

// nombre archivo: Ejercicio03.cpp
// ejecucion: g++ -o Ejercicio03 Ejercicio03.cpp -lpthread