# Creado por Pablo P.

all: main.o

pilas.o: pilas.c
	gcc -Wall -c -o pilas.o pilas.c

colas.o: colas.c
	gcc -Wall -c -o colas.o colas.c

listas.o: listas.c
	gcc -Wall -c -o listas.o listas.c

main.o: main.c pilas.o colas.o listas.o
	gcc -Wall -o main.o main.c

clean:
	rm -f *.o
