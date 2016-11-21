#include<stdio.h>
#include<stdlib.h>
#include<ncurses.h>
#include"structs.h"
#include"buildLevel.h"
#include"checkChar.h"
#include"fileparse.h"
#include"heroloc.h"
#include"navigate.h"
#include"roomLoc.h"


int *locateHero(struct Rooms ** aRoom, int numRooms)
{
	//error checking
	if (numRooms>6){
		endwin();
		printf("number of rooms is out of bounds\n");
		exit(0);
	}
	//variable declarations
	int i;
	int j;
	int * heroLoc;
	int heroCount;
	//set heroCount to 0
	heroCount = 0;
	// count and record location of hero
	for(i=0; i<numRooms; i++)
	{

		for(j=0; j<10;j++)
		{
			if(aRoom[i]->other[j].item =='@')
        	        {
        	                heroLoc =(int*)malloc(3*sizeof(int));
				if (heroLoc == NULL)
				{
					printf("out of memory\n");
					exit(1);
				}

        	                heroLoc[0] = (aRoom[i]->other[j].xlocal);
        	                heroLoc[1] = (aRoom[i]->other[j].ylocal);
				//saves the room that the hero exists
				heroLoc[2] = i;
				heroCount++;
			}

		}
	}
	//if no hero is specified in text file, it defaults to (1,0)
	if(heroCount == 0)
	{
		heroLoc[0] = 2;
		heroLoc[1] = 1;
		heroLoc[2] = 0;
	}
	// if multiple heros exists, the program ends
	if(heroCount>1)
	{
		endwin();
		printf("please include only one hero in the whole text file\n");
		exit(0);
	}

	return heroLoc;

}
