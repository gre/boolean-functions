.PHONY: clean

DEBUG = -Wall -g -DDEBUG
OPT = ${DEBUG}

all: clean main

utils.o : utils.c utils.h
	gcc -c utils.c -o $@ $(OPT)

parser/parser.tab.o:
	cd parser; make

function.o: function.c function.h
	gcc -c function.c -o $@ $(OPT)

ftree.o: ftree.c ftree.h
	gcc -c ftree.c -o $@ $(OPT)

interpreter.o : interpreter.c interpreter.h function.o ftree.o btable.o parser/parser.tab.o
	gcc -c interpreter.c -o $@ $(OPT)

ui.o : ui.c ui.h
	gcc -c ui.c -o $@ $(OPT)

main: main.c globals.h function.o ftree.o btree.o btable.o interpreter.o ui.o utils.o parser/parser.tab.o 
	gcc main.c ui.o parser/parser.tab.o ftree.o btree.o btable.o function.o interpreter.o utils.o -o $@ $(OPT)

clean:
	rm -f *.o parser/parser.tab.o

