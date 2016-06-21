CC=gcc
CFLAGS=-Wall -O2

INCLUDES=genetic.h
OBJECTS=main.o genetic.o
BINARY=genetic

all: ${OBJECTS} ${INCLUDES}
	${CC} ${CFLAGS} -o ${BINARY} ${OBJECTS}

clean:
	rm -f ${BINARY}
	rm -f *~
	rm -f ${OBJECTS}
