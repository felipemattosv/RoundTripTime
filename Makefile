all: main

main: main.c
	gcc -o main *.c

clean:
	rm -rf *.o main