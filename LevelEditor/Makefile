CC=gcc
CFLAGS= -std=c11 -Wall -g
LDFLAGS= -lSDL2 -lSDL2_image
SRC= ../shared/src/level.c src/leveleditor.c src/main.c ../shared/src/container.c ../shared/src/texture.c

leveleditor: $(SRC)
	$(CC) $(CFLAGS) -o leveleditor $(SRC) $(LDFLAGS)
