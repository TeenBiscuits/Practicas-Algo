// Creado por Pablo P. Pablo M. Maite G.

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <stdbool.h>
#include <fcntl.h>
#include <math.h>
#include <unistd.h>

#include "monticulos.h"

void ordenarPorMonticulos(int v[], int n);

void print_vector(int v[], int n);

void inicializarVectorAleatorio(int v[], int n);

void inicializarVectorAscendente(int v[], int n);

void inicializarVectorDescentende(int v[], int n);

void test(int n, void (*inicializarvector)(int *v, int n));

void tiemposInsertar();

void tiemposCrear();

void tiemposOrdenar(void (*inicializarvector)(int *v, int n));

void comprobar();

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
    int i;

    iniMonticulo(&M);

    crearMonticulo(&M, v, n);
    for (i = 0; i < n; i++) {
        v[i] = consultarMenor(&M);
        quitarMenor(&M);
    }
}

void print_vector(int v[], int n) {
    int i;

    for (i = 0; i < n; i++)
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

void tiemposInsertar() {
    int i, j, q, p, n = 1000;
    double inicio = 0, fin = 0, t = 0;
    float x;
    struct monticulo M;

    printf("insertarMontículo(...)\n");
    printf("Insertado n elementos...\n        n        "
        "     t(n)      t(n)/(n*log(n))\n");

    for (i = 0; i < 9; i++, n = n * 2) {
        inicio = microsegundos();
        iniMonticulo(&M);
        for (j = 0; j < n; j++) {
            p = (int) rand() % TAM;
            insertarMonticulo(&M, p);
        }
        fin = microsegundos();
        t = (fin - inicio);

        if (t < 500) {
            inicio = microsegundos();
            for (q = 0; q < 1000; q++) {
                iniMonticulo(&M);
                for (j = 0; j < n; j++) {
                    p = (int) rand() % TAM;
                    insertarMonticulo(&M, p);
                }
            }
            fin = microsegundos();
            t = (fin - inicio) / 1000;
            printf("(*)");
        } else printf("   ");


        x = t / (n * log(n));
        printf("%6d%17.3f%17.6f\n", n, t, x);
    }
    printf("\n");
}

void tiemposCrear() {
    int i, q, n = 1000, v[TAM];;
    double inicio = 0, fin = 0, t = 0;
    float x;
    struct monticulo M;

    printf("crearMonticulo(...)\n");
    printf("Creando montículos de n elementos...\n        n        "
        "     t(n)          t(n)/n\n");

    for (i = 0; i < 9; i++, n = n * 2) {
        inicializarVectorAleatorio(v, n);
        inicio = microsegundos();
        iniMonticulo(&M);
        crearMonticulo(&M, v, n);
        fin = microsegundos();
        t = (fin - inicio);

        if (t < 500) {
            inicio = microsegundos();
            for (q = 0; q < 1000; q++) {
                iniMonticulo(&M);
                crearMonticulo(&M, v, n);
            }
            fin = microsegundos();
            t = (fin - inicio) / 1000;
            printf("(*)");
        } else printf("   ");
        x = t / n;
        printf("%6d%17.3f%17.6f\n", n, t, x);
    }
    printf("\n");
}

void tiemposOrdenar(void (*inicializarvector)(int *v, int n)) {
    int i, q, n = 1000, k = 1000, v[TAM];;
    double inicio = 0, fin = 0, t = 0, t1 = 0, t2 = 0;
    float x, y, z;

    if (inicializarvector == inicializarVectorAleatorio)
        printf("ORDENAR VECTOR ALEATORIO\n");
    if (inicializarvector == inicializarVectorAscendente)
        printf("ORDENAR VECTOR ASCENDENTE\n");
    if (inicializarvector == inicializarVectorDescentende)
        printf("ORDENAR VECTOR DESCENDENTE\n");

    printf("Ordenando n elementos...\n        n             t(n)"
        "      t(n)/log(n)     t(n)/(n*log(n))       t(n)/n^2\n");

    for (i = 0; i < 9; i++, n = n * 2) {
        inicializarvector(v, n);
        inicio = microsegundos();
        ordenarPorMonticulos(v, n);
        fin = microsegundos();
        t = (fin - inicio);

        if (t < 500) {
            inicio = microsegundos();
            for (q = 0; q < k; q++) {
                inicializarvector(v, n);
                ordenarPorMonticulos(v, n);
            }
            fin = microsegundos();
            t1 = fin - inicio;
            inicio = microsegundos();
            for (q = 0; q < k; q++) inicializarvector(v, n);
            fin = microsegundos();
            t2 = fin - inicio;
            t = (t1 - t2) / k;
            printf("(*)");
        } else printf("   ");


        x = t / log(n);
        y = t / (n * log(n));
        z = t / powf(n, 2);
        printf("%6d%17.3f%17.6f%17.6f%18.9f\n", n, t, x, y, z);
    }
    printf("\n");
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
    printf("\n<----------- Tablas de Tiempos ----------->\n\n");

    tiemposInsertar();
    tiemposCrear();

    tiemposOrdenar(inicializarVectorAscendente);
    tiemposOrdenar(inicializarVectorDescentende);
    tiemposOrdenar(inicializarVectorAleatorio);
}

double microsegundos() {
    struct timeval t;
    if (gettimeofday(&t,NULL) < 0) return 0.0;
    return (t.tv_usec + t.tv_sec * 1000000.0);
}
