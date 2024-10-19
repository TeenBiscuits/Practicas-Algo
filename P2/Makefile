all: main.out
	rm tiempos.txt
	./main.out
	cat tiempos.txt

main.out: main.c
	gcc -Wall -o main.out main.c -lm

clean: 
	rm -f *.out tiempos.txt
