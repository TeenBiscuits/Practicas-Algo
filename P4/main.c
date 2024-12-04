// Creado por Pablo P. Pablo M. Maite G.

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <stdbool.h>
#include <fcntl.h>
#include <unistd.h>

#include "monticulos.h"

void ordenarPorMonticulos(int v[], int n);

void inicializarVectorAleatorio(int v[], int n);

void print_vector(int v[], int n);

void comprobar();

void test(int n, void (*inicializarvector)(int *v, int n));

void tiempos();

double microsegundos();

int main() {
    srand(time(NULL));

    printf("<--- Práctica de Pablos & Maite --->\n");
    printf("<--- ORDENACIÓN POR MONTÍCULOS --->\n");
    comprobar();
    tiempos();
    return 0;
}

void ordenarPorMonticulos(int v[], int n) {
    struct monticulo M;
    iniMonticulo(&M);

    crearMonticulo(&M, v, n);
    for (int i = 0; i < n; i++) {
        v[i] = consultarMenor(&M);
        quitarMenor(&M);
    }
}

void print_vector(int v[], int n) {
    for (int i = 0; i < n; i++)
        printf("%d ", v[i]);
    printf("\n");
}

void inicializarVectorAleatorio(int v[], int n) {
    int i, m = 2 * n + 1;

    for (i = 0; i < n; i++) v[i] = (rand() % m) - n;
}

void inicializarVectorAscendente(int v[], int n) {
    int i;
    for (i = 0; i < n; i++) v[i] = i;
}

void inicializarVectorDescentende(int v[], int n) {
    int i, j;

    for (i = 0, j = n; i < n; i++, j--)
        v[i] = j;
}

void test(int n, void (*inicializarvector)(int *v, int n)) {
    struct monticulo M;
    int vector[n];

    inicializarvector(vector, n);
    printf("Vector a ordenar: ");
    print_vector(vector, n);

    crearMonticulo(&M, vector, n);

    printf("Menor elemento: %d\n", consultarMenor(&M));
    quitarMenor(&M);
    printf("Menor elemento tras eliminar: %d\n", consultarMenor(&M));

    ordenarPorMonticulos(vector, n);
    printf("Vector ordenado: ");
    print_vector(vector, n);
}

void comprobar() {
    int n = 10;
    printf("\n<----------- Comprobación ----------->\n");

    printf("[ Aleatorio ]\n");
    test(n, inicializarVectorAleatorio);
    printf("[ Ascendente ]\n");
    test(n, inicializarVectorAscendente);
    printf("[ Descendente ]\n");
    test(n, inicializarVectorDescentende);
}

void tiempos() {
    printf("\n     [ Tablas de Tiempos ]\n\n");
}

double microsegundos() {
    struct timeval t;
    if (gettimeofday(&t,NULL) < 0) return 0.0;
    return (t.tv_usec + t.tv_sec * 1000000.0);
}
