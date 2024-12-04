# Creado por Pablo P. Pablo M. Maite G.

all: p4.o

run: p4.o
	./p4.o

file: p4.o
	./p4.o > tiempos.txt
	cat tiempos.txt

leaks:
	gcc -Wall -g -O0 -o  p4.o main.c -lm
	valgrind --leak-check=full --show-reachable=yes ./p4.o

p4.o: main.c
	gcc -Wall -o p4.o main.c -lm

clean: 
	rm -f *.o tiempos.txt
