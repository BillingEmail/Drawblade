CC=gcc
LDFLAGS= -lSDL2 -lSDL2_image
CFLAGS= -g -Wall -std=c11
SRC= ../shared/src/*.c src/*.c

all:
	$(CC) $(CFLAGS) src/main.c -o drawblade $(SRC) $(LDFLAGS)

