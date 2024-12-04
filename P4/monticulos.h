// Creado por Pablo P. Pablo M. Maite G.

#ifndef MONTICULOS_H
#define MONTICULOS_H

#define TAM 256000

struct monticulo {
    int ultimo;
    int vector[TAM];
};

typedef struct monticulo *pmonticulo;

void iniMonticulo(pmonticulo m);

void insertarMonticulo(pmonticulo m, int x);

void quitarMenor(pmonticulo m);

int consultarMenor(const pmonticulo m);

void crearMonticulo(pmonticulo m, int v[], int n);

void flotar(pmonticulo m, int i);

void hundir(pmonticulo m, int i);

#endif //MONTICULOS_H
