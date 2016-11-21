#include<stdio.h>
#include<stdlib.h>
#include<ncurses.h>
#include"structs.h"
#include<time.h>
#include"structs.h"
#include"buildLevel.h"
#include"checkChar.h"
#include"fileparse.h"
#include"heroloc.h"
#include"navigate.h"
#include"roomLoc.h"
#include"monster.h"
#include"itemidentity.h"
#include"monsterstruct.h"

struct Monsters ** monsterStruct(int numRooms, struct Rooms ** room){

	move(20, 100);
	Monsters ** monsters;
	int otherEl;
	int monsterCount;

	monsterCount = 0;
	monsters = (Monsters**)malloc(15*sizeof(Monsters*));
        if (monsters == NULL)
        {
                printf("out of memory\n");
                exit(1);
        }


	for(int count = 0; count<numRooms; count++){
		otherEl= room[count]->numOther;

		for(int otherCount = 0; otherCount<otherEl; otherCount++){
			int isAMonster;
			int healthPoints;
			int attackRating;
			int speed;
			switch(room[count]->other[otherCount].item){
				case('A'):
					isAMonster = 1;
					healthPoints = 5;
					attackRating =1;
					speed =2;
					break;
				case('B'):
					isAMonster = 1;
					healthPoints = 2;
					attackRating =5;
					speed =4;
					break;
				case('S'):
					isAMonster = 1;
					healthPoints = 5;
					attackRating =5;
					speed =4;
				case('Z'):
					isAMonster = 1;
					healthPoints = 15;
					attackRating =5; 
					speed = 2;
					break;
				case('T'):
					isAMonster = 1;
					healthPoints = 50;
					attackRating =5; 
					speed = 3;
					break;
				default:
					isAMonster = 0;
					break;
			}
			if(isAMonster==1){
				int *monsLoc;
				monsters[monsterCount] = (Monsters*)malloc(sizeof(Monsters));
			        if (monsters[monsterCount] == NULL)
			        {
                			printf("out of memory\n");
                			exit(1);
        			}
				monsters[monsterCount]->type = room[count]->other[otherCount].item;
				monsters[monsterCount]->healthPoints = healthPoints;
				monsters[monsterCount]->attackRating= attackRating;
				monsters[monsterCount]->speed = speed;
				monsters[monsterCount]->roomNumber = count;
				monsLoc = roomLoc(count);
				monsters[monsterCount]->xPos =1+ monsLoc[0]+ room[count]-> other[otherCount].xlocal;
				monsters[monsterCount]->yPos =1+ monsLoc[1]+ room[count]-> other[otherCount].ylocal;
				monsterCount++;

			}
		}

	}
	return monsters;

return 0;
}
