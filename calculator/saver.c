#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("No result provided to save.\n");
        return 1;
    }

    // Parametreyi al
    const char *result = argv[1];

    // Sonucu kaydetme
    FILE *file = fopen("results.txt", "a");
    if (file == NULL) {
        perror("Error opening file to save result");
        return 1;
    }

    fprintf(file, "%s\n", result);
    fclose(file);

    return 0;
}

