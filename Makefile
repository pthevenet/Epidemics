CC = gcc
CFLAGS += -std=c99 -Wall -g -Wshadow -I/usr/include/python2.7
LDLIBS += -lpython2.7

# ---------- COMMAND LINE ----------

cli.o:
	cd cli && $(CC) $(CFLAGS) cli.c -o ../CLI $(LDLIBS)

cli: cli/cli.o


clean:
	rm -f cli/cli.o CLI
