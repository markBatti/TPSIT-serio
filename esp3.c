#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/wait.h>

int main() {
    int fd1[2];
    int fd2[2];

    if (pipe(fd1) == -1) {
        perror("Error pipe1");
        exit(-1);
    }
    if (pipe(fd2) == -1) {
        perror("Error pipe2");
        exit(-1);
    }

    pid_t ritorno1 = fork();
    if (ritorno1 == -1) {
        perror("Error fork 1");
        exit(-2);
    }
    if (!ritorno1) {
        close(fd1[1]);
        close(fd2[0]);

        int num, quadrato;
        while (read(fd1[0], &num, sizeof(num)) > 0) {
            if (num>49) {
                quadrato = num * num;
                write(fd2[1], &quadrato, sizeof(quadrato));
            }
        }
        close(fd1[0]);
        close(fd2[1]);
        exit(0);
    }

    pid_t ritorno2 = fork();
    if (ritorno2 == -1) {
        perror("Error fork 2");
        exit(-2);
    }
    if (!ritorno2) {
        close(fd1[0]);
        close(fd1[1]);
        close(fd2[1]);

        int quadrato;
        int somma = 0;
        int conta = 0;

        while (read(fd2[0], &quadrato, sizeof(quadrato)) > 0) {
            printf("Figlio2 ha ricevuto %d\n", quadrato);
            somma += quadrato;
            conta++;
        }
        close(fd2[0]);

        if (conta > 0)
            printf("Media %.2f\n", (double)somma / conta);
        exit(0);
    }

    close(fd1[0]);
    close(fd2[0]);
    close(fd2[1]);

    srand(time(NULL));
    for (int i = 0; i < 20; i++) {
        int num = rand() % 100 + 1;
        printf("Figlio1 genera %d\n", num);
        write(fd1[1], &num, sizeof(num));
    }
    close(fd1[1]);
    wait(NULL);
    wait(NULL);
}