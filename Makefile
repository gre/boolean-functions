.PHONY: clean

DEBUG = -Wall -g
OPT = ${DEBUG}

all: clean main

utils.o : utils.c utils.h
	gcc -c utils.c -o $@ $(OPT)

interpreter.o : interpreter.c interpreter.h
	gcc -c interpreter.c -o $@ $(OPT)

parser.o : parser.c parser.h
	gcc -c parser.c -o $@ $(OPT)

ui.o : ui.c ui.h
	gcc -c ui.c -o $@ $(OPT)
	

main: main.c globals.h interpreter.o ui.o parser.o
	gcc main.c ui.o interpreter.o parser.o -o $@ $(OPT)

clean:
	rm -f *.o

