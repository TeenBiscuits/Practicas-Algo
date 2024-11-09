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

void test_t_doble();

void test();

void tiempos();

void analizar();

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

    // Inicializo un diccionario, calculo los tiempos, sobreescribo el diccionario, repito y finalmente libero memoria

    /*
    inicializar_cerrada(&diccionario, sizeDiccionario);
    analizar(&diccionario, sinonimos, totalSinonimos, sizeDiccionario, dispersionA, explora_lineal);
    inicializar_cerrada(&diccionario, sizeDiccionario);
    analizar(&diccionario, sinonimos, totalSinonimos, sizeDiccionario, dispersionA, explora_cuadratica);
    inicializar_cerrada(&diccionario, sizeDiccionario);
    analizar(&diccionario, sinonimos, totalSinonimos, sizeDiccionario, dispersionA, explora_doble);
    inicializar_cerrada(&diccionario, sizeDiccionario);
    analizar(&diccionario, sinonimos, totalSinonimos, sizeDiccionario, dispersionB, explora_lineal);
    inicializar_cerrada(&diccionario, sizeDiccionario);
    analizar(&diccionario, sinonimos, totalSinonimos, sizeDiccionario, dispersionB, explora_cuadratica);
    inicializar_cerrada(&diccionario, sizeDiccionario);
    analizar(&diccionario, sinonimos, totalSinonimos, sizeDiccionario, dispersionA, explora_doble);
    */

    free(diccionario);
}

void realizar_busquedas_aleatorias(tabla_cerrada diccionario, item sinonimos[], int totalSinonimos, int sizeDiccionario){
    int numBusquedas = 10;
    int colisiones, posicion;

    srand(time(NULL));
    printf("Resultados de las busquedas aleatorias:\n");
    for (int i = 0; i < numBusquedas; i++) {
        int indiceAleatorio = rand() % totalSinonimos; // Índice aleatorio en el rango de sinonimos

        colisiones = 0;
        posicion = buscar_cerrada(sinonimos[indiceAleatorio].clave, diccionario, sizeDiccionario, &colisiones, dispersionA, explora_lineal);

        if (diccionario[posicion].ocupada) {
            printf("Búsqueda de %s: encontrado con %d colisiones\n", sinonimos[indiceAleatorio].clave, colisiones);
        } else {
            printf("Búsqueda de %s: no encontrado, colisiones: %d\n", sinonimos[indiceAleatorio].clave, colisiones);
        }
    }
}

void analizar(tabla_cerrada *diccionario, item sinonimos[],int totalSinonimos, int sizeDiccionario,
              unsigned int (*dispersion) (char *, int),
              unsigned int (*resol_colisiones) (int, int)){
    int i, colisiones, totalColisiones = 0, repeticiones = 1;
    double tiempoInicio, tiempoFin, tiempoTotal;

    do{
        totalColisiones = 0; //inicializo ocntador de colisiones y tiempo
        tiempoInicio = microsegundos();

        for (i = 0; i < totalSinonimos; i++) { //inserto cada sinónimo en la tabla y cuenta colisiones
            colisiones = insertar_cerrada(sinonimos[i].clave, sinonimos[i].sinonimos,
                                          diccionario, sizeDiccionario, dispersion, resol_colisiones);
            totalColisiones += colisiones;
        }

        //Calculo tiempo total para las repeticiones actuales
        tiempoFin = microsegundos();
        tiempoTotal = (tiempoFin-tiempoInicio)/repeticiones;

        if(tiempoTotal<500){
        repeticiones *=10;//Aumenta las repeticiones para obtener un tiempo mayor
        }
    } while (tiempoTotal<500); //Repite si el tiempo e menor a 500 microsegundos
    printf("Función de dispersión: %s, Método de exploración: %s\n",
           "dispersionA", "exploracion_lineal"); // Ajusta según la combinación
    printf("Tiempo promedio de inserción: %f microsegundos\n", tiempoTotal);
    printf("Número total de colisiones: %d\n\n", totalColisiones);


}

double microsegundos() {
    struct timeval t;
    if (gettimeofday(&t,NULL) < 0) return 0.0;
    return (t.tv_usec + t.tv_sec * 1000000.0);
}
