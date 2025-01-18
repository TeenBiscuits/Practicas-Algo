# Prácticas Algoritmos 2024/25

Prácticas de la asignatura de Algoritmos, curso 2024/25, GEI-UDC. Por Pablo Portas López, Pablo Míguez Muiño y Maite González Vázquez.

---

>[!NOTE]
> Las prácticas cuentan con la nota original de cuando fueron evaluadas (por dejar constancia), pero **todas han sido corregidas** para el examen final de la asignatura.
>
> _PD: No te asustes si ves un 2._

- [P1: La sucesión de Fibonacci](/P1/)
- [P2: Ordenación por Inserción (Insertion Sort) y Ordenación Rápida (Quicksort)](/P2/)
- [P3: Diccionario de datos (Hash Tables)](/P3/)
- [P4: Montículos (Heapsort)](/P4/)

---

### Como ejecutar las prácticas

Hay un archivo ``CMakeLists.txt`` en todas las prácticas, ya que si el a CLion (en Windows y MacOS) le da la mala y no le apetece corregir archivos, "porque no forman parte del proyecto".

La forma correcta de ejecutar las prácticas es mediante el ``Makefile`` en un sistema **Unix**.

- Para solo **compilar** la práctica:
    ```bash
    make
    ```
- Para **compilar y ejecutar** la práctica:
    ```bash
    make run
    ```
- Para **compilar, ejecutar y crear el archivo `tiempos.txt`** con el _output_ de la práctica:
    ```bash
    make file
    ```
- Para **compilar y ejecutar** la práctica con [Valgrind](https://es.wikipedia.org/wiki/Valgrind) (comprobar memory leaks):
    ```bash
    make leaks
    ```
- Para **borrar** los ejecutables y `tiempos.txt` de la práctica:
    ```bash
    make clean
    ```

