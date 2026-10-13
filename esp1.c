#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

int main() {
    int fd[2];
    int sommap= 0;
    int sommad=0;
    int numeri[10]={2,14,26,38,32,41,42,47,65,82};
    if(pipe(fd) == -1){
        fprintf(stderr, "Error pipe");
        exit(-1);
    }
    pid_t ritorno = fork();
    if (ritorno==-1){
        perror("Error fork");
        exit(-2);
    }
    if (!ritorno) {
        close(fd[0]);
        for(int i=0;i<10;i++) {
            if (numeri[i]%2==0)
                sommap+=numeri[i];
        }
        write(fd[1], &sommap, sizeof(sommap));
        close(fd[1]);
        exit(0);

    }
    for(int i=0;i<10;i++) {
        if (numeri[i]%2==!0)
            sommad+=numeri[i];
    }
    wait(NULL);

    int r = read(fd[0], &sommap, sizeof(&sommap));

    printf("Numeri pari %d\n",sommap);
    close(fd[0]);
    printf("Numeri dispari %d\n",sommad);
    printf("Numeri tutti %d\n",sommap+sommad);
}