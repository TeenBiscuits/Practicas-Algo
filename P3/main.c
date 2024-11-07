// Creado por Pablo P. Pablo M. Maite G.

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/time.h>

#include "tablas.h"

unsigned int ndispersion(char *clave, int tamTabla);

int leer_sinonimos(item datos[]);

void test_t_lineal();

void test_t_cuadratica();

void test();

void tiempos();

double microsegundos();

int main(void) {
    printf("<--- Práctica de Pablos & Maite --->\n");
    test();
    tiempos();
    return 0;
}

unsigned int ndispersion(char *clave, int tamTabla) {
    if (strcmp(clave, "ANA") == 0) return 7;
    if (strcmp(clave, "JOSE") == 0) return 7;
    if (strcmp(clave, "OLGA") == 0) return 7;
    return 6;
}

int leer_sinonimos(item datos[]) {
    char c;
    int i, j;
    FILE *archivo;
    if ((archivo = fopen("sinonimos.txt", "r")) == NULL) {
        printf("Error al abrir ’sinonimos.txt’\n");
        return (EXIT_FAILURE);
    }
    for (i = 0; fscanf(archivo, "%s", datos[i].clave) != EOF; i++) {
        if ((c = fgetc(archivo)) != '\t') {
            printf("Error al leer el tabulador\n");
            return (EXIT_FAILURE);
        }
        for (j = 0; (c = fgetc(archivo)) != '\n'; j++) {
            if (j < LONGITUD_SINONIMOS - 1)
                datos[i].sinonimos[j] = c;
        }
        datos[i].sinonimos[MIN(j, (LONGITUD_SINONIMOS - 1)))] = '\0';
    }
    if (fclose(archivo) != 0) {
        printf("Error al cerrar el fichero\n");
        return (EXIT_FAILURE);
    }
    return (i);
}

void test_t_cuadratica() {
    tabla_cerrada tabla = malloc(11 * sizeof(entrada));
    char claves[][7] = {
        "ANA", "LUIS", "JOSE", "OLGA", "ROSA",
        "IVAN", "CARLOS"
    };
    int i = 0;
    item elem;
    pos posicion;
    int colis;
    int contadorcol = 0;

    inicializar_cerrada(&tabla, 11);

    // INSERTAR LOS ELEMENTOS EN LA TABLA ( MENOS A CARLOS :( )
    for (i = 0; i < 6; i++) {
        strcpy(elem.clave, claves[i]);
        strcpy(elem.sinonimos, "");
        colis = insertar_cerrada(elem.clave, elem.sinonimos, &tabla, 11,
                                 ndispersion, resol_cuadratica);
        contadorcol += colis;
    }

    printf("***TABLA CERRADA CUADRÁTICA\n");
    printf("{\n");
    mostrar_cerrada(tabla, 11);
    printf("}\n");
    printf("Numero total de colisiones al insertar los elementos: %d\n\n", contadorcol);
    // BUSCAR TODOS LOS ELEMENTOS EN LA TABLA
    for (i = 0; i < 6 + 1; i++) {
        colis = 0;
        posicion = buscar_cerrada(claves[i], tabla, 11, &colis, ndispersion, resol_cuadratica);
        if (tabla[posicion].ocupada)
            printf("Al buscar: %s, encuentro: %s, colisiones: %d", claves[i], tabla[posicion].clave, colis);
        else printf("No encuentro: %s, colisiones: %d", claves[i], colis);
        printf("\n");
    }
    printf("\n");

    free(tabla);
}

void test_t_lineal() {
    tabla_cerrada tabla = malloc(11 * sizeof(entrada));
    char claves[][7] = {
        "ANA", "LUIS", "JOSE", "OLGA", "ROSA",
        "IVAN", "CARLOS"
    };
    int i = 0;
    item elem;
    pos posicion;
    int colis;
    int contadorcol = 0;

    inicializar_cerrada(&tabla, 11);

    // INSERTAR LOS ELEMENTOS EN LA TABLA ( MENOS A CARLOS :( )
    for (i = 0; i < 6; i++) {
        strcpy(elem.clave, claves[i]);
        strcpy(elem.sinonimos, "");
        colis = insertar_cerrada(elem.clave, elem.sinonimos, &tabla, 11,
                                 ndispersion, resol_lineal);
        contadorcol += colis;
    }

    printf("***TABLA CERRADA LINEAL\n");
    printf("{\n");
    mostrar_cerrada(tabla, 11);
    printf("}\n");
    printf("Numero total de colisiones al insertar los elementos: %d\n\n", contadorcol);
    // BUSCAR TODOS LOS ELEMENTOS EN LA TABLA
    for (i = 0; i < 6 + 1; i++) {
        colis = 0;
        posicion = buscar_cerrada(claves[i], tabla, 11, &colis, ndispersion, resol_lineal);
        if (tabla[posicion].ocupada)
            printf("Al buscar: %s, encuentro: %s, colisiones: %d", claves[i], tabla[posicion].clave, colis);
        else printf("No encuentro: %s, colisiones: %d", claves[i], colis);
        printf("\n");
    }
    printf("\n");

    free(tabla);
}

void test() {
    test_t_lineal();
    test_t_cuadratica();
}

void tiempos() {
    item sinonimos[19062];
    leer_sinonimos(sinonimos);
}

double microsegundos() {
    struct timeval t;
    if (gettimeofday(&t,NULL) < 0) return 0.0;
    return (t.tv_usec + t.tv_sec * 1000000.0);
}
