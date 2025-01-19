//
// Created by pablo on 18/01/2025.
//

#include "ordenar.h"

#include <stdlib.h>

void ord_ins(int v[], int n) {
    int x = 0, j = 0, i;

    for (i = 1; i < n; i++) {
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
    int i, j, x, pivote;

    if (iz < dr) {
        x = iz + rand() % (dr - iz + 1);
        pivote = v[x];
        intercambiar(&v[iz], &v[x]);
        i = iz + 1;
        j = dr;

        while (i <= j) {
            while (i <= dr && v[i] < pivote) {
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
        ord_rap_aux(v, iz, j - 1);
        ord_rap_aux(v, j + 1, dr);
    }
}

void ord_rap(int v[], int n) {
    ord_rap_aux(v, 0, n - 1);
}

void intercambiar(int *a, int *b) {
    int aux;

    aux = *a;
    *a = *b;
    *b = aux;
}

void init_aleatorio(int v[], int n) {
    int i, m = 2 * n + 1;
    for (i = 0; i < n; i++)
        v[i] = (rand() % m) - n;
}

void init_descendente(int v[], int n) {
    int i, j;
    for (i = 0, j = n; i < n; i++, j--)
        v[i] = j;
}

void init_ascendente(int v[], int n) {
    int i;
    for (i = 0; i < n; i++)
        v[i] = i;
}
