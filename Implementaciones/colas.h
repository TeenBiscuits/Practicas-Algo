// Creado por Pablo P.

#ifndef COLAS_H
#define COLAS_H

#define TAMANO_MAXIMO_COLA 5
typedef int tipo_elemento;

typedef struct {
    int cabeza, final, tamano;
    tipo_elemento vector[TAMANO_MAXIMO_COLA];
} cola;

void crear_cola(cola *);

int cola_vacia(cola);

void insertar(tipo_elemento, cola *);

tipo_elemento quitar_primero(cola *);

tipo_elemento primero(cola);

/* ERRORES: quitar_primero o primero sobre una cola vacía
            insertar en una cola llena */

#endif //COLAS_H
