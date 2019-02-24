build: tema2

tema2: tema2.o
	gcc -o  tema2 tema2.o

tema2.o: tema2.c
	gcc -Wall -c -o tema2.o tema2.c

run:
	./tema2 

clean:
	rm -f tema2 tema2.o
