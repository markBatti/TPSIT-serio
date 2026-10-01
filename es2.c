#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
int main(void) {
    pid_t ritorno1 = fork();
    pid_t ritorno2 = fork();
    pid_t ritorno3 = fork();
    if (ritorno1 == -1) {
        perror("Errore nel fork");
        exit(-1);
    }
    if (!ritorno1) {
        sleep (1);
        fprintf(stdout, "Sono il figlio\n");
        exit(0);
    }
    if (ritorno2 == -1) {
        perror("Errore nel fork");
        exit(-1);
    }
    if (!ritorno2) {
        sleep (1);
        fprintf(stdout, "Sono il figlio\n");
        exit(0);
    }
    if (ritorno3 == -1) {
        perror("Errore nel fork");
        exit(-1);
    }
    if (!ritorno3) {
        sleep (1);
        fprintf(stdout, "Sono il figlio\n");
        exit(0);
    }
    printf("Sono il padre\n");
    wait(NULL);
    return 0;
}