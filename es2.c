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
        fprintf(stdout, "Sono il figlio con pid %d\n",getpgid(ritorno1));
        sleep (2);
        exit(0);
    }
    if (ritorno2 == -1) {
        perror("Errore nel fork");
        exit(-1);
    }
    if (!ritorno2) {
        fprintf(stdout, "Sono il figlio con pid %d\n",getpgid(ritorno2));
        sleep (2);
        exit(0);
    }
    if (ritorno3 == -1) {
        perror("Errore nel fork");
        exit(-1);
    }
    if (!ritorno3) {
        fprintf(stdout, "Sono il figlio con pid %d\n",getpgid(ritorno3));
        sleep (2);
        exit(0);
    }
    wait(NULL);
    printf("Sono il padre\n");
    return 0;
}