CC=gcc
LDFLAGS= -lSDL2 -lSDL2_image
CFLAGS= -g -Wall -std=c11
SRC= src/character.c src/object.c ../shared/src/*.c 

object:
	$(CC) $(CFLAGS) src/tests/testobject.c -o objecttest $(SRC) $(LDFLAGS)

character:
	$(CC) $(CFLAGS) src/tests/testcharacter.c -o charactertest $(SRC) $(LDFLAGS)

