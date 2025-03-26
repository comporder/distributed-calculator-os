#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <signal.h>
#include <fcntl.h>

#define ADDER_PIPE "adder_pipe"
#define SUBTRACTOR_PIPE "subtractor_pipe"
#define MULTIPLIER_PIPE "multiplier_pipe"
#define DIVIDER_PIPE "divider_pipe"

void calculate(int choice) {
    double numbers[2];
    char result[80];
    int pipe_fd;
    
    // Kullanıcıdan iki sayıyı alıyoruz
    printf("Enter the first number: ");
    scanf("%lf", &numbers[0]);
    
    printf("Enter the second number: ");
    scanf("%lf", &numbers[1]);

    switch (choice) {
        case 1: // Addition
            pipe_fd = open(ADDER_PIPE, O_WRONLY);
            write(pipe_fd, numbers, sizeof(numbers[1])*2);
            close(pipe_fd);

            pipe_fd = open(ADDER_PIPE, O_RDONLY);
            read(pipe_fd, result, sizeof(result));
            printf("Result: %s\n", result);
            close(pipe_fd);
            break;

        case 2: // Subtraction
            pipe_fd = open(SUBTRACTOR_PIPE, O_WRONLY);
            write(pipe_fd, numbers, sizeof(numbers[1])*2);
            close(pipe_fd);

            pipe_fd = open(SUBTRACTOR_PIPE, O_RDONLY);
            read(pipe_fd, result, sizeof(result));
            printf("Result: %s\n", result);
            close(pipe_fd);
            break;

        case 3: // Multiplication
            pipe_fd = open(MULTIPLIER_PIPE, O_WRONLY);
            write(pipe_fd, numbers, sizeof(numbers[1])*2);
            close(pipe_fd);

            pipe_fd = open(MULTIPLIER_PIPE, O_RDONLY);
            read(pipe_fd, result, sizeof(result));
            printf("Result: %s\n", result);
            close(pipe_fd);
            break;

        case 4: // Division
            if (numbers[1] != 0) {
                pipe_fd = open(DIVIDER_PIPE, O_WRONLY);
                write(pipe_fd, numbers, sizeof(numbers[1])*2);
                close(pipe_fd);

                pipe_fd = open(DIVIDER_PIPE, O_RDONLY);
                read(pipe_fd, result, sizeof(result));
                printf("Result: %s\n", result);
                close(pipe_fd);
            } else {
                printf("ERROR: Division by zero!\n");
            }
            break;

        default:
            printf("Invalid choice!\n");
            break;
    }
    
}

int main() {
    mkfifo(ADDER_PIPE, 0666);
    mkfifo(SUBTRACTOR_PIPE, 0666);
    mkfifo(MULTIPLIER_PIPE, 0666);
    mkfifo(DIVIDER_PIPE, 0666);

    int pid1 = fork();
    if (pid1 == 0) {
        execl("./addition", "addition", NULL);
    }

    int pid2 = fork();
    if (pid2 == 0) {
        execl("./subtraction", "subtraction", NULL);
    }

    int pid3 = fork();
    if (pid3 == 0) {
        execl("./multiplication", "multiplication", NULL);
    }

    int pid4 = fork();
    if (pid4 == 0) {
        execl("./division", "division", NULL);
    }

    // Döngü ile kullanıcıdan seçim alınır
    while (1) {
        printf("Calculator\n");
        printf("1 - Addition\n");
        printf("2 - Subtraction\n");
        printf("3 - Multiplication\n");
        printf("4 - Division\n");
        printf("5 - Exit\n");
        printf("Enter your choice: ");
        int choice;
        scanf("%d", &choice);

        if (choice == 5) {
            printf("Exiting calculator.\n");
            break;  // Döngüden çık ve programı bitir
        }

        calculate(choice);  // Seçilen işlemi yap
    }
    
    /* Child ve parent processlerinin ölüp ölmediklerini kontrol etmek adına pid değerlerinin gösterimi
    pid_t parent_pid = getpid();
    char command[50];
    sprintf(command, "pgrep -P %d", parent_pid);
    system(command);
    */
    
    kill(pid1, SIGKILL);
    kill(pid2, SIGKILL);
    kill(pid3, SIGKILL);
    kill(pid4, SIGKILL);    
    
    // Child process'leri bekle
    waitpid(pid1, NULL, 0);
    waitpid(pid2, NULL, 0);
    waitpid(pid3, NULL, 0);
    waitpid(pid4, NULL, 0);
    
    return 0;
}

