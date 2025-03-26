#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#define ADDER_PIPE "adder_pipe"

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
        // Verileri okuma
        read_fd = open(ADDER_PIPE, O_RDONLY);
        if (read_fd == -1) {
            perror("Failed to open adder pipe for reading");
            break;
        }
        read(read_fd, numbers, sizeof(numbers[0]) * 2);
        close(read_fd);

        // İşlem yapma
        sprintf(result, "%.2lf", numbers[0] + numbers[1]);

        // Sonucu yazma
        write_fd = open(ADDER_PIPE, O_WRONLY);
        if (write_fd == -1) {
            perror("Failed to open adder pipe for writing");
            break;
        }
        write(write_fd, result, sizeof(result));
        close(write_fd);

        // Sonucu kaydetmek için saver programını çağırma
        call_saver(result);
    }

    return 0;
}

