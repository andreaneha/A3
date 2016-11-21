#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ncurses.h>
#include<time.h>
#include"structs.h"
#include"buildLevel.h"
#include"checkChar.h"
#include"fileparse.h"
#include"heroloc.h"
#include"navigate.h"
#include"roomLoc.h"


int checkChar(char string[], char searchFor);

//Code that switches room items extrated from the file to ones to be displayed
char switchElem(char elem)
{
	int number;

	time_t t;
	char newElem;
	switch(elem)
	{
		case('h'):
			newElem = '@';
			break;
		case('z'):
			newElem = '<';
			break;
		case('a'):
			newElem = '>';
			break;
		case('g'):
			newElem = '*';
			break;
		case('G'):
			newElem = '8';
			break;
		case('w'):
			newElem = '(';
			break;
		case('W'):
			newElem = ')';
			break;
		case('m'):
                        srand((unsigned) time(&t));
			number = rand() % 4;
			switch(number){
				case(0):
					newElem = 'A';
					break;
				case(1):
					newElem = 'B';
					break;
				case(2):
					newElem = 'Z';
					break;
				case(3):
					newElem = 'S';
					break;
			}
			break;
		case('e'):
			newElem = ']';
			break;
		case('M'):
			newElem = 'T';
			break;
		case('p'):
			newElem = '!';
			break;
		default:
			printf("A item in the specification text file is not valid\n");
			exit(0);
			break;
	}
return newElem;
}


//Code that stores doors
struct Rooms* storeDoors(char rawDoor[], int doorNum, struct Rooms* room)
{
	if(rawDoor[0] != 'd')
	{
		free(room);
		exit(0);
	}
	char wall;
	char *loc;
	int position;
	wall = rawDoor[1];
	loc = &rawDoor[2];
	position = atoi(loc);
	room -> doors[doorNum]. wall = wall;
	room -> doors[doorNum]. position = position;
	return room;
}

// code that saves room dimensions to the struct
struct Rooms* roomDimensions(char rawDim[], struct Rooms * room)
{
	int charLength;
	char * row;
	char * column;
	int i;
	row = &rawDim[0];

	charLength = strlen(rawDim);
	for(i = 0; i<charLength; i++)
	{
		if (rawDim[i] =='X'){
			rawDim[i] = '\0';
			column = &rawDim[i+1];
		}
	}

	room -> height = atoi(row);
	room -> width = atoi(column);
	return room;
}

//code that handles other entries
struct Rooms* handleItems(char itemLoc[],int itemNum, struct Rooms*room)
{
	int i;
	int stringLength;
	char displayItem;
	char *xloc;
	char *yloc;
	time_t t;
	srand((unsigned) time(&t));
	xloc = &itemLoc[1];
	stringLength = strlen(itemLoc);
	for (i=1; i<stringLength; i++)
	{
		if (itemLoc[i]==',')
		{
			itemLoc[i] = '\0';
			yloc = &itemLoc[i+1];
			break;
		}
	}
	displayItem = switchElem(itemLoc[0]);

	room->other[itemNum].item = displayItem;
	room-> other[itemNum].xlocal = atoi(xloc);
	room-> other[itemNum].ylocal = atoi(yloc);
	switch(displayItem){
		case(']'): //equipment
			room->other[itemNum].stat = rand() % 20;
			break;
		case('('): // rareweapon
			room -> other[itemNum].stat = (rand()%5)+10;
			break;
		case(')'): //comman weapon
			room->other[itemNum].stat = (rand() % 8) +1;
			break;
		default:
			break;
	}

return room;
}


struct Rooms ** fileParse(char filename[], int numRooms)
{
	FILE*levelInfo;
	char *wordPntr[15]; 
	int w;
	char line [150]; 
	int lineSize;
	int k;
	int exists;
	int doorNum;
	int numMonsters;
	Room ** roompntr;
	roompntr = (struct Rooms**)malloc(numRooms* sizeof(struct Rooms*));
	if (roompntr == NULL)
	{
		printf("out of memory\n");
		exit(1);
	}

	int otherNum;
	k=0;
	doorNum = 0;
	numMonsters = 0;

	levelInfo = fopen(filename,"rt");
	while(fgets(line,1000,levelInfo) != NULL)
	{

		w=0;
		roompntr[k] = (Room*)malloc(sizeof(Room));
		if (roompntr == NULL)
		{
			printf("out of memory\n");
			exit(1);
		}

		lineSize = strlen(line);

		wordPntr[w] = &line[0];
		w++;
		for(int i = 0;i<lineSize;i++)
		{
			if(line[i]==' ')
			{
				line[i] = '\0';
				wordPntr[w] = &line[i+1];
				w++;
			}
		}

	//save dimensions in struct 
        roompntr[k] = roomDimensions(wordPntr[0],roompntr[k]);
	doorNum = 0;
	otherNum = 0;
	for(int i=1; i<w;i++)
	{
		exists = checkChar(wordPntr[i],'d');

		if(exists == 1)
		{
			if(doorNum>=4)
			{
				printf("A room can only have up to 4 doors");
				exit(0);
			}
			roompntr[k]=storeDoors(wordPntr[i],doorNum, roompntr[k]);
			doorNum++;
		}
		else
		{
			numMonsters = checkChar(wordPntr[i], 'm')+numMonsters;
			roompntr[k] = handleItems(wordPntr[i],otherNum,roompntr[k]);
			otherNum++;
		}



	}
	roompntr[k] -> numDoors = doorNum;
	roompntr[k] -> numOther = otherNum;
//	printf("%d braahh\n", roompntr[k]-> numOther);

	k++;
	}
	fclose(levelInfo);
	return roompntr;

}

