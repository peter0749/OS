all: test
test: msort.o test.c msort.h
	gcc msort.o test.c ${ARGS} -o test
msort.o: msort.c msort.h
	gcc msort.c -c -o msort.o -pthread
clean:
	rm -f msort.o test
