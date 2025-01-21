// Creado por Pablo P.

#include <stdlib.h>
#include <stdio.h>
#include "pilas.h"

void crear_pila(pila *p) {
    p->cima = -1;
}

int pila_vacia(pila p) {
    return (p.cima == -1);
}

void apilar(tipo_elemento x, pila *p) {
    if (++p->cima == TAMANO_MAXIMO_PILA) {
        printf("Error: pila llena\n");
        exit(EXIT_FAILURE);
    }
    p->vector[p->cima] = x;
}

tipo_elemento cima(pila p) {
    if (pila_vacia(p)) {
        printf("Error: pila vacía\n");
        exit(EXIT_FAILURE);
    }
    return p.vector[p.cima];
}

void desapilar(pila *p) {
    if (pila_vacia(*p)) {
        printf("Error: pila vacía\n");
        exit(EXIT_FAILURE);
    }
    p->cima--;
}
