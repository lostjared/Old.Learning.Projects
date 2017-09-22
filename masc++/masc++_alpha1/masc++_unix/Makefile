$CC = g++

all: masc

masc: main.o masc.o
	g++ main.o masc.o -o masc++

masc.o: masc.cpp
	$(CC) -c masc.cpp
main.o: main.cpp
	$(CC) -c main.cpp

clean:
	rm -f *.o

install:
	cp masc /usr/bin/masc
