// Creado por Pablo P. Pablo M. Maite G.

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdbool.h>
#include <math.h>
#include <sys/time.h>

bool guardaraarchivo(const char *archivo);

void ord_ins(int v[], int n);

void ord_rap_aux(int v[], int iz, int dr);

void ord_rap(int v[], int n);

void intercambiar(int *a, int *b);

void imprimir(int v[], int n);

void aleatorio(int v[], int n);

void inicializar_semilla();

void descendente(int v[], int n);

void ascendente(int v[], int n);

void test();

void tablas();

void creartabla(void initvector(int[], int), void algoritmo(int[], int), const char *tipoVector, const char *nombreAlgoritmo, int valoresN[]);

double microsegundos();

void test_algo(void algoritmo(int *, int), int n);

int test_orden(int v[], int n);

int main(void) {
    if (guardaraarchivo("tiempos.txt")) {
        printf("<--- Práctica de Pablos & Maite --->\n");
        test();
        tablas();
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
        x = iz + rand() % (dr - iz + 1);
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

void ascendente(int v[], int n) {
    for (int i = 0; i < n; i++)
        v[i] = i;
}

void test() {
    int size = 20;
    printf("\n--- Iniciando tests de tamaño %d ---\n",size);
    printf("\n--- Test 1 | Ordenación por inserción ---\n");
    test_algo(ord_ins, size);
    printf("\n--- Test 2 | Ordenación rápida ---\n");
    test_algo(ord_rap, size);
}

void creartabla(void initvector(int[], int), void algoritmo(int[], int), const char *tipoVector, const char *nombreAlgoritmo, int valoresN[]) {
    printf("\n%s con inicialización %s\n", nombreAlgoritmo, tipoVector);
    printf("n               t(n)     t(n)/n^1.8       t(n)/n^2     t(n)/n^2.2\n");

    for (int k = 0; k < 7; k++) {
        int n = valoresN[k];
        int v[n];
        double inicio, fin, t;

        initvector(v, n);

        inicio = microsegundos();
        algoritmo(v, n);
        fin = microsegundos();
        t = (fin-inicio);

        if(t < 500){
            printf("¡TIEMPO PETIT ENCONTRADO! PROMEDIO DE 1000 REPETICIONES\n");
            int m = 0;
            inicio = microsegundos();
            for(; m < 1000; m++) {
                algoritmo(v, n);
            }
            fin = microsegundos();
            t = (fin-inicio) / m;
        }

        double x = t / pow(n, 1.8);
        double y = t / pow(n, 2.0);
        double z = t / pow(n, 2.2);

        printf("%5d%15.3f%15.12f%15.12f%15.12f\n", n, t, x, y, z);
    }
}

double microsegundos() {
    struct timeval t;
    if (gettimeofday(&t,NULL) < 0) return 0.0;
    return (t.tv_usec + t.tv_sec * 1000000.0);
}

void tablas() {
    int valoresene[] = {500, 1000, 2000, 4000, 8000, 16000, 32000};

    creartabla(aleatorio, ord_ins, "aleatoria", "Ordenación por inserción", valoresene);
    creartabla(ascendente, ord_ins, "ascendente", "Ordenación por inserción", valoresene);
    creartabla(descendente, ord_ins, "descendente", "Ordenación por inserción", valoresene);
    creartabla(aleatorio, ord_rap, "aleatoria", "Ordenación rápida", valoresene);
    creartabla(ascendente, ord_rap, "ascendente", "Ordenación rápida", valoresene);
    creartabla(descendente, ord_rap, "descendente", "Ordenación rápida", valoresene);

}

void test_algo(void algoritmo(int *, int), int n) {
    int v1[n], v2[n];
    inicializar_semilla();
    aleatorio(v1, n);
    descendente(v2, n);

    printf("Ordenación con inicialización aleatoria\n");
    imprimir(v1, n);
    printf("¿Ordenado? %d\nOrdenando...\n",test_orden(v1,n));
    algoritmo(v1, n);
    imprimir(v1, n);
    printf("¿Ordenado? %d\nOrdenando...\n",test_orden(v1,n));

    printf("Ordenación con inicialización descendente\n");
    imprimir(v2, n);
    printf("¿Ordenado? %d\nOrdenando...\n",test_orden(v2,n));
    algoritmo(v2, n);
    imprimir(v2, n);
    printf("¿Ordenado? %d\n",test_orden(v2,n));

    printf("\n");
}

int test_orden(int v[], int n) {
    for(int i = 1; i < n; i++) {
        if(v[i] < v[i - 1]) return 0;
    }
    return 1;
}
