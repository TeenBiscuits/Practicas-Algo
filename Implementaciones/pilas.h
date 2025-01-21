// Creado por Pablo P.

#ifndef PILAS_H
#define PILAS_H

#define TAMANO_MAXIMO_PILA 10
typedef int tipo_elemento;

typedef struct {
    int cima;
    tipo_elemento vector[TAMANO_MAXIMO_PILA];
} pila;

void crear_pila(pila *);

int pila_vacia(pila);

void apilar(tipo_elemento, pila *);

tipo_elemento cima(pila);

void desapilar(pila *);

/* ERRORES: cima o desapilar sobre la pila vacía
            apilar sobre la pila llena */

#endif //PILAS_H
