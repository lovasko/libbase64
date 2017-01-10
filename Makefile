CC=clang
CFLAGS=-O3 -fPIC -Isrc -ansi -pedantic -Wall -Wextra -Weverything
LDFLAGS= 
SRC=./src
EXECUTABLE=libbase64.so
OBJECTS=decode.o encode.o

all: libbase64.so

libbase64.so: $(OBJECTS)
	$(CC) -fPIC -o libbase64.so -shared $(OBJECTS) $(LDFLAGS)

clean:
	rm *.o libbase64.so 

decode.o: $(SRC)/decode.c
	$(CC) $(CFLAGS) -c $(SRC)/decode.c -o decode.o

encode.o: $(SRC)/encode.c
	$(CC) $(CFLAGS) -c $(SRC)/encode.c -o encode.o
