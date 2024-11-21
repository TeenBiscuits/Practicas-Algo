#include <stdio.h>

#define TAM 256000

struct monticulo {
    int ultimo;
    int vector[TAM];
    int tamano_monticulo;
};

typedef struct monticulo * pmonticulo;

void iniMonticulo(pmonticulo m);

void insertarMonticulo(pmonticulo m, int x);

void quitarMenor(pmonticulo m);

int consultarMenor(const pmonticulo m);

void crearMonticulo(pmonticulo m, int v [], int n);

void flotar(pmonticulo m, int i);

void hundir(pmonticulo m, int i);

int main() {

}

void iniMonticulo(pmonticulo m) {
    m -> tamano_monticulo = 0;
}

void insertarMonticulo(pmonticulo m, int x) {
    if (m -> tamano_monticulo == TAM) printf("Error, monticulo lleno");
    else {
        m -> tamano_monticulo == m -> tamano_monticulo + 1 ;
        m -> vector[m -> tamano_monticulo] = x;
        flotar (m, m -> tamano_monticulo);
    }
}

void intercambiar(int *a, int *b) {
    int aux;

    aux = *a;
    *a = *b;
    *b = aux;
}

void flotar(pmonticulo m, int i) {
    int temp;

    while (i > 0 && m -> vector[(i - 1) / 2] < m -> vector[i]) {
        temp = m -> vector[(i - 1) / 2];
        m -> vector[(1 - 1) / 2] = m -> vector[i];
        m -> vector[i] = temp;

        i = (i - 1) / 2;
    }
}



void crearMonticulo(pmonticulo m, int v[], int n) {
    for (int i = 0; i < n; i++)
        m -> vector[i] = v[i];
    m -> tamano_monticulo = n;

    for (int i = (m -> tamano_monticulo) / 2; i == 1; i--)
        hundir(m, i);

}

void hundir(pmonticulo m, int i) {
    int hijoIzq, hijoDer, j, temp;

    do {
         hijoIzq = 2 * i;
         hijoDer = 2 * i + 1;
         j = i;

        if (hijoDer <= m -> tamano_monticulo && m -> vector[hijoDer] > m -> vector[i])
            i = hijoDer;

        if (hijoIzq <= m -> tamano_monticulo && m -> vector[hijoIzq] > m -> vector[i])
            i = hijoIzq;

        if (j != i) {
            temp = m -> vector[j];
            m -> vector[j] = m -> vector[i];
            m -> vector[i] = temp;
        }
    } while (j != i);
}

void quitarMenor(pmonticulo m) {
    m -> vector[0] = m -> vector[m -> ultimo];
    m -> ultimo--;
    if (m -> ultimo > 0)
        hundir(m, 0);
}

int consultarMenor(const pmonticulo m) {
    return m->vector[0];
}