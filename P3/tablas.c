// Creado por Pablo P. Pablo M. Maite G.

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <math.h>

#include "tablas.h"

unsigned int dispersionA(char *clave, int tamTabla) {
    int i, n = MIN(8, strlen(clave)));
    unsigned int valor = clave[0];
    for (i = 1; i < n; i++) {
        valor += clave[i];
    }
    return valor % tamTabla;
}

unsigned int dispersionB(char *clave, int tamTabla) {
    int i, n = MIN(8, strlen(clave)));
    unsigned int valor = clave[0];
    for (i = 1; i < n; i++) {
        valor = (valor << 5) + clave[i];
    }
    return valor % tamTabla;
}

void inicializar_cerrada(tabla_cerrada *diccionario, int tam) {
    int i = 0;
    // Se recorre toda la "tabla" marcando cada elemento como no ocupado
    for (i = 0; i < tam; i++) {
        (*diccionario)[i].ocupada = 0;
    }
}

pos buscar_cerrada(char *clave, tabla_cerrada diccionario, int tam, int *colisiones,
                   unsigned int (*dispersion)(char *, int),
                   unsigned int (*resol_colisiones)(int pos_ini, int num_intento)) {
    int i = 0;
    int x = dispersion(clave, tam);
    int posAct = x;

    while (diccionario[posAct].ocupada &&
           strcmp(diccionario[posAct].clave, clave)) {
        i++;
        posAct = resol_colisiones(x, i) % tam;
    }
    *colisiones = i;
    return posAct;
}

int insertar_cerrada(char *clave, char *sinonimos, tabla_cerrada *diccionario, int tam,
                     unsigned int (*dispersion)(char *, int),
                     unsigned int (*resol_colisiones)(int pos_ini, int num_intento)) {
    int i = 0;
    int x = dispersion(clave, tam);
    int posAct = x;

    while ((*diccionario)[posAct].ocupada &&
           strcmp((*diccionario)[posAct].clave, clave)) {
        i++;
        posAct = resol_colisiones(x, i) % tam;
    }

    if (!((*diccionario)[posAct].ocupada)) {
        strcpy((*diccionario)[posAct].clave, clave);
        strcpy((*diccionario)[posAct].sinonimos, sinonimos);
        (*diccionario)[posAct].ocupada = 1;
    }
    return i;
}

void mostrar_cerrada(tabla_cerrada diccionario, int tam) {
    int i = 0;

    for (i = 0; i < tam; i++) {
        printf("%2d - ", i);
        if (diccionario[i].ocupada)
            printf("(%s)", diccionario[i].clave);
        printf("\n");
    }
}

unsigned int explora_lineal(int pos_ini, int num_intentos) {
    int posAct;
    posAct = pos_ini + num_intentos;
    return posAct;
}

unsigned int explora_cuadratica(int pos_ini, int num_intentos) {
    int posAct;
    posAct = pos_ini + powf(num_intentos, 2);
    return posAct;
}

unsigned int explora_doble(int pos_ini, int num_intentos) {
    int posAct;
    posAct = pos_ini + (10007 - pos_ini % 10007) * num_intentos;
    return posAct;
}

unsigned int explora_doble_test_only(int pos_ini, int num_intentos) {
    int posAct;
    posAct = pos_ini + (5 - pos_ini % 5) * num_intentos;
    return posAct;
}
