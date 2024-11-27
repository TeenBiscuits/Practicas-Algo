#include <stdio.h>

#define TAM 256000

struct monticulo {
    int ultimo;
    int vector[TAM];
};

typedef struct monticulo * pmonticulo;

void iniMonticulo(pmonticulo m);

void insertarMonticulo(pmonticulo m, int x);

void quitarMenor(pmonticulo m);

int consultarMenor(const pmonticulo m);

void crearMonticulo(pmonticulo m, int v[], int n);

void flotar(pmonticulo m, int i);

void hundir(pmonticulo m, int i);

void ordenarPorMonticulos(int v[], int n);

int main() {
    struct monticulo heap;
    iniMonticulo(&heap);

    int valores[] = {15, 11, 17, 5, 3};
    int n = sizeof(valores) / sizeof(valores[0]);

    crearMonticulo(&heap, valores, n);
    printf("Menor elemento: %d\n", consultarMenor(&heap));
    quitarMenor(&heap);
    printf("Menor elemento tras eliminar: %d\n", consultarMenor(&heap));

    ordenarPorMonticulos(valores, n);
    printf("Vector ordenado:\n");
    for (int i = 0; i < n; i++) {
        printf("%d ", valores[i]);
    }
    printf("\n");
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
    struct monticulo heap;
    iniMonticulo(&heap);

    crearMonticulo(&heap, v, n);
    for (int i = 0; i < n; i++) {
        v[i] = consultarMenor(&heap);
        quitarMenor(&heap);
    }
}

