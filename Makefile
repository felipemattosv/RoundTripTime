all: trab2

trab2: main.c
	gcc -o trab2 *.c

clean:
	rm -rf *.o trab2
