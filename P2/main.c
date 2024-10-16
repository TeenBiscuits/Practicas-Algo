#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void ord_ins (int v[], int n);

void ord_rap_aux (int v[], int iz, int dr);

void ord_rap (int v[], int n);

void intercambiar (int *a, int *b);

void imprimir (int v[], int n);

void aleatorio(int v[], int n);

void inicializar_semilla();

void ascendente (int v[], int n);

int main(void) {
    int n=20;
    int v1[n] ;//= {2, 6, 3, 9, 5, 4, 1, 7, 8, 0};

    inicializar_semilla();

    aleatorio(v1, n);
    //ord_ins (v1, n);

    ord_rap(v1, n);
    imprimir (v1, n);


}

void ord_ins (int v[], int n) {
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

void ord_rap_aux (int v[], int iz, int dr) {
    int x;
    int i;
    int j;
    int pivote;

    if (iz < dr) {
        x = (iz+dr)/2;
        pivote = v[x];
        intercambiar (&v[iz], &v[x]);
        i = iz + 1;
        j = dr-1;

        while (i <= j) {
            while (i < dr && v[i] < pivote) {
                i = i + 1;
            }
            while (v[j] > pivote) {
                j = j - 1;
            }
            if (i <= j) {
                intercambiar (&v[i], &v[j]);
                i = i + 1;
                j = j - 1;
            }
        }

        intercambiar (&v[iz], &v[j]);
        ord_rap_aux(v, iz, j);
        ord_rap_aux(v, j+1, dr);
    }
}

void ord_rap (int v[], int n) {
    ord_rap_aux(v, 0, n-1);
}

void intercambiar (int *a, int *b) {
    int aux;

    aux = *a;
    *a = *b;
    *b = aux;
}

void imprimir (int v[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", v[i]);
    }
    printf("\n");
}

void aleatorio(int v [], int n) {
    int i, m=2*n+1;
    for (i=0; i < n; i++)
        v[i] = (rand() % m) - n;
}

void inicializar_semilla() {
    srand(time(NULL));
}

void ascendente(int v [], int n) {
    int i;
    for (i=0; i < n; i++)
        v[i] = i;
}