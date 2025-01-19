# Creado por Pablo P. Pablo M. Maite G.

all: p2.o

run: p2.o
	./p2.o

file: p2.o
	./p2.o > tiempos.txt
	cat tiempos.txt

leaks:
	gcc -Wall -g -O0 -c -o p2.o ordenar.o ordenar.c
	gcc -Wall -g -O0 -o p2.o main.c ordenar.o -lm
	valgrind --leak-check=full --show-reachable=yes ./p2.o

p2.o: main.c ordenar.o
	gcc -Wall -o p2.o main.c ordenar.o -lm

ordenar.o: ordenar.c
	gcc -Wall -c -o ordenar.o ordenar.c

clean: 
	rm -f *.o tiempos.txt
