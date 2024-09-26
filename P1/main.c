#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/time.h>

void test();

double microsegundos();

int fib1(int n);

int fib2(int n);

int fib3(int n);

int main(void) {
    // Impresión en archivo
    int fd;
    char *name = "tiempos.txt";
    fd = open(name, O_WRONLY | O_CREAT, 0644);
    if (fd == -1) {
        perror("open failed");
        return 1;
    }

    if (dup2(fd, 1) == -1) {
        perror("dup2 failed");
        return 1;
    }

    // Test Function
    test();

    return 0;
}

void test(){
    int n1[5] = {2,4,8,16,32};
    int n2[5] = {1000,10000,100000,1000000,10000000};
    puts("Test de funciones de Fibonacci");
    puts("Por Pablo Portas, Pablo Míguez y Maite González");
    puts("");

    printf("función\t       n\t tiempo   sqrt(log(n))\t       log(n)\t      n**0.5\n");
    printf("----------------------------------------------------------------------------\n");

    double t1, t2, t, x, y, z;

    // Algoritmo Fib 1
    // Mediciones con valores {2,4,8,16,32}
    for(int i = 0; i < 5; i++) {
        t1 = microsegundos();
        fib1(n1[i]);
        t2 = microsegundos();
        t = t2-t1;
        x = t / sqrt(log(n1[i]));
        y = t / log(n1[i]);
        z = t / pow(n1[i], 0.5);
        printf("fib1%12d%15.3f%15.6f%15.6f%15.6f\n", n1[i], t, x, y, z);
    }

    // Algoritmo Fib2
    // Mediciones con valores {1000,10000,100000,1000000,10000000}
    for(int i = 0; i < 5; i++) {
        t1 = microsegundos();
        fib2(n2[i]);
        t2 = microsegundos();
        t = t2-t1;
        x = t / sqrt(log(n2[i]));
        y = t / log(n2[i]);
        z = t / pow(n2[i], 0.5);
        printf("fib2%12d%15.3f%15.6f%15.6f%15.6f\n", n2[i], t, x, y, z);
    }

    // Algoritmo Fib3
    // Mediciones con valores {1000,10000,100000,1000000,10000000}
    for(int i = 0; i < sizeof(n2); i++) {
        t1 = microsegundos();
        fib3(n2[i]);
        t2 = microsegundos();
        t = t2-t1;
        x = t / sqrt(log(n2[i]));
        y = t / log(n2[i]);
        z = t / pow(n2[i], 0.5);
        printf("fib3%12d%15.3f%15.6f%15.6f%15.6f\n", n2[i], t, x, y, z);
    }
    printf("----------------------------------------------------------------------------\n");
}

int fib1(int n){

    if (n < 2) {
    return n;
    } else {
        return fib1(n-1) + fib1(n-2);
    }
}

int fib2(int n){
int i=1;
int j=0;
    for (int k = 0; k < n; ++k) {
        j = i+j;
        i = j-i;
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
        t = (int) powf((float) h,2);
        h = 2 * k * h + t;
        k = (int) powf((float) k,2) + t;
        n = n / 2;
    }
    return j;
}
double microsegundos(){
    struct timeval t;
    if (gettimeofday(&t,NULL)<0)
        return 0.0;
    return (t.tv_usec + t.tv_sec * 1000000.0);
}








