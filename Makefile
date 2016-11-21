all: 
	gcc src/checkchar.c src/fileparse.c src/main.c src/buildLevel.c src/roomLoc.c src/navigate.c src/locatehero.c src/combat.c src/monsterstruct.c src/itemid.c -Wall -std=c99 -lncurses -I include
	./a.out assets/level.txt
