#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

void realizar_trabajo(const char *nombre) {
    const int ITERACIONES = 5;
    for (int i = 1; i <= ITERACIONES; i++) {
        sleep(rand() % 2);
        printf("[%s | PID: %d] Iteración %d\n", nombre, (int) getpid(), i);
    }
}

int main(void) {
    printf("Proceso principal iniciado con PID: %d\n", (int) getpid());

    pid_t pid = fork();

    if (pid < 0) {
        perror("Error al crear el proceso con fork()");
        return 1;
    } else if (pid == 0) {
        // Proceso hijo
        srand(getpid());
        realizar_trabajo("HIJO");
        printf("Hijo (PID %d) finalizado.\n", (int) getpid());
        exit(0);
    } else {
        // Proceso padre
        srand(getpid());
        realizar_trabajo("PADRE");
        wait(NULL);
        printf("Padre (PID %d) confirmó fin del hijo y termina.\n", (int) getpid());
    }

    return 0;
}
