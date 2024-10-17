#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdbool.h>

bool guardaraarchivo(const char *archivo);

void ord_ins(int v[], int n);

void ord_rap_aux(int v[], int iz, int dr);

void ord_rap(int v[], int n);

void intercambiar(int *a, int *b);

void imprimir(int v[], int n);

void aleatorio(int v[], int n);

void inicializar_semilla();

void descendente(int v[], int n);

void test();

void test_algo(void algoritmo(int *, int), int n);

int test_orden(int v[], int n);

int main(void) {
    if (guardaraarchivo("tiempos.txt")) {
        test();
    }
    else return EXIT_FAILURE;
    return EXIT_SUCCESS;
}

bool guardaraarchivo(const char *archivo) {
    int file = open(archivo, O_WRONLY | O_CREAT, 0644);
    if (file == -1) {
        perror("open failed");
        return false;
    }
    if (dup2(file, 1) == -1) {
        perror("dup2 failed");
        return false;
    }
    return true;
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
    int size = 20;
    printf("\n--- Iniciando tests de tamaño %d ---\n",size);
    printf("\n--- Test 1 | Ordenación por inserción ---\n");
    test_algo(ord_ins, size);
    printf("\n--- Test 2 | Ordenación rápida ---\n");
    test_algo(ord_rap, size);
}

void test_algo(void algoritmo(int *, int), int n) {
    int v1[n], v2[n];
    inicializar_semilla();
    aleatorio(v1, n);
    descendente(v2, n);

    printf("Ordenación con inicialización aleatoria\n");
    imprimir(v1, n);
    printf("ordenado? %d\nordenando...\n",test_orden(v1,n));
    algoritmo(v1, n);
    imprimir(v1, n);
    printf("ordenado? %d\nordenando...\n",test_orden(v1,n));

    printf("Ordenación con inicialización descendente\n");
    imprimir(v2, n);
    printf("ordenado? %d\nordenando...\n",test_orden(v2,n));
    algoritmo(v2, n);
    imprimir(v2, n);
    printf("ordenado? %d\nordenando...\n",test_orden(v2,n));

    printf("\n");
}

int test_orden(int v[], int n) {
    for(int i = 1; i < n; i++) {
        if(v[i] < v[i - 1]) return 0;
    }
    return 1;
}
