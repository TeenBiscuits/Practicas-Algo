#include <stdio.h>
#include <math.h>

void test();

int fib1(int n);

int fib2(int n);

int fib3(int n);

int main(void) {
    test();
    return 0;
}

void test(){

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









