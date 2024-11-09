/**********************************************************************

Copyleft (C) 2017  Álex Velo Santórum y Caetán Tojeiro Carpente

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU Affero General Public License as published by
the Free Software Foundation, either version 3 of the License, or
any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <https://www.gnu.org/licenses/agpl-3.0.html>

**********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "disp_cerrada.h"
#include "disp_cerrada.c"
#include <sys/time.h>
#include <time.h>
#include <math.h>

void inicializar_semilla () {
	srand(time(NULL));
}

double microsegundos (){
	struct timeval t;
	if (gettimeofday(&t, NULL) < 0 )
		return 0.0;
	return (t.tv_usec + t.tv_sec * 1000000.0);
}

void inicializar_cerrada (tabla_cerrada *diccionario, int TAM) {
	int i = 0;
	for(i=0; i<TAM; i++){
		(*diccionario)[i].ocupada = 0;	
	}
}

int rc_cuadratica (int posicion_inicial, int num_intentos) {
	int posAct;
	posAct = posicion_inicial + (num_intentos*num_intentos);
	return posAct;
}

int rc_lineal (int posicion_inicial, int num_intentos) {
	int posAct;
	posAct = posicion_inicial + num_intentos;
	return posAct;
}


pos buscar_cerrada (char *clave, tabla_cerrada diccionario, int TAM,
	int (*dispersion)(char *, int),
	int (*resolucion_colisiones)(int pos_inicial, int num_intento)){
		
	int i = 0;
	int x = dispersion(clave, TAM);
	int posAct = x;
	
	while (diccionario[posAct].ocupada && 
	strcmp(diccionario[posAct].clave, clave)){
		i++;
		posAct = (*resolucion_colisiones)(x,i) % TAM;
	}
	return posAct;	
}


colisiones insertar_cerrada (char *clave, char *sinonimos,
	tabla_cerrada *diccionario, int TAM,
	int (*dispersion)(char *, int),
	int (*resolucion_colisiones)(int pos_inicial, int num_intento)){

	int i = 0;
	int x = dispersion(clave, TAM);
	int posAct = x;
	
	while ((*diccionario)[posAct].ocupada && 
	strcmp((*diccionario)[posAct].clave, clave)){
		i++;
		posAct = (*resolucion_colisiones)(x,i) % TAM;
	}

	if(!((*diccionario)[posAct].ocupada)) {
		strcpy((*diccionario)[posAct].clave, clave);
		strcpy((*diccionario)[posAct].sinonimos, sinonimos);
		(*diccionario)[posAct].ocupada = 1;
	}
	return (colisiones) i;
}

void mostrar_cerrada (tabla_cerrada diccionario, int TAM){
	int i = 0;
	
	for (i = 0; i < TAM; i++){
		printf("%2d-", i);
		if (diccionario[i].ocupada) 
			printf("(%s)", diccionario[i].clave);
		printf("\n");
	}
}

int ndispersion(char *clave, int tamTabla) {
	if (strcmp(clave, "ANA")==0) return 7;
	if (strcmp(clave, "JOSE")==0) return 7;
	if (strcmp(clave, "OLGA")==0) return 7;
	return 6;
}

void test_lineal(){
	tabla_cerrada d = malloc (11 * sizeof(entrada));
	char claves [][7] = {"ANA", "LUIS", "JOSE", "OLGA", "ROSA", 
	"IVAN", "CARLOS"};
	int i = 0;
	item elem;
	int posicion;
	int col;
	int aux = 0;

	inicializar_cerrada(&d, 11);
	for (i = 0;i < 6; i++){
		strcpy(elem.clave, claves[i]);
		strcpy(elem.sinonimos, "");
		col = insertar_cerrada(elem.clave, elem.sinonimos, &d, 11, 
		ndispersion, rc_lineal);
		aux = aux + col;
	}
	printf("Tabla cerrada lineal\n");
	printf("{\n");
	mostrar_cerrada(d, 11);
	printf("}\n");
	printf(" numero total de colisiones: %d\n\n", aux);
	for (i = 0; i < 6 + 1; i++){
		posicion = buscar_cerrada(claves[i], d, 11, ndispersion, 
		rc_lineal);
		if (d[posicion].ocupada)
			printf("Al buscar: %s, encontro: %s", claves[i], 
			d[posicion].clave);
		else printf("No encontro: %s", claves[i]);
		printf("\n");
	}
	printf("\n");
	free(d);
}

void test_cuadratica(){
	tabla_cerrada d = malloc (11 * sizeof(entrada));
	char claves [][7] = {"ANA", "LUIS", "JOSE", "OLGA", "ROSA", 
	"IVAN", "CARLOS"};
	int i = 0;
	item elem;
	int posicion;
	int col;
	int aux = 0;

	inicializar_cerrada(&d, 11);

	for (i = 0;i < 6; i++){
		strcpy(elem.clave, claves[i]);
		strcpy(elem.sinonimos, "");
		col = insertar_cerrada(elem.clave, elem.sinonimos, &d, 11, 
		ndispersion, rc_cuadratica);
		aux = col + aux;
	}

	printf("Tabla cerrada cuadratica\n");
	printf("{\n");
	mostrar_cerrada(d, 11);
	printf("}\n");

	printf(" numero total de colisiones: %d\n\n", aux);
	
	for (i = 0; i < 6 + 1; i++){
		posicion = buscar_cerrada(claves[i], d, 11, ndispersion, 
		rc_cuadratica);
		if (d[posicion].ocupada)
			printf("Al buscar: %s, encontro: %s", claves[i], 
			d[posicion].clave);
		else printf("No encontro: %s", claves[i]);
		printf("\n");
	}
	printf("\n");

	free(d);
}

void pintarCabeceras(int (*dispersion)(char *, int), 
int (*resolucion_colisiones)(int pos_inicial, int num_intento), 
int colisiones, int TAM){ 
	
	if((resolucion_colisiones == rc_lineal) && 
	(dispersion == dispersionA))
		printf("***Dispersion cerrada lineal con dispersionA \n");
	if((resolucion_colisiones == rc_cuadratica) && 
	(dispersion == dispersionA))
		printf("***Dispersion cerrada cuadratica con dispersionA \n");
	if((resolucion_colisiones == rc_lineal) && 
	(dispersion == dispersionB))
		printf("***Dispersion cerrada lineal con dispersionB \n");
	if((resolucion_colisiones == rc_cuadratica) && 
	(dispersion == dispersionB))
		printf("***Dispersion cerrada cuadratica con dispersionB \n");
    printf("  Insertando %d elementos... ", TAM);
    printf("  Numero de colisions: %d\n", colisiones);
    printf("  Buscando n elementos...\n\n");
	if((resolucion_colisiones == rc_lineal) && 
	(dispersion == dispersionA)){
		printf("%10s%15s%18s%13s%22s\n\n", "n", "t(n)", "t(n)/n^0.8", 
		"t(n)/n", "t(n)/(n*(log(n)))");
	}
	if((resolucion_colisiones == rc_cuadratica) && 
	(dispersion == dispersionA)){
		printf("%10s%15s%18s%13s%22s\n\n", "n", "t(n)", "t(n)/n^0.9", 
		"t(n)/n", "t(n)/n^1.1");
	}
	if((resolucion_colisiones == rc_lineal) && 
	(dispersion == dispersionB)){
		printf("%10s%15s%18s%13s%22s\n\n", "n", "t(n)", "t(n)/n^0.7", 
		"t(n)/n^0.9", "t(n)/(n*(log(n)))");
	}
	if((resolucion_colisiones == rc_cuadratica) && 
	(dispersion == dispersionB)){
		printf("%10s%15s%18s%13s%22s\n\n", "n", "t(n)", "t(n)/n^0.8", 
		"t(n)/n^0.9", "t(n)/(n*(log(n)))");
	}
}

void pintarTiempos(int (*dispersion)(char *, int), 
int (*resolucion_colisiones)(int pos_inicial, int num_intento), 
double t, int n, int umbral){
	
	double sub, sobre, ajust;
	
	if((resolucion_colisiones == rc_lineal) && 
	(dispersion == dispersionA)){
		sub = t / pow(n, 0.8);
		ajust = t / pow(n, 1.0);
		sobre = t / (n*log(n));
	}
	if((resolucion_colisiones == rc_cuadratica) && 
	(dispersion == dispersionA)){
		sub = t / pow(n, 0.9);
		ajust = t / pow(n, 1.0);
		sobre = t / pow(n, 1.1);
	}
	if((resolucion_colisiones == rc_lineal) && 
	(dispersion == dispersionB)){
		sub = t / pow(n, 0.7);
		ajust = t / pow(n, 0.9);
		sobre = t / (n*log(n));
	}
	if((resolucion_colisiones == rc_cuadratica) && 
	(dispersion == dispersionB)){
		sub = t / pow(n, 0.8);
		ajust = t / pow(n, 0.9);
		sobre = t / (n*log(n));
	}
	
	printf("%10d%15.3f", n, t);
	if (umbral == 1) printf("%2s", "*");
	else printf("%2s", " ");
	printf("%15.9f%15.9f%15.9f\n", sub, ajust, sobre);
}

void tiempoEj (tabla_cerrada *d, item *datos, int TAM, int tamTabla, 
int (*dispersion)(char *, int), 
int (*resolucion_colisiones)(int pos_inicial, int num_intento)) {
    double  t, tan, tdes;
    int i, j, n, umbral;
	int col = 0;
	int aux = 0;
	int ran = 0;
	for(i = 0; i<TAM; i++){
		col = insertar_cerrada(datos[i].clave, datos[i].sinonimos, d, 
		tamTabla, dispersion, resolucion_colisiones);
		aux = col + aux;
    }
    pintarCabeceras(dispersion, resolucion_colisiones, aux, TAM);	 
    for (n = 125;n <= 8000;n *= 2){
        umbral = 0;
        tan = microsegundos();       
        for (j = 0;j < n;j++){
			ran = rand() % (TAM - 1);
            buscar_cerrada(datos[ran].clave, *d, tamTabla, dispersion, 
            resolucion_colisiones);
        }
        tdes = microsegundos();
        t = tdes - tan;
        if (t < 500) {
            umbral = 1;
            tan = microsegundos();
            for (i = 0;i < 1000;i++){
                for (j = 0; j < n;j++){
					ran = rand() % (TAM - 1);
                    buscar_cerrada(datos[ran].clave, *d, tamTabla, 
                    dispersion, resolucion_colisiones);
                 }
            }
            tdes = microsegundos();
            t = (tdes - tan)/1000;
        }
		pintarTiempos(dispersion, resolucion_colisiones, t, n, umbral);
    }
    printf("\n");
}

int main(){

	tabla_cerrada d = malloc (38197 * sizeof(entrada));
	item datos[19062];
	
	test_lineal();
	test_cuadratica();
	inicializar_semilla();
	leer_sinonimos(datos);
	inicializar_cerrada(&d, 38197);
	tiempoEj(&d, datos, 19062, 38197, dispersionA, rc_lineal);
	inicializar_cerrada(&d, 38197);
	tiempoEj(&d, datos, 19062, 38197, dispersionA, rc_cuadratica);
	inicializar_cerrada(&d, 38197);
	tiempoEj(&d, datos, 19062, 38197,dispersionB, rc_lineal);
	inicializar_cerrada(&d, 38197);
	tiempoEj(&d, datos, 19062, 38197,dispersionB, rc_cuadratica);
	free(d);
	return 0;
	
}
