#include <stdio.h>

void ord_ins (int v[], int n);

void ord_rap_aux (int v[], int iz, int dr);

void ord_rap (int v[], int n);

int main(void) {
    printf("Hello, World!\n");
    return 0;
}

void ord_ins (int v[], int n) {
    /* ... */
}

void ord_rap_aux (int v[], int iz, int dr) {
    /* ... */
}

void ord_rap (int v[], int n) {
    ord_rap_aux(v, 0, n-1);
}
