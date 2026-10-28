#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

#define F1 "/tmp/fifo_1_2"
#define F2 "/tmp/fifo_2_1"

int main() {
    mkfifo(F1, 0666);
    mkfifo(F2, 0666);

    int fd_w = open(F1, O_WRONLY);
    int fd_r = open(F2, O_RDONLY);

    char buf[256];
    char recv_buf[256];

    while (1) {
        printf("Tu: ");
        if (!fgets(buf, sizeof(buf), stdin)) break;
        
        write(fd_w, buf, strlen(buf));
        
        buf[strcspn(buf, "\n")] = 0;
        if (strcmp(buf, "EXIT") == 0) break;

        ssize_t n = read(fd_r, recv_buf, sizeof(recv_buf) - 1);
        if (n <= 0) break;
        recv_buf[n] = '\0';
        
        printf("Altro: %s", recv_buf);
        
        char temp[256];
        strcpy(temp, recv_buf);
        temp[strcspn(temp, "\n")] = 0;
        if (strcmp(temp, "EXIT") == 0) break;
    }

    close(fd_w);
    close(fd_r);
    unlink(F1);
    unlink(F2);
    return 0;
}