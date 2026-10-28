#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

#define FIFO_PATH "/tmp/echo_fifo"

int main() {
    char buf[256];
    if (!fgets(buf, sizeof(buf), stdin)) {
        return 0;
    }

    int fd = open(FIFO_PATH, O_WRONLY);
    if (fd == -1) {
        perror("open");
        exit(1);
    }

    write(fd, buf, strlen(buf));
    close(fd);
    return 0;
}