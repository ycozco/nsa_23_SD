#include <stdio.h>
#include <pthread.h>

// Cada thread cuenta TIMES_TO_COUNT veces
#define TIMES_TO_COUNT 21000
#define NC "\e[0m"
#define YELLOW "\e[33m"
#define BYELLOW "\e[1;33m"
#define RED "\e[31m"
#define GREEN "\e[32m"

// Esta estructura contiene el recuento así como el mutex
// eso protegerá el acceso a la variable.
typedef struct s_counter
{
    pthread_mutex_t count_mutex;
    unsigned int count;
} t_counter;

void *thread_routine(void *data)
{
    // Cada thread empieza aqui
    pthread_t tid;
    t_counter *counter; // puntero a la estructura en main
    unsigned int i;
    tid = pthread_self();
    counter = (t_counter *)data;

    // Imprime el recuento antes de que este hilo comience a iterar.
    // Para leer el valor de count, bloqueamos el mutex:
    pthread_mutex_lock(&counter->count_mutex);
    printf("%sThread [%ld]: contador del thread empieza = %u.%s\n",
           YELLOW, tid, counter->count, NC);
    pthread_mutex_unlock(&counter->count_mutex);

    i = 0;
    while (i < TIMES_TO_COUNT)
    {
        // Iterar TIMES_TO_COUNT veces
        // Incrementa el contador en cada iteración
        // Bloquear el mutex mientras dure el incremento
        pthread_mutex_lock(&counter->count_mutex);
        counter->count++;
        pthread_mutex_unlock(&counter->count_mutex);
        i++;
    }

    // Imprime el recuento final cuando este hilo termina su
    // cuenta propia, sin olvidar bloquear el mutex:
    pthread_mutex_lock(&counter->count_mutex);
    printf("%sThread [%ld]: Contador final = %u.%s\n",
           BYELLOW, tid, counter->count, NC);
    pthread_mutex_unlock(&counter->count_mutex);
    return (NULL); // Thread termine ici.
}

int main(void)
{
    pthread_t tid1;
    pthread_t tid2;

    // Esta estructura contiene el contador total del thread
    t_counter counter;

    // Aquí solo hay un hilo (hilo principal), por lo que podemos hacerlo de forma segura
    // inicializa el recuento sin utilizar el mutex.
    counter.count = 0;

    // Inicializa el mutex :
    pthread_mutex_init(&counter.count_mutex, NULL);

    // Dado que cada hilo cuenta TIMES_TO_COUNT veces y eso
    // tenemos 2 hilos, esperamos que el recuento final sea
    // 2 * VECES_PARA_CONTAR:
    printf("Main: el contador esperado es %s%u%s\n", GREEN,
           2 * TIMES_TO_COUNT, NC);

    // Creación del Thread:
    pthread_create(&tid1, NULL, thread_routine, &counter);
    printf("Main: Creando el primer thread [%ld]\n", tid1);

    pthread_create(&tid2, NULL, thread_routine, &counter);
    printf("Main: Creando el segundo thread [%ld]\n", tid2);

    // Thread adicionado:
    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);

    printf("Main: adiciona el primer thread [%ld]\n", tid1);
    printf("Main: adiciona el segundo thread [%ld]\n", tid2);

    // Contador final de la evaluación:
    // (Aquí podemos leer el conteo sin preocuparnos
    // el mutex porque todos los hilos se han unido y
    // no puede haber carrera de datos entre hilos)
    if (counter.count != (2 * TIMES_TO_COUNT))
        printf("%sMain: ERROR ! Total contador es %u%s\n",
               RED, counter.count, NC);
    else
        printf("%sMain: OK. Total contador es %u%s\n",
               GREEN, counter.count, NC);

    // Destruye el mutex al final del programa:
    pthread_mutex_destroy(&counter.count_mutex);
    return (0);
}

// nombre archivo: Ejercicio02.cpp
// ejecutar: g++ -o Ejercicio02 Ejercicio02.cpp -lpthread