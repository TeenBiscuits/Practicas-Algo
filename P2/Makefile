all: main.out
	./main.out
	#cat tiempos.txt

main.out: main.c
	gcc -Wall -o main.out main.c -lm

clean: 
	rm -f *.out # tiempos.txt
