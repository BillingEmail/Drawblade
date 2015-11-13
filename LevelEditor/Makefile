CC=gcc
CFLAGS= -std=c11 -Wall -g
LDFLAGS= -lSDL2
SRC=src/editrun.c src/loadsave.c src/main.c

leveleditor: $(SRC)
	$(CC) $(CFLAGS) -o leveleditor $(SRC) $(LDFLAGS)
