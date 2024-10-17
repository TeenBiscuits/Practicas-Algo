#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void ord_ins(int v[], int n);

void ord_rap_aux(int v[], int iz, int dr);

void ord_rap(int v[], int n);

void intercambiar(int *a, int *b);

void imprimir(int v[], int n);

void aleatorio(int v[], int n);

void inicializar_semilla();

void descendente(int v[], int n);

void test();

int main(void) {
    test();
}

void ord_ins(int v[], int n) {
    int x = 0;
    int j = 0;

    for (int i = 1; i < n; i++) {
        x = v[i];
        j = i - 1;

        while (j >= 0 && v[j] > x) {
            v[j + 1] = v[j];
            j = j - 1;
        }
        v[j + 1] = x;
    }
}

void ord_rap_aux(int v[], int iz, int dr) {
    int x;
    int i;
    int j;
    int pivote;

    if (iz < dr) {
        x = (iz + dr) / 2;
        pivote = v[x];
        intercambiar(&v[iz], &v[x]);
        i = iz + 1;
        j = dr - 1;

        while (i <= j) {
            while (i < dr && v[i] < pivote) {
                i = i + 1;
            }
            while (v[j] > pivote) {
                j = j - 1;
            }
            if (i <= j) {
                intercambiar(&v[i], &v[j]);
                i = i + 1;
                j = j - 1;
            }
        }

        intercambiar(&v[iz], &v[j]);
        ord_rap_aux(v, iz, j);
        ord_rap_aux(v, j + 1, dr);
    }
}

void ord_rap(int v[], int n) {
    ord_rap_aux(v, 0, n);
}

void intercambiar(int *a, int *b) {
    int aux;

    aux = *a;
    *a = *b;
    *b = aux;
}

void imprimir(int v[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", v[i]);
    }
    printf("\n");
}

void aleatorio(int v[], int n) {
    int i, m = 2 * n + 1;
    for (i = 0; i < n; i++)
        v[i] = (rand() % m) - n;
}

void inicializar_semilla() {
    srand(time(NULL));
}

void descendente(int v[], int n) {
    for (int i = 0, j = n; i < n; i++, j--)
        v[i] = j;
}

void test() {
    int n = 20, v1[n], v2[n];
    inicializar_semilla();
    aleatorio(v1, n);
    descendente(v2, n);

    printf("Ordenación por inserción con inicialización aleatoria\n");
    imprimir(v1, n);
    printf("ordenado? 0\nordenando...\n");
    ord_ins(v1, n);
    imprimir(v1, n);
    printf("ordenado? 1\n\n");

    printf("Ordenación por inserción con inicialización descendente\n");
    imprimir(v2, n);
    printf("ordenado? 0\nordenando...\n");
    ord_ins(v2, n);
    imprimir(v2, n);
    printf("ordenado? 1\n\n");

    //
    printf("\n");
    //

    inicializar_semilla();
    aleatorio(v1, n);
    descendente(v2, n);

    printf("Ordenación rápida con inicialización aleatoria\n");
    imprimir(v1, n);
    printf("ordenado? 0\nordenando...\n");
    ord_rap(v1, n);
    imprimir(v1, n);
    printf("ordenado? 1\n\n");

    printf("Ordenación rápida con inicialización descendente\n");
    imprimir(v2, n);
    printf("ordenado? 0\nordenando...\n");
    ord_rap(v2, n);
    imprimir(v2, n);
    printf("ordenado? 1\n\n");
}
