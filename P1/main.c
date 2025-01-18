// Creado por Pablo P. Pablo M. Maite G.

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>

void comprobar();

void test(int algo(int n));

int fib1(int n);

int fib2(int n);

int fib3(int n);

double tiempospetit(int n, int algo(int n));

void imprimircabecerat(int algo(int n));

void imprimirresultados(int n, double t, int algo(int n));

double microsegundos();

int main(void) {
    printf("Algoritmos de Fibonacci   -  "
        "Por Pablo Portas, Pablo Míguez y Maite González\n\n");
    comprobar();
    test(fib1);
    test(fib2);
    test(fib3);
    return 0;
}

void comprobar() {
    int i;
    printf("  n    fib1    fib2    fib3\n");
    printf("---------------------------\n");
    for (i = 2; i <= 32; i = i * 2)
        printf("%3d%8d%8d%8d\n", i, fib1(i), fib2(i), fib3(i));
    printf("---------------------------\n\n");
}

void test(int algo(int n)) {
    int n, i;
    double t, t1, t2;
    const int n1[5] = {2, 4, 8, 16, 32},
            n2[5] = {1000, 10000, 100000, 1000000, 10000000};

    imprimircabecerat(algo);
    for (i = 0; i < 5; i++) {
        if (algo == fib1) n = n1[i];
        else n = n2[i];

        t1 = microsegundos();
        algo(n);
        t2 = microsegundos();
        t = t2 - t1;

        if (t <= 500) t = tiempospetit(n, algo);
        else printf("   ");

        imprimirresultados(n, t, algo);
    }
    printf("---------------------------------------------"
        "-----------------------------------\n\n");
}

int fib1(const int n) {
    if (n < 2) {
        return n;
    } else {
        return fib1(n - 1) + fib1(n - 2);
    }
}

int fib2(const int n) {
    int i = 1, j = 0, k;
    for (k = 0; k < n; ++k) {
        j = i + j;
        i = j - i;
    }
    return j;
}

int fib3(int n) {
    int i = 1, j = 0, k = 0, h = 1, t = 0;
    while (n > 0) {
        if (n % 2 != 0) {
            t = j * h;
            j = i * h + j * k + t;
            i = i * k + t;
        }
        t = h * h;
        h = 2 * k * h + t;
        k = k * k + t;
        n = n / 2;
    }
    return j;
}

double tiempospetit(const int n, int algo(int n)) {
    double t = 0, ta = 0, tb = 0;
    int k = 10000, i;

    ta = microsegundos();
    for (i = 0; i <= k; i++) algo(n);
    tb = microsegundos();
    t = tb - ta;

    printf("(*)");
    return t / (double) k;
}

void imprimircabecerat(int algo(int n)) {
    if (algo == fib1)
        printf("función	          n         tiempo"
            "        t/1.1**n            t/n         t/n**2\n");
    if (algo == fib2)
        printf("función	          n         tiempo"
            "        t/n**0.8            t/n   t/(n*log(n))\n");
    if (algo == fib3)
        printf("función	          n         tiempo"
            "  t/sqrt(log(n))       t/log(n)       t/n**0.5\n");
    printf("---------------------------------------------"
        "-----------------------------------\n");
}

void imprimirresultados(int n, double t, int algo(int n)) {
    char *nombre = "fib0";
    double x = 0, y = 0, z = 0;

    if (algo == fib1) {
        nombre = "fib1";
        x = t / pow(1.1, n);
        y = t / pow((1 + sqrt(5)) / 2, n);
        z = t / pow(2, n);
    }
    if (algo == fib2) {
        nombre = "fib2";
        x = t / pow(n, 0.8);
        y = t / n;
        z = t / (n * log(n));
    }
    if (algo == fib3) {
        nombre = "fib3";
        x = t / sqrt(log(n));
        y = t / log(n);
        z = t / pow(n, 0.5);
    }
    printf(" %s%11d%15.5f%16.6f%15.6f%15.8f\n", nombre, n, t, x, y, z);
}

double microsegundos() {
    struct timeval t;
    if (gettimeofday(&t,NULL) < 0) return 0.0;
    return (t.tv_usec + t.tv_sec * 1000000.0);
}
