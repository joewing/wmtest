
CC=gcc
CFLAGS=-O0 -g -Wall -Werror
LDFLAGS=-g -lX11

OBJECTS= wmtest.o \
         test-util.o \
         test-map.o \
         test-gravity.o

wmtest: $(OBJECTS)
	$(CC) $(LDFLAGS) -o wmtest $(OBJECTS)

.c.o: $*.c
	$(CC) $(CFLAGS) -c $*.c

clean:
	rm -f $(OBJECTS) wmtest
