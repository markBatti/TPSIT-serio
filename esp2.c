#include <ctype.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

struct Messaggio{
    int cv;
    char parolaM [100];
};
int main() {
    int fd1[2];
    int fd2[2];
    int cv= 0;
    char parolai [100];
    char parolaM [100];

    printf("SCRIVI!!!! \n");
    scanf("%s",parolai);
    if(pipe(fd1) == -1){
        fprintf(stderr, "Error pipe");
        exit(-1);
    }
    pid_t ritorno = fork();
    if (ritorno==-1){
        perror("Error fork");
        exit(-2);
    }
    if (!ritorno) {
        close(fd1[0]);
        for(int i=0;i<100;i++) {
            if (parolai[i]=='a'||parolai[i]=='e'||parolai[i]=='i'||parolai[i]=='o'||parolai[i]=='u')
                cv++;
            parolaM[i]=toupper(parolai[i]);
        }

        write(fd2[1], Messaggio, sizeof(cv));
        close(fd1[1]);
        exit(0);

    }
    for(int i=0;i<10;i++) {
        if (numeri[i]%2==!0)
            sommad+=numeri[i];
    }
    wait(NULL);

    int r = read(fd1[0], &sommap, sizeof(&sommap));

    printf("Numeri pari %d\n",sommap);
    close(fd1[0]);
    printf("Numeri dispari %d\n",sommad);
    printf("Numeri tutti %d\n",sommap+sommad);
}