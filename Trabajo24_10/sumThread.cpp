#include <stdio.h>
#include <pthread.h>
#include <stdint.h>  // Incluir la cabecera para intptr_t
// intptr_t: es un tipo de dato entero definido en la biblioteca estándar de C (stdint.h) 
//que tiene un tamaño fijo garantizado en todas las plataformas compatibles con C99 o versiones posteriores.
#define SIZE 1000  // Tamaño del arreglo
#define NUM_THREADS 15  // Número de threads

int arr[SIZE] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
int sum[NUM_THREADS] = {0};  // Almacena la suma de los elementos de cada segmento del arreglo

void *partialSum(void *arg) {
    int thread_num = (int)(intptr_t)arg;

    // Determinar los índices de inicio y fin para la suma
    int segment_size = SIZE / NUM_THREADS;
    int start = thread_num * segment_size;
    int end = (thread_num == NUM_THREADS - 1) ? SIZE : start + segment_size;

    // Suma de elementos en el segmento actual
    for (int i = start; i < end; i++) {
        sum[thread_num] += arr[i];
    }
    return NULL;
}

int main() {
    pthread_t threads[NUM_THREADS];

    for (intptr_t i = 0; i < NUM_THREADS; i++) {
        pthread_create(&threads[i], NULL, partialSum, (void *)i);
    }

    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    int total_sum = 0;
    for (int i = 0; i < NUM_THREADS; i++) {
        total_sum += sum[i];
    }

    printf("Suma total de los elementos: %d\n", total_sum);

    return 0;
}
