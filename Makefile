CC = gcc
CFLAGS += -std=c99 -Wall -g -Wshadow -I/usr/include/python2.7
LDLIBS += -lpython2.7


all: cli

# ---------- COMMAND LINE ----------

cli.o: cli.c cli.h

cli: cli.o


clean:
	rm -f cli.o cli
