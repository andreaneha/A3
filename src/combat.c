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

int countMonsters(struct Rooms**rooms, int numRooms)
{
	int numMonsters;
	numMonsters = 0;
	for(int i=0; i<numRooms; i++)
	{
		for(int j=0; j < rooms[i]->numOther; j++)
		{
			switch(rooms[i]->other[j].item)
			{
				case('A'):
					numMonsters++;
					break;
				case('B'):
					numMonsters++;
					break;
				case('S'):
					numMonsters++;
					break;
				case('Z'):
					numMonsters++;
					break;
				case('T'):
					numMonsters++;
					break;
				default:
					break;
			}
		}
	}
	return numMonsters;
}


int patrol(struct Monsters ** monster, int cycle, int numMonsters){

	for(int i=0; i<numMonsters ; i++){
		int xLoc;
		int yLoc;
		char locCheck;
		if(monster[i]-> healthPoints >= 1){
			mvaddch(monster[i]->xPos, monster[i]->yPos, '.');
		}
		if(monster[i]-> type == 'Z'){
			switch(cycle%2){
				case 0:
					xLoc = monster[i]->xPos -1;
					yLoc = monster[i]->yPos;
					break;
				case 1:
					xLoc = monster[i]->xPos + 1;
					yLoc = monster[i]->yPos;
					break;
			}

		}
		else if (monster[i]->type == 'B'){
			int num;
			time_t t;
			srand((unsigned) time(&t));
			num = rand() % 4;
			switch(num){
				case 0:
					xLoc = monster[i]->xPos -1;
					yLoc = monster[i]->yPos;
					break;
				case 1:
					xLoc= monster[i]->xPos +1;
					yLoc = monster[i]->yPos;
					break;
				case 2:
					yLoc = monster[i]->yPos -1;
					xLoc = monster[i]->xPos;
					break;
				case 3:
					yLoc = monster[i]->yPos +1;
					xLoc = monster[i]->xPos;
					break;
				}
		}
		else if (monster[i]-> type == 'S')
		{
			switch(cycle%4){
				case 0: 
					yLoc = monster[i]->yPos +1;
					xLoc = monster[i]->xPos;
					break;
				case 1:
					xLoc = monster[i]->xPos;
					yLoc = monster[i]->yPos +1;
					break;
				case 2:
					xLoc = monster[i]->xPos;
					yLoc = monster[i]->yPos -1;
					break;
				case 3:
					xLoc = monster[i]->xPos;
					yLoc = monster[i]->yPos -1;
					break;
			}
		}

		else if (monster[i]-> type == 'T')
		{
			switch(cycle%4){
				case 0: 
					yLoc = monster[i]->yPos;
					xLoc = monster[i]->xPos - 1;
					break;
				case 1:
					xLoc = monster[i]->xPos;
					yLoc = monster[i]->yPos+1;
					break;
				case 2:
					xLoc = monster[i]->xPos+1;
					yLoc = monster[i]->yPos;
					break;
				case 3:
					xLoc = monster[i]->xPos;
					yLoc = monster[i]->yPos-1;
					break;
			}
		}


		else{
			xLoc = monster[i]->xPos;
			yLoc = monster[i]->yPos;
		}

		locCheck = mvinch(xLoc, yLoc);
		if(monster[i]-> healthPoints >= 1 && locCheck == '.'){
			monster[i]->xPos = xLoc;
			monster[i]->yPos = yLoc;
			mvaddch(monster[i]->xPos, monster[i]->yPos, monster[i]-> type);

		}
		else if(monster[i]-> healthPoints >= 1 && locCheck != '.'){
				mvaddch(monster[i]->xPos, monster[i]->yPos, monster[i]-> type);
		}


	}
	return 0;

}

int combat(struct Monsters ** monster, int monsterID){
	time_t t;
	srand((unsigned) time(&t));
	int randNum;

	randNum = (rand() % 9)+1;
	if (randNum > monster[monsterID]->speed){
		monster[monsterID]->healthPoints = monster[monsterID]->healthPoints - 5;
		move(0,0);
		clrtoeol();
		printw("Hero caused 5 damage");

		if (monster[monsterID]->healthPoints < 1){
			mvaddch(monster[monsterID]->xPos, monster[monsterID]->yPos, '.');
			move(0,0);
			clrtoeol();
			printw("hero killed %d %d", monster[monsterID]->xPos, monster[monsterID]->yPos);
		}


		return 0;
	}
	else{
		move(0,0);
		printw("Hero lost %d health or attack", monster[monsterID]->attackRating);
		return monster[monsterID]->attackRating;
	}
}

int monsterID(struct Monsters ** monster, int numMons, int xPos, int yPos){
	int i;
	for(i=0; i<numMons; i++){
		if (monster[i]->xPos == xPos && monster[i]->yPos == yPos){
				break;
		}
	}
	return i;
}


