#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

#define FIFO_PATH "/tmp/echo_fifo"

int main() {
    mkfifo(FIFO_PATH, 0666);

    int fd = open(FIFO_PATH, O_RDONLY);
    if (fd == -1) {
        perror("open");
        exit(1);
    }

    char buf[256];
    ssize_t n;
    while ((n = read(fd, buf, sizeof(buf) - 1)) > 0) {
        buf[n] = '\0';
        printf("[SERVER] %s", buf);
    }

    close(fd);
    unlink(FIFO_PATH);
    return 0;
}