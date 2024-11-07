# Creado por Pablo P. Pablo M. Maite G.

all: main.o

run: main.o
	rm tiempos.txt
	./main.out > tiempos.txt
	cat tiempos.txt

main.o: main.c tablas.c
	gcc -Wall -o main.o main.c tablas.o -lm

tablas.o: tablas.c
	gcc -Wall -o tablas.o tablas.c -lm

clean: 
	rm -f *.o tiempos.txt
