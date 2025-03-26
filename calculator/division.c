#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#define DIVIDER_PIPE "divider_pipe"

void call_saver(const char *result) {
    // saver programını çalıştır
    if (fork() == 0) {
        execl("./saver", "saver", result, (char *)NULL);
        perror("execl failed");
        exit(1);  // Eğer execl başarısız olursa, child process'ini sonlandır
    }
}

int main() {
    double numbers[2];
    char result[80];
    int read_fd;
    int write_fd;

    while (1) {
        read_fd = open(DIVIDER_PIPE, O_RDONLY);
        if (read_fd == -1) {
            perror("Failed to open division pipe for reading");
            break;
        }
        read(read_fd, numbers, sizeof(numbers[1])*2);
        close(read_fd);

        if (numbers[1] != 0) {
            sprintf(result, "%.2lf", numbers[0] / numbers[1]);
        } else {
            sprintf(result, "ERROR: Division by zero");
        }

        write_fd = open(DIVIDER_PIPE, O_WRONLY);
        if (read_fd == -1) {
            perror("Failed to open division pipe for writing");
            break;
        }
        write(write_fd, result, sizeof(result));
        close(write_fd);

        // Call saver to save the result
        call_saver(result);
    }

    return 0;
}

