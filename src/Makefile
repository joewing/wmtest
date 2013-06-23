
CC=gcc
CFLAGS=-O0 -g -Wall -Werror
LDFLAGS=-g
LIBS=-lX11

OBJECTS= wmtest.o \
         test-util.o \
         test-desktop.o \
         test-map.o \
         test-gravity.o \
         test-resize.o

wmtest: $(OBJECTS)
	$(CC) $(LDFLAGS) -o wmtest $(OBJECTS) $(LIBS)

.c.o: $*.c
	$(CC) $(CFLAGS) -c $*.c

$(OBJECTS) :: *.h

clean:
	rm -f $(OBJECTS) wmtest
