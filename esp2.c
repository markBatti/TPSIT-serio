#include <ctype.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

struct Messaggio {
    int cv;
    char parolaM[100];
};

int main() {
    int fd1[2];
    int fd2[2];
    char parolai[100];

    if (pipe(fd1) == -1) {
        perror("Error pipe1");
        exit(-1);
    }
    if (pipe(fd2) == -1) {
        perror("Error pipe2");
        exit(-1);
    }

    pid_t ritorno = fork();
    if (ritorno == -1) {
        perror("Error fork");
        exit(-2);
    }

    if (!ritorno) {
        close(fd1[1]);
        close(fd2[0]);

        char parolaf[100];
        struct Messaggio m;
        m.cv = 0;

        int n = read(fd1[0], parolaf, sizeof(parolaf));
        if (n == -1) {
            perror("Error read figlio");
            exit(-3);
        }

        for (int i = 0; i < n ; i++) {
            m.parolaM[i] = toupper(parolaf[i]);
            if (m.parolaM[i] == 'A' || m.parolaM[i] == 'E' || m.parolaM[i] == 'I' ||
                m.parolaM[i] == 'O' || m.parolaM[i] == 'U')
                m.cv++;
        }

        write(fd2[1], &m, sizeof(m));

        close(fd1[0]);
        close(fd2[1]);
        exit(0);
    }

    close(fd1[0]);
    close(fd2[1]);

    printf("SCRIVI!!!! \n");
    scanf("%s", parolai);

    write(fd1[1], parolai, strlen(parolai) + 1);
    close(fd1[1]);

    struct Messaggio r;
    int n = read(fd2[0], &r, sizeof(r));
    if (n == -1) {
        perror("Error read padre");
        exit(-4);
    }
    close(fd2[0]);

    wait(NULL);

    printf("Maiuscolo %s\n", r.parolaM);
    printf("Numero vocali %d\n", r.cv);
}