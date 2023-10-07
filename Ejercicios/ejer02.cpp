#include <stdio.h>
#include <unistd.h>

int main() {
    int n;
    printf("Introduce el número de procesos hijos a crear: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        if (fork() == 0) {
            printf("Soy el proceso hijo con PID %d y mi padre es %d\n", getpid(), getppid());
            return 0; // Termina el proceso hijo
        }
    }

    sleep(10); // Para que los procesos no terminen inmediatamente
    return 0;
}
