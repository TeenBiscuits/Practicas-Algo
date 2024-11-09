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

#ifndef DISP_H
#define DISP_H


#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define LONGITUD_CLAVE 30
#define LONGITUD_SINONIMOS 300
#define MIN(X,Y) ((X) < (Y) ? (X) : (Y))

typedef struct entrada_ {
	int ocupada;
	char clave [LONGITUD_CLAVE];
	char sinonimos [LONGITUD_SINONIMOS];
} entrada;
typedef int colisiones;
typedef int pos;

typedef struct {
	char clave [LONGITUD_CLAVE];
	char sinonimos [LONGITUD_SINONIMOS];
} item;

typedef entrada *tabla_cerrada;

int dispersionA(char *, int);
int dispersionB(char *, int);
int leer_sinonimos(item[]);


#endif
