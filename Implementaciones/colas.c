// Creado por Pablo P.

#include <stdlib.h>
#include <stdio.h>
#include "colas.h"

void crear_cola(cola *c) {
    c->tamano = 0;
    c->cabeza = 0;
    c->final = -1;
}

int cola_vacia(cola c) {
    return (c.tamano == 0);
}

void incrementar(int *x) {
    /* privado */
    if (++(*x) == TAMANO_MAXIMO_COLA)
        *x = 0;
}

void insertar(tipo_elemento x, cola *c) {
    if (c->tamano == TAMANO_MAXIMO_COLA) {
        printf("error: cola llena: %d\n", c->tamano);
        exit(EXIT_FAILURE);
    }
    c->tamano++;
    incrementar(&(c->final));
    c->vector[c->final] = x;
}

tipo_elemento primero(cola c) {
    if (cola_vacia(c)) {
        printf("error: cola vacia\n");
        exit(EXIT_FAILURE);
    }
    return (c.vector[c.cabeza]);
}

tipo_elemento quitar_primero(cola *c) {
    tipo_elemento x;
    if (cola_vacia(*c)) {
        printf("error: cola vacia\n");
        exit(EXIT_FAILURE);
    }
    c->tamano--;
    x = c->vector[c->cabeza];
    incrementar(&(c->cabeza));
    return x;
}
