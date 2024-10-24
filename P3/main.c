#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <fcntl.h>

bool guardaraarchivo(const char *archivo);

int main(void) {
    if (guardaraarchivo("tiempos.txt")) {
        printf("<--- Práctica de Pablos & Maite --->\n");
    }
    else return EXIT_FAILURE;
    return EXIT_SUCCESS;
}

bool guardaraarchivo(const char *archivo) {
    int file = open(archivo, O_WRONLY | O_CREAT, 0644);
    if (file == -1) {
        perror("open failed");
        return false;
    }
    if (dup2(file, 1) == -1) {
        perror("dup2 failed");
        return false;
    }
    return true;
}
