.PHONY: clean

DEBUG = -Wall -g -DDEBUG -DTRACE
OPT = ${DEBUG}

all: clean main

utils.o : utils.c utils.h
	gcc -c utils.c -o $@ $(OPT)

parser/parser.tab.o:
	cd parser; make

file.o: file.c file.h
	gcc -c file.c -o $@ $(OPT)

point.o: point.c point.h
	gcc -c point.c -o $@ $(OPT)
  
points.o: points.c points.h
	gcc -c points.c -o $@ $(OPT)

btree.o: btree.c btree.h
	gcc -c btree.c -o $@ $(OPT)
  
btable.o: btable.c btable.h point.o ftree.o btree.o
	gcc -c btable.c -o $@ $(OPT)
  
ftree.o: ftree.c ftree.h point.o btree.o
	gcc -c ftree.c -o $@ $(OPT)
  
function.o: function.c function.h ftree.o btable.o btree.o
	gcc -c function.c -o $@ $(OPT)

interpreter.o : interpreter.c interpreter.h function.o ftree.o btable.o parser/parser.tab.o file.o
	gcc -c interpreter.c -o $@ $(OPT)

ui.o : ui.c ui.h
	gcc -c ui.c -o $@ $(OPT)

main: main.c globals.h function.o ftree.o btree.o btable.o interpreter.o file.o ui.o utils.o parser/parser.tab.o point.o points.o
	gcc main.c function.o ftree.o btree.o btable.o interpreter.o ui.o utils.o file.o parser/parser.tab.o point.o points.o -o $@ $(OPT)

clean:
	rm -f *.o parser/parser.tab.o

