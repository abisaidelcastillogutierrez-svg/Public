#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(void) {
    pid_t pid = fork();

    if (pid < 0) {
        perror("Error en fork()");
        return 1;
    }

    if (pid == 0) {
        // El hijo termina de inmediato
        printf("Hijo (PID: %d, PPID: %d) finalizando inmediatamente...\n",
               (int) getpid(), (int) getppid());
        exit(0);
    } else {
        // El padre duerme antes de llamar a wait(), dejando al hijo en estado ZOMBIE temporalmente
        printf("Padre (PID: %d) creó al hijo %d.\n", (int) getpid(), (int) pid);
        printf("El hijo estará en estado ZOMBIE (<defunct>) durante 10 segundos.\n");
        printf("Puedes verificarlo en otra terminal con: ps -el | grep Z\n");
        sleep(10);

        // El padre recoge el estado de salida y libera la entrada de la tabla de procesos
        int status;
        wait(&status);
        printf("Padre recolectó el estado del hijo (código: %d). Proceso zombie eliminado.\n",
               WEXITSTATUS(status));
    }
    return 0;
}

