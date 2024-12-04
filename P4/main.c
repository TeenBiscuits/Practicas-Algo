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

typedef struct monticulo * pmonticulo;


bool guardararchivo();

void iniMonticulo(pmonticulo m);

void insertarMonticulo(pmonticulo m, int x);

void quitarMenor(pmonticulo m);

int consultarMenor(const pmonticulo m);

void crearMonticulo(pmonticulo m, int v[], int n);

void flotar(pmonticulo m, int i);

void hundir(pmonticulo m, int i);

void ordenarPorMonticulos(int v[], int n);

void inicializarVectorAleatorio(int v[], int n);

void comprobar();

void tiempos();

void selectfuncion(const int n, const int funcion);

void print_cabecerat();

double microsegundos();

int main() {
    if (guardararchivo()) {
        printf("<--- Práctica de Pablos & Maite --->\n");
        printf("<--- ORDENACIÓN POR MONTÍCULOS --->\n");
        comprobar();
    }
    return 0;
}

void iniMonticulo(pmonticulo m) {
    m->ultimo = -1;
}

void insertarMonticulo(pmonticulo m, int x) {
    if (m -> ultimo == TAM - 1) printf("Error, monticulo lleno\n");
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
    m->vector[0] = m->vector[m -> ultimo];
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

bool guardararchivo() {
    const char *name = "tiempos.txt";
    const int fd = open(name, O_WRONLY | O_CREAT, 0644);
    if (fd == -1) {
        perror("open failed");
        return false;
    }
    if (dup2(fd, 1) == -1) {
        perror("dup2 failed");
        return false;
    }
    return true;
}

void inicializarVectorAleatorio(int v[], int n) {
    srand(time(NULL));
    int i, m = 2 * n + 1;

    for  (i = 0; i < n; i++)
        v[i] = (rand() % m) - n;
}

void comprobar() {
    struct monticulo M;
    int n = 10, min = 1, max = 1000;
    int vector[n];

    inicializarVectorAleatorio(vector, n);
    printf("Vector a ordenar: ");
    for (int i = 0; i < n; i++)
        printf("%d ", vector[i]);
    printf("\n");

    crearMonticulo(&M, vector, n);

    printf("Menor elemento: %d\n", consultarMenor(&M));
    quitarMenor(&M);
    printf("Menor elemento tras eliminar: %d\n", consultarMenor(&M));

    ordenarPorMonticulos(vector, n);
    printf("Vector ordenado: ");
    for (int i = 0; i < n; i++)
        printf("%d ", vector[i]);
    printf("\n");
}

void selectfuncion(int v[], int n, int funcion) {
    struct monticulo monticulo;
    pmonticulo m = &monticulo;
    iniMonticulo(m);
    int x;

    switch (funcion) {
        case 1:
            insertarMonticulo(m, x);
        break;
        case 2:
            crearMonticulo(m, v, n);
        break;
        case 3:
            ordenarPorMonticulos(v, n);
        break;
    }
}

void imprimir_cabecerat() {

}
void tiempos() {
    const int n[8] = {1000, 5000, 10000, 25000, 50000, 100000, 200000, 256000};
    int inicio = 0, final = 0;
}

double microsegundos() {
    struct timeval t;
    if (gettimeofday(&t,NULL) < 0) return 0.0;
    return (t.tv_usec + t.tv_sec * 1000000.0);
}

