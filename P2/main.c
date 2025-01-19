// Creado por Pablo P. Pablo M. Maite G.

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <sys/time.h>

#include "ordenar.h"

void imprimir_vector(int v[], int n);

void inicializar_semilla();

void test();

void test_algo(void algoritmo(int *, int), void initvector(int [], int), int n, char *init_type);

int test_orden(int v[], int n);

void tablas(void algoritmo(int [], int));

void creartabla(void initvector(int [], int), void algoritmo(int [], int), char *nombreAlgoritmo, char *tipoVector);

void imprimircabecerat(void algoritmo(int [], int), void initvector(int [], int));

void imprimirresultados(int n, double t, void algoritmo(int [], int), void initvector(int [], int));

double tiempospetit(void initvector(int [], int), void algoritmo(int [], int), int n);

double microsegundos();

int main(void) {
    printf("<--- Práctica de Pablos & Maite --->\n");
    test();
    tablas(ord_ins);
    tablas(ord_rap);
    return 0;
}

void imprimir_vector(int v[], int n) {
    int i;
    printf("[ ");
    for (i = 0; i < n; i++)
        printf("%d ", v[i]);
    printf("]\n");
}


void inicializar_semilla() {
    srand(time(NULL));
}

void test() {
    int size = 20;
    printf("\n--- Iniciando tests de tamaño %d ---\n", size);
    printf("\n--- Test 1 | Ordenación por inserción ---\n");
    test_algo(ord_ins, init_aleatorio, size, "aleatoria");
    test_algo(ord_ins, init_descendente, size, "descendente");
    printf("\n--- Test 2 | Ordenación rápida ---\n");
    test_algo(ord_rap, init_aleatorio, size, "aleatoria");
    test_algo(ord_rap, init_descendente, size, "descendente");
}

void test_algo(void algoritmo(int *, int), void initvector(int [], int), int n, char *init_type) {
    int v[n];
    inicializar_semilla();
    initvector(v, n);

    printf("Ordenación con inicialización %s\n", init_type);
    imprimir_vector(v, n);
    printf("¿Ordenado? %d - Ordenando...\n", test_orden(v, n));
    algoritmo(v, n);
    imprimir_vector(v, n);
    printf("¿Ordenado? %d\n", test_orden(v, n));
}

int test_orden(int v[], int n) {
    int i;
    for (i = 1; i < n; i++)
        if (v[i] < v[i - 1]) return 0;
    return 1;
}

void creartabla(void initvector(int [], int), void algoritmo(int [], int), char *nombreAlgoritmo, char *tipoVector) {
    int m, n;
    double inicio, fin, t;
    int v[32000];

    printf("\n%s con inicialización %s\n", nombreAlgoritmo, tipoVector);
    imprimircabecerat(algoritmo, initvector);

    for (m = 0, n = 500; m < 7; m++, n = 2 * n) {
        initvector(v, n);
        inicio = microsegundos();
        algoritmo(v, n);
        fin = microsegundos();
        t = (fin - inicio);

        if (t < 500) t = tiempospetit(initvector, algoritmo, n);
        else printf("   ");

        imprimirresultados(n, t, algoritmo, initvector);
    }
}

double tiempospetit(void initvector(int [], int), void algoritmo(int [], int), int n) {
    double inicio, fin, taa, tab;
    int k, v[n];

    printf("(*)");
    inicio = microsegundos();
    for (k = 0; k <= 1000; k++) {
        initvector(v, n);
        algoritmo(v, n);
    }
    fin = microsegundos();

    taa = microsegundos();
    for (k = 0; k <= 1000; k++) {
        initvector(v, n);
    }
    tab = microsegundos();

    return ((fin - inicio) - (tab - taa)) / k;
}

void imprimircabecerat(void algoritmo(int [], int), void initvector(int [], int)) {
    if (algoritmo == ord_ins) {
        if (initvector == init_ascendente)
            printf("n                 t(n)"
                "    t(n)/log(n)         t(n)/n     t(n)/n^1.7\n");
        else
            printf("n                 t(n)"
                "         t(n)/n     t(n)/n^2.0     t(n)/n^2.5\n");
    }
    if (algoritmo == ord_rap) {
        if (initvector == init_ascendente)
            printf("n                 t(n)"
                "    t(n)/log(n)           t(n)/n       t(n)/n^2\n");
        else
            printf("n                 t(n)"
                "    t(n)/log(n)  t(n)/(n*log(n))       t(n)/n^2\n");
    }
}

void imprimirresultados(int n, double t, void algoritmo(int [], int), void initvector(int [], int)) {
    double x = 0, y = 0, z = 0;

    if (algoritmo == ord_ins) {
        if (initvector == init_ascendente) {
            x = t / log(n);
            y = t / n;
            z = t / pow(n, 1.7);
        } else {
            x = t / n;
            y = t / pow(n, 2.0);
            z = t / pow(n, 2.5);
        }
        printf(" %5d%13.3f%15.8f%15.8f%15.8f\n", n, t, x, y, z);
    }
    if (algoritmo == ord_rap) {
        if (initvector == init_ascendente) {
            x = t / log(n);
            y = t / n;
            z = t / pow(n, 2.0);
        } else {
            x = t / log(n);
            y = t / (n * log(n));
            z = t / pow(n, 2.0);
        }

        printf(" %5d%13.3f%15.5f%17.8f%15.8f\n", n, t, x, y, z);
    }
}

void tablas(void algoritmo(int [], int)) {
    char *nombrealg;
    if (algoritmo == ord_ins) nombrealg = "Ordenación por inserción";
    if (algoritmo == ord_rap) nombrealg = "Ordenación rápida";
    printf("\n--- Tablas de tiempos | %s ---\n", nombrealg);
    creartabla(init_aleatorio, algoritmo, nombrealg, "aleatorio");
    creartabla(init_ascendente, algoritmo, nombrealg, "ascendente");
    creartabla(init_descendente, algoritmo, nombrealg, "descendente");
}

double microsegundos() {
    struct timeval t;
    if (gettimeofday(&t,NULL) < 0) return 0.0;
    return (t.tv_usec + t.tv_sec * 1000000.0);
}
