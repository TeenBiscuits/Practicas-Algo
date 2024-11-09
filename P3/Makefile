# Creado por Pablo P. Pablo M. Maite G.

all: p3.o

run: p3.o
	./p3.o

file: p3.o
	./p3.o > tiempos.txt
	cat tiempos.txt

leaks:
	gcc -Wall -g -O0 -c -o tablas.o tablas.c -lm
	gcc -Wall -g -O0 -o  p3.o main.c tablas.o -lm
	valgrind --leak-check=full --show-reachable=yes ./p3.o

p3.o: main.c tablas.o
	gcc -Wall -o p3.o main.c tablas.o -lm

tablas.o: tablas.c
	gcc -Wall -c -o tablas.o tablas.c -lm

clean: 
	rm -f *.o tiempos.txt
