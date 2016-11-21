#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ncurses.h>
#include<time.h>
#include"structs.h"
#include"buildLevel.h"
#include"checkChar.h"
#include"fileparse.h"
#include"heroloc.h"
#include"navigate.h"
#include"roomLoc.h"

int * itemID(struct Rooms ** room, int numRooms){
	int xPos;
	int yPos;
	int * roomLocate;
	int xPos2;
	int yPos2;
	int i;
	int j;
	int *itemID;
	itemID = (int*)malloc(2*sizeof(int));
	getyx(stdscr,xPos,yPos);

	for(i=0;i<numRooms;i++){
		for(j=0; j < room[i]->numOther; j++){

		roomLocate = roomLoc(i);
		xPos2 = room[i]->other[j].xlocal + roomLocate[0] + 1 ;
		yPos2 = room[i]->other[j].ylocal + roomLocate[1] + 2 ;

			if(xPos2 == xPos && yPos2==yPos){
				itemID[0] = i;
				itemID[1] = j;
				break;
			}
		}
	}

return itemID;
}
