// Creado por Pablo P. Pablo M. Maite G.

#ifndef TABLAS_H
#define TABLAS_H

#define MIN(X,Y) ((X) < (Y) ? (X) : (Y)
#define LONGITUD_CLAVE 30
#define LONGITUD_SINONIMOS 300

typedef struct entrada_ {
    int ocupada;
    char clave[LONGITUD_CLAVE];
    char sinonimos[LONGITUD_SINONIMOS];
} entrada;

typedef struct {
    char clave[LONGITUD_CLAVE];
    char sinonimos[LONGITUD_SINONIMOS];
} item;

typedef int pos;
typedef entrada *tabla_cerrada;
//tabla_cerrada d = malloc (38197 * sizeof(entrada));

unsigned int dispersionA(char *clave, int tamTabla);

unsigned int dispersionB(char *clave, int tamTabla);

void inicializar_cerrada(tabla_cerrada *diccionario, int tam);

pos buscar_cerrada(char *clave, tabla_cerrada diccionario, int tam, int *colisiones,
                   unsigned int (*dispersion)(char *, int),
                   unsigned int (*resol_colisiones)(int pos_ini, int num_intento));

int insertar_cerrada(char *clave, char *sinonimos, tabla_cerrada *diccionario, int tam,
                     unsigned int (*dispersion)(char *, int),
                     unsigned int (*resol_colisiones)(int pos_ini, int num_intento));

void mostrar_cerrada(tabla_cerrada diccionario, int tam);

unsigned int explora_lineal(int pos_ini, int num_intentos);

unsigned int explora_cuadratica(int pos_ini, int num_intentos);

unsigned int explora_doble(int pos_ini, int num_intentos);

unsigned int explora_doble_test_only(int pos_ini, int num_intentos);

#endif //TABLAS_H
