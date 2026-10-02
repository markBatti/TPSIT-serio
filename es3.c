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
        pid_t ritorno1 = fork();
        if (ritorno1 == -1) {
            perror("Errore nel fork");
            exit(-1);
        }
        if (!ritorno1) {
            fprintf(stdout, "Sono il figlio\n");
            exit(0);
        }
        wait(NULL);
        fprintf(stdout, "Sono il padre\n");
        exit(0);
    }
    wait(NULL);
    printf("Sono il nonno\n");
    return 0;
}