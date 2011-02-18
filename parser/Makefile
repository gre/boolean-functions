parser.tab.o: parser.y parser.h parser.l
	bison parser.y
	flex parser.l
	gcc -c -g parser.tab.c

parser-test: parser.tab.o parser-test.c parser.h
	gcc -g -o $@ parser.tab.o parser-test.c
	echo "eval AAA BBB" | ./parser-test
