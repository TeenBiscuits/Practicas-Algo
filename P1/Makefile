# Creado por Pablo P. Pablo M. Maite G.

all: p1.o

run: p1.o
	./p1.o

file: p1.o
	./p1.o > tiempos.txt
	cat tiempos.txt

leaks:
	gcc -Wall -g -O0 -o p1.o main.c -lm
	valgrind --leak-check=full --show-reachable=yes ./p1.o

p1.o: main.c
	gcc -Wall -o p1.o main.c -lm

clean: 
	rm -f *.o tiempos.txt
