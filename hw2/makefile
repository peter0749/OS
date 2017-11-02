all: hw2 valid
hw2: hw2.c msort.o msort.h threadedsum.o threadedsum.h
	gcc hw2.c msort.o threadedsum.o -o hw2 -pthread
msort.o: msort.c msort.h
	gcc msort.c -DPARALLEL -c -o msort.o -pthread
threadedsum.o: threadedsum.c threadedsum.h
	gcc threadedsum.c -c -o threadedsum.o -pthread
valid: valid.c
	gcc valid.c -o valid
clean:
	rm -f msort.o hw2 threadedsum.o valid

