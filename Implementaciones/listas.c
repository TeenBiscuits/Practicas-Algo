// Creado por Pablo P.

#include <stdlib.h>
#include <stdio.h>
#include "listas.h"

static struct nodo *crearnodo() {
    struct nodo *tmp = malloc(sizeof(struct nodo));
    if (tmp == NULL) {
        printf("memoria agotada\n");
        exit(EXIT_FAILURE);
    }
    return tmp;
}

lista crearlista() {
    struct nodo *l = crearnodo();
    l->sig = NULL;
    return l;
}

int eslistavacia(lista l) {
    return (l->sig == NULL);
}

void insertar(void *x, posicion p) {
    struct nodo *tmp = crearnodo();
    tmp->elem = x;
    tmp->sig = p->sig;
    p->sig = tmp;
}

posicion buscar(lista l, void *e, int (*comp)(const void *x, const void *y)) {
    struct nodo *p = l->sig;
    while (p != NULL && 0 != (*comp)(p->elem, e))
        p = p->sig;
    return p;
}

static posicion buscarant(lista l, void *x, int (*comp)(const void *, const void *)) {
    struct nodo *p = l;
    while (p->sig != NULL && 0 != (*comp)(p->sig->elem, x))
        p = p->sig;
    return p;
}

static int esultimoelemento(struct nodo *p) {
    return (p->sig == NULL);
}

void borrar(lista l, void *x, int (*comp)(const void *, const void *)) {
    struct nodo *tmp, *p = buscarant(l, x, comp);
    if (!esultimoelemento(p)) {
        tmp = p->sig;
        p->sig = tmp->sig;
        free(tmp);
    }
}

posicion primero(lista l) { return l->sig; }
posicion siguiente(posicion p) { return p->sig; }
int esfindelista(posicion p) { return (p == NULL); }
void *elemento(posicion p) { return p->elem; }
