# Creado por Pablo P. Pablo M. Maite G.

all: p4.o

run: p4.o
	./p4.o

file: p4.o
	./p4.o > tiempos.txt
	cat tiempos.txt

leaks: monticulos.c main.c
	gcc -Wall -g -O0 -c -o monticulos.o monticulos.c
	gcc -Wall -g -O0 -o p4.o main.c monticulos.o -lm
	valgrind --leak-check=full --show-reachable=yes ./p4.o

monticulos.o: monticulos.c
	gcc -Wall -c -o monticulos.o monticulos.c

p4.o: main.c monticulos.o
	gcc -Wall -o p4.o main.c monticulos.o -lm

clean: 
	rm -f *.o tiempos.txt
