// Creado por Pablo P. Pablo M. Maite G.

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

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
}

int insertar_cerrada(char *clave, char *sinonimos, tabla_cerrada *diccionario, int tam,
                     unsigned int (*dispersion)(char *, int),
                     unsigned int (*resol_colisiones)(int pos_ini, int num_intento)) {
}

void mostrar_cerrada(tabla_cerrada diccionario, int tam) {
    int i = 0;

    for (i = 0; i < tam; i++) {
        printf("%2d-", i);
        if (diccionario[i].ocupada)
            printf("(%s)", diccionario[i].clave);
        printf("\n");
    }
}
