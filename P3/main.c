// Creado por Pablo P. Pablo M. Maite G.

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <math.h>
#include <sys/time.h>
#include <time.h>

#include "tablas.h"

unsigned int ndispersion(char *clave, int tamTabla);

int leer_sinonimos(item datos[]);

void test_tabla(unsigned int (*resol_colisiones)(int pos_ini, int num_intento));

void test();

void tiempos();

void analizar(tabla_cerrada diccionario, item sinonimos[], int totalSinonimos,
              int sizeDiccionario, unsigned int (*dispersion)(char *, int),
              unsigned int (*resol_colisiones)(int pos_ini, int num_intento));

void print_cabecerat(unsigned int (*dispersion)(char *, int),
                     unsigned int (*resol_colisiones)(int pos_ini, int num_intento));

void print_fila(int n, double t);

double microsegundos();

int main(void) {
    printf("<--- Práctica de Pablos & Maite --->\n");
    printf("<--- TESTS --->\n");
    test();
    printf("<--- TIEMPOS --->\n");
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

void test_tabla(unsigned int (*resol_colisiones)(int pos_ini, int num_intento)) {
    tabla_cerrada tabla = malloc(11 * sizeof(entrada));
    char *claves[7] = {
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
                                 ndispersion, resol_colisiones);
        contadorcol += colis;
    }

    printf("{\n");
    mostrar_cerrada(tabla, 11);
    printf("}\n");
    printf("Número total de colisiones al insertar los elementos: %d\n\n",
           contadorcol);

    // BUSCAR TODOS LOS ELEMENTOS EN LA TABLA
    for (i = 0; i < 6 + 1; i++) {
        colis = 0;
        posicion = buscar_cerrada(claves[i], tabla, 11, &colis,
                                  ndispersion, resol_colisiones);
        if (tabla[posicion].ocupada)
            printf("Al buscar: %s, encuentro: %s, colisiones: %d",
                   claves[i], tabla[posicion].clave, colis);
        else printf("No encuentro: %s, colisiones: %d", claves[i], colis);
        printf("\n");
    }
    printf("\n");

    free(tabla);
}

void test() {
    printf("***TABLA CERRADA LINEAL\n");
    test_tabla(explora_lineal);
    printf("***TABLA CERRADA CUADRÁTICA\n");
    test_tabla(explora_cuadratica);
    // NOTA A TENER EN CUENTA EN ESTE TEST, HOLA PROFE SI ME LEES DURANTE LA DEFENSA
    // EN EL TEST DE LA TABLA CERRADA DOBLE SE UTILIZA UNA EXPLORACIÓN DOBLE CUYO
    // MÓDULO EN VEZ DE SER EL DADO POR LA PRÁCTICA (10007) USA 5 QUE ES EL DEL EJEMPLO
    // DE LAS TRANSPARENCIAS, ASI SE PUEDE COMPROBAR QUE ESTA BIEN IMPLEMENTADO :)
    printf("***TABLA CERRADA DOBLE\n");
    test_tabla(explora_doble_test_only);
}

void tiempos() {
    int totalSinonimos = 19062;
    int sizeDiccionario = 38197;
    tabla_cerrada diccionario = malloc(sizeDiccionario * sizeof(entrada));
    item sinonimos[totalSinonimos];
    leer_sinonimos(sinonimos);
    srand(time(NULL));

    analizar(diccionario, sinonimos, totalSinonimos, sizeDiccionario,
             dispersionA, explora_lineal);
    analizar(diccionario, sinonimos, totalSinonimos, sizeDiccionario,
             dispersionA, explora_cuadratica);
    analizar(diccionario, sinonimos, totalSinonimos, sizeDiccionario,
             dispersionA, explora_doble);
    analizar(diccionario, sinonimos, totalSinonimos, sizeDiccionario,
             dispersionB, explora_lineal);
    analizar(diccionario, sinonimos, totalSinonimos, sizeDiccionario,
             dispersionB, explora_cuadratica);
    analizar(diccionario, sinonimos, totalSinonimos, sizeDiccionario,
             dispersionB, explora_doble);

    free(diccionario);
}

void analizar(tabla_cerrada diccionario, item sinonimos[], int totalSinonimos,
              int sizeDiccionario, unsigned int (*dispersion)(char *, int),
              unsigned int (*resol_colisiones)(int pos_ini, int num_intento)) {
    int i, j, q, colis = 0, ran, otrascolis = 0;
    int valoresn[8] = {125, 250, 500, 1000, 2000, 4000, 8000, 16000};
    double inicio = 0, fin = 0, t = 0;

    print_cabecerat(dispersion, resol_colisiones);

    inicializar_cerrada(&diccionario, sizeDiccionario); // Inicializamos el diccionario

    printf("Insertando %d elementos... ", totalSinonimos);
    for (i = 0; i < totalSinonimos; i++)
        colis += insertar_cerrada(sinonimos[i].clave, sinonimos[i].sinonimos,
                                  &diccionario, sizeDiccionario, dispersion, resol_colisiones);
    printf("Número total de colisiones: %d\n", colis);

    printf("Buscando n elementos...\n        n             t(n)       "
        "t(n)/n^0.8           t(n)/n  t(n)/(n*log(n))\n");

    for (i = 0; i < sizeof valoresn / sizeof valoresn[0]; i++) {
        inicio = microsegundos();
        for (j = 0; j < valoresn[i]; j++) {
            ran = rand() % (totalSinonimos - 1);
            buscar_cerrada(sinonimos[ran].clave, diccionario, sizeDiccionario, &otrascolis, dispersion,
                           resol_colisiones);
        }
        fin = microsegundos();
        t = (fin - inicio);

        if (t < 500) {
            // VERSIÓN MEJORADA DE TIEMPOS PETIT
            inicio = microsegundos();
            for (j = 0; j < 1000; j++) {
                for (q = 0; q < valoresn[i]; q++) {
                    ran = rand() % (totalSinonimos - 1);
                    buscar_cerrada(sinonimos[ran].clave, diccionario, sizeDiccionario,
                                   &otrascolis, dispersion, resol_colisiones);
                }
            }
            fin = microsegundos();
            t = (fin - inicio) / 1000;
            printf("(*)");
        } else printf("   ");

        print_fila(valoresn[i], t);
    }

    printf("\n");
}

void print_cabecerat(unsigned int (*dispersion)(char *, int),
                     unsigned int (*resol_colisiones)(int pos_ini, int num_intento)) {
    if (resol_colisiones == explora_lineal)
        printf("***Dispersion cerrada lineal ");
    else if (resol_colisiones == explora_cuadratica)
        printf("***Dispersion cerrada cuadrática ");
    else if (resol_colisiones == explora_doble)
        printf("***Dispersion cerrada doble ");
    else printf("***Dispersión cerrada desconocida ");

    if (dispersion == dispersionA)
        printf("con dispersión A");
    else if (dispersion == dispersionB)
        printf("con dispersión B");
    else printf("con dispersion desconocida");

    printf("\n");
}

void print_fila(int n, double t) {
    double x, y, z;

    x = t / pow(n, 0.8);
    y = t / n;
    z = t / (n * log(n));

    printf("%6d%17.3f%17.6f%17.6f%17.6f\n", n, t, x, y, z);
}


double microsegundos() {
    struct timeval t;
    if (gettimeofday(&t,NULL) < 0) return 0.0;
    return (t.tv_usec + t.tv_sec * 1000000.0);
}
