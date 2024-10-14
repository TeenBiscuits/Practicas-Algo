#include <stdio.h>

void ord_ins (int v[], int n);

void ord_rap_aux (int v[], int iz, int dr);

void ord_rap (int v[], int n);

int main(void) {
    printf("Hello, World!\n");
    return 0;
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
    if (iz < dr) {

    }
}

void ord_rap (int v[], int n) {
    ord_rap_aux(v, 0, n-1);
}
