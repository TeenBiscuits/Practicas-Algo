// Creado por Pablo P.

#ifndef LISTAS_H
#define LISTAS_H

struct nodo {
    void *elem; /* 'void *' es un apuntador 'genérico' */
    struct nodo *sig;
};

typedef struct nodo *posicion;
typedef struct nodo *lista;

lista crearlista();

int eslistavacia(lista l);

void insertar(void *e, posicion p);

/*inserta e tras el nodo apuntado por p*/
posicion buscar(lista l, void *e, int (*comp)(const void *x, const void *y));

/*la función comp devuelve un número mayor, igual o menor
que cero, según x sea mayor, igual, o menor que y*/

/*
Como ejemplo, la función:
int strcmp(const char *str1, const char *str2) de la biblioteca estándar C
compara dos cadenas de caracteres apuntadas por str1 y str2.

El valor devuelto por esta función es:
    - menor que cero si str1 precede alfabéticamente a str2
    - mayor que cero si str2 precede alfabéticamente a str1
    - cero si ambas cadenas son iguales.
*/

void borrar(lista l, void *e,
            int (*comp)(const void *x, const void *y));

posicion primero(lista l);

posicion siguiente(posicion p);

int esfindelista(posicion p);

void *elemento(posicion p);

/* Para recorrer los elementos de la lista:
    for(p=primero(l); !esfindelista(p); p=siguiente(p)) {
        //hacer algo con elemento(p)
    }
*/

#endif //LISTAS_H
