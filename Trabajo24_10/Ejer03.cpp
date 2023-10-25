// Inclusión de las bibliotecas necesarias
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

// Función que será ejecutada por el hilo creado
void *threadFunction(void *arg) {
    // Imprime el ID del hilo que está ejecutando esta función
    // La función pthread_self() devuelve el ID del hilo que la invoca
    printf("ID del hilo en la función: %lu\n", pthread_self());
    return NULL;  // Termina la ejecución del hilo y devuelve NULL
}

int main() {
    pthread_t thread;  // Declaración de la variable que almacenará el ID del hilo creado

    // Imprime el ID del hilo principal que está ejecutando la función main
    printf("ID del hilo principal (main): %lu\n", pthread_self());

    // Crea un nuevo hilo que ejecutará la función threadFunction
    // Los argumentos son, en orden:
    // - Una referencia al identificador del hilo (para poder referenciarlo después)
    // - Atributos del hilo (NULL significa atributos predeterminados)
    // - La función que el hilo debe ejecutar
    // - Argumentos para pasar a la función (en este caso, ninguno, por lo que es NULL)
    pthread_create(&thread, NULL, threadFunction, NULL);

    // Espera a que el hilo creado termine su ejecución antes de continuar
    // Esto garantiza que la función main no termine antes de que el hilo haya completado su tarea
    pthread_join(thread, NULL);

    return 0;  // Finaliza la ejecución del programa
}

// Afirmacion INCORRECTA , dado que los id de los hilos creados en la funcion y el main son diferentes. 
// file name:  Ejer03.cpp
// how to compile: g++ -o Ejer03 Ejer03.cpp -lpthread
// how to exec: ./Ejer03