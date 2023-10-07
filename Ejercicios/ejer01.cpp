#include <stdio.h>
#include <unistd.h>

int main() {
    pid_t pid;

    printf("Yo soy el bisabuelo con PID %d\n", getpid());
    pid = fork();

    if (pid == 0) { // Hijo
        printf("Yo soy el abuelo con PID %d y mi padre es %d\n", getpid(), getppid());
        pid = fork();

        if (pid == 0) { // Nieto
            printf("Yo soy el padre con PID %d y mi padre es %d\n", getpid(), getppid());
            pid = fork();

            if (pid == 0) { // Bisnieto
                printf("Yo soy el hijo con PID %d y mi padre es %d\n", getpid(), getppid());
            }
        }
    }

    sleep(10); // Para que los procesos no terminen inmediatamente
    return 0;
}
