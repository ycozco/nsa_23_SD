#include <stdio.h>
#include <pthread.h>

#define TIMES_TO_COUNT 21000  // Número de veces que cada hilo incrementará el contador
#define NC "\e[0m"
#define YELLOW "\e[33m"
#define BYELLOW "\e[1;33m"
#define RED "\e[31m"
#define GREEN "\e[32m"

typedef struct s_counter {
    pthread_mutex_t count_mutex;  // Mutex para sincronizar el acceso al contador
    unsigned int count;  // Variable contador
} t_counter;

void *thread_routine(void *data) {
    pthread_t tid;
    t_counter *counter;
    unsigned int i;
    tid = pthread_self();
    counter = (t_counter *)data;

    // Bloquear el mutex para leer el valor inicial del contador
    pthread_mutex_lock(&counter->count_mutex);
    printf("%sThread [%ld]: contador del thread empieza = %u.%s\n",
           YELLOW, tid, counter->count, NC);
    pthread_mutex_unlock(&counter->count_mutex);

    i = 0;
    while (i < TIMES_TO_COUNT) {
        pthread_mutex_lock(&counter->count_mutex);
        counter->count++;
        pthread_mutex_unlock(&counter->count_mutex);
        i++;
    }

    pthread_mutex_lock(&counter->count_mutex);
    printf("%sThread [%ld]: Contador final = %u.%s\n",
           BYELLOW, tid, counter->count, NC);
    pthread_mutex_unlock(&counter->count_mutex);
    return (NULL);
}

int main(void) {
    pthread_t tid1, tid2, tid3, tid4;  // IDs de los 4 hilos

    t_counter counter;

    counter.count = 0;

    pthread_mutex_init(&counter.count_mutex, NULL);

    // El contador esperado es 4 * TIMES_TO_COUNT
    printf("Main: el contador esperado es %s%u%s\n", GREEN,
           4 * TIMES_TO_COUNT, NC);

    pthread_create(&tid1, NULL, thread_routine, &counter);
    printf("Main: Creando el primer thread [%ld]\n", tid1);

    pthread_create(&tid2, NULL, thread_routine, &counter);
    printf("Main: Creando el segundo thread [%ld]\n", tid2);

    pthread_create(&tid3, NULL, thread_routine, &counter);
    printf("Main: Creando el tercer thread [%ld]\n", tid3);

    pthread_create(&tid4, NULL, thread_routine, &counter);
    printf("Main: Creando el cuarto thread [%ld]\n", tid4);

    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);
    pthread_join(tid3, NULL);
    pthread_join(tid4, NULL);

    printf("Main: adiciona el primer thread [%ld]\n", tid1);
    printf("Main: adiciona el segundo thread [%ld]\n", tid2);
    printf("Main: adiciona el tercer thread [%ld]\n", tid3);
    printf("Main: adiciona el cuarto thread [%ld]\n", tid4);

    if (counter.count != (4 * TIMES_TO_COUNT))
        printf("%sMain: ERROR ! Total contador es %u%s\n",
               RED, counter.count, NC);
    else
        printf("%sMain: OK. Total contador es %u%s\n",
               GREEN, counter.count, NC);

    pthread_mutex_destroy(&counter.count_mutex);
    return (0);
}

// nombre archivo: Ejercicio02.cpp
// ejecutar: g++ -o Ejercicio02 Ejercicio02.cpp -lpthread