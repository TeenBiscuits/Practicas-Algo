#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/time.h>

bool guardaraarchivo();

void test();

double microsegundos();

int selectalgo(int n, int algo);

int fib1(int n);

int fib2(int n);

int fib3(int n);

double tiempospetit(int n, int alg);

int main(void) {
    // Impresión en archivo
    if (guardaraarchivo()) {
        // Test Function
        test();
    }
    return 0;
}

bool guardaraarchivo() {
    int fd;
    char *name = "tiempos.txt";
    fd = open(name, O_WRONLY | O_CREAT, 0644);
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

void test() {
    int n = 1;
    int n1[5] = {2, 4, 8, 16, 32};
    int n2[5] = {1000, 10000, 100000, 1000000, 10000000};

    printf("Test de funciones de Fibonacci\n"
        "Por Pablo Portas, Pablo Míguez y Maite González\n");
    printf("función\t       n         tiempo"
        "   sqrt(log(n))         log(n)         n**0.5\n"
        "---------------------------------------------"
        "-------------------------------\n");

    char *nombref = "fib";
    double t1, t2, t, x, y, z;

    for (int alg = 1; alg <= 3; alg++) {
        for (int i = 0; i < 5; i++) {
            if (alg == 1) {
                nombref = "fib1";
                n = n1[i];
            }
            if (alg == 2) {
                nombref = "fib2";
                n = n2[i];
            }
            if (alg == 3) {
                nombref = "fib3";
                n = n2[i];
            }
            t1 = microsegundos();
            selectalgo(n, alg);
            t2 = microsegundos();
            t = t2 - t1;
            if (t <= 500) {
                t = tiempospetit(n, alg);
            }
            x = t / sqrt(log(n));
            y = t / log(n);
            z = t / pow(n, 0.5);
            printf("%s%12d%15.3f%15.6f%15.6f%15.6f\n", nombref, n, t, x, y, z);
        }
    }

    printf("----------------------------------------------------------------------------\n");
}

int selectalgo(int n, int algo) {
    if (algo == 1) return fib1(n);
    if (algo == 2) return fib2(n);
    if (algo == 3) return fib3(n);
    return 0;
}

int fib1(int n) {
    if (n < 2) {
        return n;
    } else {
        return fib1(n - 1) + fib1(n - 2);
    }
}

int fib2(int n) {
    int i = 1, j = 0;
    for (int k = 0; k < n; ++k) {
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
        t = (int) powf((float) h, 2);
        h = 2 * k * h + t;
        k = (int) powf((float) k, 2) + t;
        n = n / 2;
    }
    return j;
}

double tiempospetit(int n, int alg) {
    double t, ta, tb; int k;
    for (k = 1; t < 500; k = k * 2) {
        ta = microsegundos();
        for (int i = k; i > 0; i--) selectalgo(n, alg);
        tb = microsegundos();
        t = tb - ta;
    }
    return t / (double) k;
}

double microsegundos() {
    struct timeval t;
    if (gettimeofday(&t,NULL) < 0)
        return 0.0;
    return (t.tv_usec + t.tv_sec * 1000000.0);
}
