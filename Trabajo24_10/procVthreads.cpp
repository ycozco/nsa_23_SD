#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
// se define cantidad de hilos y procesos a crearse 
#define NUM 100

void *threadFunction(void *arg) {
    return NULL;
}

int main() {
    pthread_t threads[NUM];
    pid_t processes[NUM];
    clock_t start_time, end_time;
    double time_taken;

    // Creación de 100 hilos y medición del tiempo
    start_time = clock();
    for (int i=0; i<NUM; i++) {
        pthread_create(&threads[i], NULL, threadFunction, NULL);
    }
    for (int i=0; i<NUM; i++) {
        pthread_join(threads[i], NULL);
    }
    end_time = clock();
    time_taken = ((double)(end_time - start_time)) / CLOCKS_PER_SEC; // En segundos
    printf("100 hilos creados y finalizados en %f segundos.\n", time_taken);

    // Creación de 100 procesos y medición del tiempo
    start_time = clock();
    for (int i=0; i<NUM; i++) {
        processes[i] = fork();
        if (processes[i] == 0) {  // Código del proceso hijo
            _exit(0);
        }
    }
    for (int i=0; i<NUM; i++) {
        waitpid(processes[i], NULL, 0);
    }
    end_time = clock();
    time_taken = ((double)(end_time - start_time)) / CLOCKS_PER_SEC; // En segundos
    printf("100 procesos creados y finalizados en %f segundos.\n", time_taken);

    return 0;
}
// file name: procVthreads.cpp
// how to compile : g++ -o procVthreads procVthreads.cpp -lpthread
// how to exec: ./procVthreads