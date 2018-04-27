GCC = gcc

CFLAGS = -O3

topN: topN.o
	$(GCC) $(CFLAGS) topN.o -o topN

topN.o: topN.c
	$(GCC) $(CFLAGS) -c topN.c -o topN.o

all: topN test

test:
	echo "Running Quick Tests....."
	./test.sh

clean:
	rm topN topN.o

