CFLAGS = -g -Wall

ifdef CROSS_COMPILE
	CC = $(CROSS_COMPILE)gcc
else
	CC = gcc
endif

default: aesdsocket

all: aesdsocket

aesdsocket: aesdsocket.o
	$(CC) $(CFLAGS) aesdsocket.o -o aesdsocket

aesdsocket.o: aesdsocket.c
	$(CC) $(CFLAGS) -c aesdsocket.c -o aesdsocket.o

clean:
	rm -f aesdsocket
	rm -f *.o
