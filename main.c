#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
int main(void) {
    pid_t ritorno = fork();
    if (ritorno == -1) {
        perror("Errore nel fork");
        exit(-1);
    }
    if (!ritorno) {
        sleep (1);
        fprintf(stdout, "Sono il figlio\n");
        exit(0);
    }
    printf("Sono il padre\n");
    wait(NULL);
    return 0;
}