# P3: Diccionario de datos (Hash Tables)

## Nota Original: 7.5

### Corrección

- [x] La función `n_busquedas` tiene dentro como "tara" el cálculo de un número random `ran = rand() % (totalSinonimos - 1);`
- [x] Esta línea genera números para todos los sinónimos menos el último `ran = rand() % (totalSinonimos - 1);` -> `ran = rand() % (totalSinonimos);`
- [x] En `tablas.c` la función `insertar_cerrada` debería llamar a la función búsqueda en vez de utilizar literalmente el mismo bucle.
- [x] El informe no tenía las cotas, y la constante de la ajustada no estaba bien declarada
- [ ] La conclusión no tenía sentido.
