#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <signal.h>
#include <errno.h>

#define FIFO_PATH "/tmp/echo_fifo"

int main() {
    signal(SIGPIPE, SIG_IGN);

    char buf[256];
    printf("Inserisci messaggio (QUIT per uscire): ");
    while (fgets(buf, sizeof(buf), stdin)) {
        int fd = open(FIFO_PATH, O_WRONLY);
        if (fd == -1) {
            perror("open");
            break;
        }

        ssize_t res = write(fd, buf, strlen(buf));
        if (res == -1 && errno == EPIPE) {
            printf("Nessun reader: canale chiuso.\n");
            close(fd);
            break;
        }

        close(fd);

        buf[strcspn(buf, "\n")] = 0;
        if (strcmp(buf, "QUIT") == 0) break;
    }
    return 0;
}