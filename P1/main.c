#include <stdio.h>

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

int fib3(int n){

}









