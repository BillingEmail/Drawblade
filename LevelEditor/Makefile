CC=gcc
CFLAGS= -std=c11 -Wall -g
LDFLAGS= -lSDL2
SRC= ../shared/src/level.c src/leveleditor.c src/main.c

leveleditor: $(SRC)
	$(CC) $(CFLAGS) -o leveleditor $(SRC) $(LDFLAGS)
