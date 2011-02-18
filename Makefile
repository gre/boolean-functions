.PHONY: clean

DEBUG = -Wall -g
OPT = ${DEBUG}

all: clean main

utils.o : utils.c utils.h
	gcc -c utils.c -o $@ $(OPT)


parser/parser.tab.o:
	cd parser; make

interpreter.o : interpreter.c interpreter.h
	gcc -c interpreter.c -o $@ $(OPT)

parser.o : parser.c parser.h parser/parser.tab.o
	gcc -c parser.c -o $@ $(OPT)

ui.o : ui.c ui.h
	gcc -c ui.c -o $@ $(OPT)

main: main.c globals.h interpreter.o ui.o parser.o utils.o parser/parser.tab.o 
	gcc main.c ui.o parser/parser.tab.o interpreter.o parser.o utils.o -o $@ $(OPT)

clean:
	rm -f *.o

