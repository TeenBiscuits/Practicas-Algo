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

void test_t_lineal();

void test_t_cuadratica();

void test_t_doble();

void test();

void tiempos();

void realizar_busquedas(tabla_cerrada diccionario, item sinonimos[], int totalSinonimos, int sizeDiccionario,
                        unsigned int (*dispersion)(char *, int),
                        unsigned int (*resol_colisiones)(int, int), int n);

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

void test_t_cuadratica() {
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
                                 ndispersion, explora_cuadratica);
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
        posicion = buscar_cerrada(claves[i], tabla, 11, &colis, ndispersion, explora_cuadratica);
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
                                 ndispersion, explora_lineal);
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
        posicion = buscar_cerrada(claves[i], tabla, 11, &colis, ndispersion, explora_lineal);
        if (tabla[posicion].ocupada)
            printf("Al buscar: %s, encuentro: %s, colisiones: %d", claves[i], tabla[posicion].clave, colis);
        else printf("No encuentro: %s, colisiones: %d", claves[i], colis);
        printf("\n");
    }
    printf("\n");

    free(tabla);
}

void test_t_doble() {
    // NOTA A TENER EN CUENTA EN ESTE TEST, HOLA PROFE SI ME LEES DURANTE LA DEFENSA
    // EN EL TEST DE LA TABLA CERRADA DOBLE SE UTILIZA UNA EXPLORACIÓN DOBLE CUYO
    // MÓDULO EN VEZ DE SER EL DADO POR LA PRÁCTICA (10007) USA 5 QUE ES EL DEL EJEMPLO
    // DE LAS TRANSPARENCIAS, ASI SE PUEDE COMPROBAR QUE ESTA BIEN IMPLEMENTADO :)

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
                                 ndispersion, explora_doble_test_only);
        contadorcol += colis;
    }

    printf("***TABLA CERRADA DOBLE\n");
    printf("{\n");
    mostrar_cerrada(tabla, 11);
    printf("}\n");
    printf("Número total de colisiones al insertar los elementos: %d\n\n", contadorcol);

    // BUSCAR TODOS LOS ELEMENTOS EN LA TABLA
    for (i = 0; i < 6 + 1; i++) {
        colis = 0;
        posicion = buscar_cerrada(claves[i], tabla, 11, &colis, ndispersion, explora_doble_test_only);
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
    test_t_doble();
}

void tiempos() {
    int totalSinonimos = 19062;
    int sizeDiccionario = 38197;
    tabla_cerrada diccionario = malloc(sizeDiccionario * sizeof(entrada));
    item sinonimos[totalSinonimos];
    leer_sinonimos(sinonimos);

    // Inserción y conteo de colisiones
    inicializar_cerrada(&diccionario, sizeDiccionario);
    int totalColisiones = 0;
    for (int i = 0; i < totalSinonimos; i++) {
        totalColisiones += insertar_cerrada(sinonimos[i].clave, sinonimos[i].sinonimos, &diccionario, sizeDiccionario, dispersionB, explora_cuadratica);
    }
    printf("*** Dispersión cerrada cuadrática con dispersión B ***\n");
    printf("Insertando 19062 elementos... Número total de colisiones: %d\n", totalColisiones);

    // Imprimir encabezado de la tabla
    printf("Buscando n elementos...\n");
    printf("n       t(n)       t(n)/n^0.8   t(n)/n       t(n)/n*log(n)\n");

    // Realizar búsquedas para diferentes valores de n
    int tamanos[] = {125, 250, 500, 1000, 2000, 4000, 8000, 16000};
    int num_tamanos = sizeof(tamanos) / sizeof(tamanos[0]);
    for (int i = 0; i < num_tamanos; i++) {
        realizar_busquedas(diccionario, sinonimos, totalSinonimos, sizeDiccionario, dispersionB, explora_cuadratica, tamanos[i]);
    }

    free(diccionario);
}

void realizar_busquedas(tabla_cerrada diccionario, item sinonimos[], int totalSinonimos, int sizeDiccionario,
                        unsigned int (*dispersion)(char *, int),
                        unsigned int (*resol_colisiones)(int, int), int n) {
    int colisiones, posicion;
    double tiempoInicio, tiempoFin, tiempoTotal;
    int repeticiones = 1;

    do {
        tiempoInicio = microsegundos();

        // Realizar las búsquedas
        for (int r = 0; r < repeticiones; r++) {
            for (int i = 0; i < n; i++) {
                int indiceAleatorio = rand() % totalSinonimos; // Seleccionar clave aleatoria
                posicion = buscar_cerrada(sinonimos[indiceAleatorio].clave, diccionario, sizeDiccionario, &colisiones, dispersion, resol_colisiones);
            }
        }

        tiempoFin = microsegundos();
        tiempoTotal = (tiempoFin - tiempoInicio) / repeticiones;

        if (tiempoTotal < 500) {
            repeticiones *= 10;
        }
    } while (tiempoTotal < 500);

    double cociente_n_08 = tiempoTotal / pow(n, 0.8);
    double cociente_n = tiempoTotal / n;
    double cociente_n_log_n = tiempoTotal / (n * log(n));

    printf("%-8d %-10.3f %-10.5f %-10.5f %-10.5f\n", n, tiempoTotal, cociente_n_08, cociente_n, cociente_n_log_n);
}

double microsegundos() {
    struct timeval t;
    if (gettimeofday(&t,NULL) < 0) return 0.0;
    return (t.tv_usec + t.tv_sec * 1000000.0);
}
