# P3: Diccionario de datos

## Nota: 7.5

### Corrección

- La función `n_busquedas` tiene dentro como "tara" el cálculo de un número random `ran = rand() % (totalSinonimos - 1);`
- Esta línea genera números para todos los sinónimos menos el último `ran = rand() % (totalSinonimos - 1);` -> `ran = rand() % (totalSinonimos);`
- En `tablas.c` la función `insertar_cerrada` debería llamar a la función búsqueda en vez de utilizar literalmente el mismo bucle.
- El informe no tenía las cotas, y la constante de la ajustada no estaba bien declarada
- La conclusión no tenía sentido.


