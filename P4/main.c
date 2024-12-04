#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <stdbool.h>
#include <fcntl.h>
#include <unistd.h>

#define TAM 256000

struct monticulo {
    int ultimo;
    int vector[TAM];
};

typedef struct monticulo *pmonticulo;

void iniMonticulo(pmonticulo m);

void insertarMonticulo(pmonticulo m, int x);

void quitarMenor(pmonticulo m);

int consultarMenor(pmonticulo m);

void crearMonticulo(pmonticulo m, int v[], int n);

void flotar(pmonticulo m, int i);

void hundir(pmonticulo m, int i);

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

void iniMonticulo(pmonticulo m) {
    m->ultimo = -1;
}

void insertarMonticulo(pmonticulo m, int x) {
    if (m->ultimo == TAM - 1) printf("Error, montículo lleno\n");
    else {
        m->ultimo++;
        m->vector[m->ultimo] = x;
        flotar(m, m->ultimo);
    }
}

void flotar(pmonticulo m, int i) {
    int temp;

    while (i > 0 && m->vector[(i - 1) / 2] > m->vector[i]) {
        temp = m->vector[(i - 1) / 2];
        m->vector[(i - 1) / 2] = m->vector[i];
        m->vector[i] = temp;
        i = (i - 1) / 2;
    }
}

void crearMonticulo(pmonticulo m, int v[], int n) {
    for (int i = 0; i < n; i++)
        m->vector[i] = v[i];

    m->ultimo = n - 1;

    for (int i = (m->ultimo - 1) / 2; i >= 0; i--)
        hundir(m, i);
}

void hundir(pmonticulo m, int i) {
    int hijoIzq, hijoDer, menor, temp;

    do {
        hijoIzq = 2 * i + 1;
        hijoDer = 2 * i + 2;
        menor = i;

        if (hijoIzq <= m->ultimo && m->vector[hijoIzq] < m->vector[menor])
            menor = hijoIzq;
        if (hijoDer <= m->ultimo && m->vector[hijoDer] < m->vector[menor])
            menor = hijoDer;

        if (menor != i) {
            temp = m->vector[i];
            m->vector[i] = m->vector[menor];
            m->vector[menor] = temp;
            i = menor;
        } else {
            break;
        }
    } while (1);
}

void quitarMenor(pmonticulo m) {
    m->vector[0] = m->vector[m->ultimo];
    m->ultimo--;
    if (m->ultimo >= 0)
        hundir(m, 0);
}

int consultarMenor(const pmonticulo m) {
    if (m->ultimo < 0) {
        printf("Error, monticulo vacio\n");
        return -1;
    }
    return m->vector[0];
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
