CC=gcc
LDFLAGS= -lm -lSDL2 -lSDL2_image -lSDL2_ttf
CFLAGS= -g -Wall -std=c11
SRC= ../shared/src/*.c src/button.c src/textbox.c src/character.c src/collisions.c src/game.c src/HUD.c src/menu.c src/object.c src/player.c src/world.c ../LevelEditor/src/leveleditor.c
all:
	$(CC) $(CFLAGS) src/main.c -o drawblade $(SRC) $(LDFLAGS)


charactertest:
	$(CC) $(CFLAGS) src/tests/charactertest.c -o charactertest $(SRC) $(LDFLAGS)

menutest:
	$(CC) $(CFLAGS) src/tests/testmainmenu.c -o menutest ../shared/src/container.c ../shared/src/texture.c src/mainmenu.c $(LDFLAGS)
