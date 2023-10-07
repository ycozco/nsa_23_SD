#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t pid = fork();

    if (pid == 0) { // Proceso hijo
        printf("Soy el proceso hijo con PID %d\n", getpid());
    } else { // Proceso padre
        printf("Soy el proceso padre esperando a que mi hijo termine\n");
        wait(NULL); // Espera a que el proceso hijo termine
        printf("Mi hijo ha terminado\n");
    }

    return 0;
}
