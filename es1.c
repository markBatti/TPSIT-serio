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
        printf("f\n");
        for (int i = 1; i <= 5; i++) {
            fprintf(stdout, "%d\n",i);
            sleep (1);
        }
        exit(0);
    }
    wait(NULL);
    printf("p\n");
    for (int i = 1; i <= 5; i++) {
        fprintf(stdout, "%d\n",i+5);
    }
    return 0;
}