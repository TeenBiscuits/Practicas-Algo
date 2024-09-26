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

void imprimircabecerat(int algo);

void imprimirresultados(int n, double t, int algo);

int main(void) {
    if (guardaraarchivo()) test();
    return 0;
}

bool guardaraarchivo() {
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

void test() {
    int n = 1;
    const int n1[5] = {2, 4, 8, 16, 32},
            n2[5] = {1000, 10000, 100000, 1000000, 10000000};
    printf("Algoritmos de Fibonacci   -  "
        "Por Pablo Portas, Pablo Míguez y Maite González\n\n");
    for (int alg = 1; alg <= 3; alg++) {
        imprimircabecerat(alg);
        for (int i = 0; i < 5; i++) {
            if (alg == 1) n = n1[i];
            else n = n2[i];
            const double t1 = microsegundos();
            selectalgo(n, alg);
            const double t2 = microsegundos();
            double t = t2 - t1;
            if (t <= 500) t = tiempospetit(n, alg);
            imprimirresultados(n, t, alg);
        }
        printf("---------------------------------------------"
            "-------------------------------\n\n");
    }
}

int selectalgo(const int n, const int algo) {
    if (algo == 1) return fib1(n);
    if (algo == 2) return fib2(n);
    if (algo == 3) return fib3(n);
    return 0;
}

int fib1(const int n) {
    if (n < 2) {
        return n;
    } else {
        return fib1(n - 1) + fib1(n - 2);
    }
}

int fib2(const int n) {
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

double tiempospetit(const int n, const int alg) {
    double t = 0;
    int k;
    for (k = 1; t < 500; k = k * 10) {
        const double ta = microsegundos();
        for (int i = k; i > 0; i--) selectalgo(n, alg);
        const double tb = microsegundos();
        t = tb - ta;
    }
    printf("(*) Dato promedio de k = %d\n",k);
    return t / (double) k;
}

void imprimircabecerat(int algo) {
    if (algo == 1) {
        printf("función	       n         tiempo"
            "         1.1**n              n           n**2\n");
    }
    if (algo == 2) {
        printf("función	       n         tiempo"
            "         n**0.8              n       n*log(n)\n");
    }
    if (algo == 3) {
        printf("función	       n         tiempo"
            "   sqrt(log(n))         log(n)         n**0.5\n");
    }
    printf("---------------------------------------------"
        "-------------------------------\n");
}

void imprimirresultados(int n, double t, int algo) {
    char *nombre = "fib";
    double x = 0, y = 0, z = 0;
    // Las funciones son en este orden
    // x = Cota subestimada
    // y = Cota Ajustada (O grande)
    // z = Cota sobreestimada
    if (algo == 1) {
        nombre = "fib1";
        x = t / pow(1.1, n);
        y = t / pow((1 + sqrt(5)) / 2, n);
        z = t / pow(2, n);
    }
    if (algo == 2) {
        nombre = "fib2";
        x = t / pow(n, 0.8);
        y = t / n;
        z = t / (n * log(n));
    }
    if (algo == 3) {
        nombre = "fib3";
        x = t / sqrt(log(n));
        y = t / log(n);
        z = t / pow(n, 0.5);
    }
    printf("%s%12d%15.3f%15.6f%15.6f%15.6f\n", nombre, n, t, x, y, z);
}

double microsegundos() {
    struct timeval t;
    if (gettimeofday(&t,NULL) < 0) return 0.0;
    return (t.tv_usec + t.tv_sec * 1000000.0);
}
